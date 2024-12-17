#include<ctime>

#ifndef ztz11
#define ztz11 ztzk 
#include<iostream>
#include<cstdlib>
#undef ztz11
#endif

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
	Time_system();
	~Time_system() {};
	void update_time();//����ʱ�� 
	time_clock get_time();//��ȡʱ��
	//����ʱ��ʱ��ĺ��������ݵ�ǰ��clock_time���¼���clock 
	void update_clock();//�����������¼���ʱ�ӵĺ��� 
	int get_clock_time();//��������ķ�ʽ�洢��ʱ��ʱ��
	bool jump_to_morning();//��Ծ���ڶ������ϵĺ�����false��ʾ��ǰʱ�䲻����Ծ 
	void load(time_clock load_time);//�趨ʱ�亯�� 
};
