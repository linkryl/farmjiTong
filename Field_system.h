#include"basic_plant_and_ground_class.h"

#ifndef ztz11
#define ztz11 ztzk
#include<iostream>
#include<cstdio>
using namespace std;
#endif

class Field_system
{
	private:
		int season;
		int now_day;
		time_clock now_time;
		const Time_system* time_system;
	public:
		plant_farm field[5][6];
		Field_system(Time_system* main_time);
		~Field_system();
		void load_field();//¶ÁÈ¡´æµµº¯Êý 
};
Field_system::Field_system(Time_system* main_time)
{
	time_system=main_time;
	for(int i=0;i<5;i++)
	{
		for(int j=0;i<6;j++)
		{
			field[i][j].set_time(main_time);
		}
	}
}


#undef ztz11
