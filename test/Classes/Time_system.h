#pragma once
#include<ctime>
#include<iostream>
#include<cstdlib>

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
		time_t now_time = time(nullptr);//获取当前时间 
		time_t delta_time = now_time - start_time;//计算更新后时间的变化量 
		clock_time += delta_time;//时钟时间被更新 
		update_clock();//更新时钟 
		start_time = now_time;//将上次调用更新函数后的时间设定为当前时间 
	}//更新时间 
	time_clock get_time()
	{
		update_time();//更新时间 
		return now_clock;
	}//获取时间
	//更新时钟时间的函数，根据当前的clock_time重新计算clock 
	void update_clock()
	{
		now_clock.day = clock_time / 720;//更新天 
		clock_t hour_sec = (clock_time % 720);
		now_clock.now_hour = hour_sec / 30;//更新小时 
		if ((hour_sec % 30) > 15)//如果已经过了半点 
		{
			now_clock.half_hour = true;
		}
		now_clock.weather = now_clock.day % 90 + 1;//更新季节 
	}//根据秒数重新计算时钟的函数 
	int get_clock_time()
	{
		return clock_time;
	}//返回以秒的方式存储的时钟时间
	bool jump_to_morning() {
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
	}//跳跃到第二天早上的函数，false表示当前时间不能跳跃 
	void load(time_clock load_time)
	{
		update_time();//先将队列里边还没更新的时间更新掉 
		clock_time = load_time.day * 720 + load_time.now_hour * 30 + load_time.half_hour * 15;
		//以上表达式中所有的多余的秒均被舍弃 
		now_clock = load_time;
	}//设定时间函数 
};