#include "Time_system.h"

Time_system::Time_system()
{
	start_time = time(0);
	clock_time = 0;
}
void Time_system::update_time()
{
	time_t now_time = time(0);//��ȡ��ǰʱ�� 
	time_t delta_time = now_time - start_time;//������º�ʱ��ı仯�� 
	clock_time += delta_time;//ʱ��ʱ�䱻���� 
	update_clock();//����ʱ�� 
	start_time = now_time;//���ϴε��ø��º������ʱ���趨Ϊ��ǰʱ�� 
}
void Time_system::update_clock()
{
	now_clock.day = clock_time / 720;//������ 
	clock_t hour_sec = (clock_time % 720);
	now_clock.now_hour = hour_sec / 30;//����Сʱ 
	if ((hour_sec % 30) > 15)//����Ѿ����˰�� 
	{
		now_clock.half_hour = true;
	}
	now_clock.weather = now_clock.day % 90 + 1;//���¼��� 
}
bool Time_system::jump_to_morning()
{
	update_time();//�Ƚ�������߻�û���µ�ʱ����µ� 
	if (now_clock.now_hour >= 6 && now_clock.now_hour < 18)//6:00-17:59�ֲ��������ڶ����糿 
	{
		return false;
	}
	time_clock load_time;
	if (load_time.now_hour >= 0 && load_time.now_hour < 6)
	{
		load_time.day = now_clock.day;//�賿˯�����ڲ��� 
	}
	else
	{
		load_time.day = now_clock.day + 1;//��������+1�� 
	}
	load_time.now_hour = 6;
	load_time.half_hour = false;
	clock_time = load_time.day * 720 + load_time.now_hour * 30 + load_time.half_hour * 15;
	load_time.weather = load_time.day % 90 + 1;//���¼��� 
	now_clock = load_time;
	return true;
}
void Time_system::load(time_clock load_time)
{
	update_time();//�Ƚ�������߻�û���µ�ʱ����µ� 
	clock_time = load_time.day * 720 + load_time.now_hour * 30 + load_time.half_hour * 15;
	//���ϱ��ʽ�����еĶ������������� 
	now_clock = load_time;
}
time_clock Time_system::get_time()//����һ��ʱ�ӽṹ�� 
{
	update_time();//����ʱ�� 
	return now_clock;
}
int Time_system::get_clock_time()
{
	return clock_time;
}