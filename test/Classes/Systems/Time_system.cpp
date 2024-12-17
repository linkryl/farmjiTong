#include "Time_system.h"

Time_system::Time_system()
{
	start_time = time(0);
	clock_time = 0;
}
void Time_system::update_time()
{
	time_t now_time = time(0);//获取当前时间 
	time_t delta_time = now_time - start_time;//计算更新后时间的变化量 
	clock_time += delta_time;//时钟时间被更新 
	update_clock();//更新时钟 
	start_time = now_time;//将上次调用更新函数后的时间设定为当前时间 
}
void Time_system::update_clock()
{
	now_clock.day = clock_time / 720;//更新天 
	clock_t hour_sec = (clock_time % 720);
	now_clock.now_hour = hour_sec / 30;//更新小时 
	if ((hour_sec % 30) > 15)//如果已经过了半点 
	{
		now_clock.half_hour = true;
	}
	now_clock.weather = now_clock.day % 90 + 1;//更新季节 
}
bool Time_system::jump_to_morning()
{
	update_time();//先将队列里边还没更新的时间更新掉 
	if (now_clock.now_hour >= 6 && now_clock.now_hour < 18)//6:00-17:59分不能跳到第二天早晨 
	{
		return false;
	}
	time_clock load_time;
	if (load_time.now_hour >= 0 && load_time.now_hour < 6)
	{
		load_time.day = now_clock.day;//凌晨睡觉日期不变 
	}
	else
	{
		load_time.day = now_clock.day + 1;//否则日期+1； 
	}
	load_time.now_hour = 6;
	load_time.half_hour = false;
	clock_time = load_time.day * 720 + load_time.now_hour * 30 + load_time.half_hour * 15;
	load_time.weather = load_time.day % 90 + 1;//更新季节 
	now_clock = load_time;
	return true;
}
void Time_system::load(time_clock load_time)
{
	update_time();//先将队列里边还没更新的时间更新掉 
	clock_time = load_time.day * 720 + load_time.now_hour * 30 + load_time.half_hour * 15;
	//以上表达式中所有的多余的秒均被舍弃 
	now_clock = load_time;
}
time_clock Time_system::get_time()//返回一个时钟结构体 
{
	update_time();//更新时间 
	return now_clock;
}
int Time_system::get_clock_time()
{
	return clock_time;
}