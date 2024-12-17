#include<ctime>

#ifndef ztz11
#define ztz11 ztzk 
#include<iostream>
#include<cstdlib>
#undef ztz11
#endif

struct time_clock
{
	int day;//记录游戏中已经经过的日期，这里按照720s一天,30s一小时来计算
	int now_hour;//记录当前小时 
	bool half_hour;//记录是否是半点，原游戏中时间步进位8:00,8：30,9:00 
	int weather;//记录当前季节，1，2，3，4为春夏秋冬，为了便于计算，一年只有360天 
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
	time_t start_time;//上次调用更新函数后的时间 
	time_clock now_clock;//时钟 
	time_t clock_time;//以秒的方式存储时钟时间，避免存在时间丢失 
public:
	Time_system();
	~Time_system() {};
	void update_time();//更新时间 
	time_clock get_time();//获取时间
	//更新时钟时间的函数，根据当前的clock_time重新计算clock 
	void update_clock();//根据秒数重新计算时钟的函数 
	int get_clock_time();//返回以秒的方式存储的时钟时间
	bool jump_to_morning();//跳跃到第二天早上的函数，false表示当前时间不能跳跃 
	void load(time_clock load_time);//设定时间函数 
};
