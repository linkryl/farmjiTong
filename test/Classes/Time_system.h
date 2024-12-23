#pragma once
#include<ctime>
#include<iostream>
#include<cstdlib>

struct time_clock
{
	int day;//��¼��Ϸ���Ѿ����������ڣ����ﰴ��720sһ��,30sһСʱ������
	int now_hour;//��¼��ǰСʱ 
	bool half_hour;//��¼�Ƿ��ǰ�㣬ԭ��Ϸ��ʱ�䲽��λ8:00,8��30,9:00 
	int weather;//��¼��ǰ���ڣ�1��2��3��4Ϊ�����ﶬ��Ϊ�˱��ڼ��㣬һ��ֻ��360�� 
	time_clock()
	{
		day = 0;
		now_hour = 0;
		half_hour = 0;
	}
};
class Time_system
{
private:
	time_t start_time;//�ϴε��ø��º������ʱ�� 
	time_clock now_clock;//ʱ�� 
	time_t clock_time;//����ķ�ʽ�洢ʱ��ʱ�䣬�������ʱ�䶪ʧ

public:

	static Time_system* getInstance()
	{
		static Time_system* _instance = new (std::nothrow) Time_system();
		return _instance;
	}
	Time_system()
	{
		start_time = time(nullptr);
		clock_time = 0;
	}
	~Time_system() {};
	void update_time()
	{
		time_t now_time = time(nullptr);//��ȡ��ǰʱ�� 
		time_t delta_time = now_time - start_time;//������º�ʱ��ı仯�� 
		clock_time += delta_time;//ʱ��ʱ�䱻���� 
		update_clock();//����ʱ�� 
		start_time = now_time;//���ϴε��ø��º������ʱ���趨Ϊ��ǰʱ�� 
	}//����ʱ�� 
	time_clock get_time()
	{
		update_time();//����ʱ�� 
		return now_clock;
	}//��ȡʱ��
	//����ʱ��ʱ��ĺ��������ݵ�ǰ��clock_time���¼���clock 
	void update_clock()
	{
		now_clock.day = clock_time / 720;//������ 
		clock_t hour_sec = (clock_time % 720);
		now_clock.now_hour = hour_sec / 30;//����Сʱ 
		if ((hour_sec % 30) > 15)//����Ѿ����˰�� 
		{
			now_clock.half_hour = true;
		}
		now_clock.weather = now_clock.day % 90 + 1;//���¼��� 
	}//�����������¼���ʱ�ӵĺ��� 
	int get_clock_time()
	{
		return clock_time;
	}//��������ķ�ʽ�洢��ʱ��ʱ��
	bool jump_to_morning() {
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
	}//��Ծ���ڶ������ϵĺ�����false��ʾ��ǰʱ�䲻����Ծ 
	void load(time_clock load_time)
	{
		update_time();//�Ƚ�������߻�û���µ�ʱ����µ� 
		clock_time = load_time.day * 720 + load_time.now_hour * 30 + load_time.half_hour * 15;
		//���ϱ��ʽ�����еĶ������������� 
		now_clock = load_time;
	}//�趨ʱ�亯�� 
};