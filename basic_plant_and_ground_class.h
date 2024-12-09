#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"Time_system.h"
using namespace std;
struct Harvest//收获结构体 
{
	int harvest_type;//收获物种类
	int max_harvest_num;//收获的最大量 
	Harvest& operator =(const Harvest& other)//重载等于号 
	{
		if(this!=&other)
		{
			harvest_type=other.harvest_type;
			max_harvest_num=other.max_harvest_num;
		}
		return *this;
	}
}; 
struct Consumption//消耗量结构体
{ 
	double water_consumption;//耗水量
	double fertilizer_consumption;//肥料消耗量
	double food_consumption;//食物消耗量
	Consumption& operator = (const Consumption& other)//重载等于号 
	{
		if(this!=&other)
		{
			water_consumption=other.water_consumption;
			fertilizer_consumption=other.fertilizer_consumption;
			food_consumption=other.food_consumption;
		}	
		return *this;
	}
}; 
struct Growth_time//生长耗时结构体 
{
	int level_num;//生长的阶段数
	int growth_time[10];//每段的消耗时间，使用前缀和进行存储 
	Growth_time& operator = (const Growth_time& other)//重载等于号 
	{
		if(this!=&other)
		{
			level_num=other.level_num;
			for(int i=0;i<level_num;i++)
			{
				growth_time[i]=other.growth_time[i];
			}
		} 
		return *this;
	} 
};
class base_farm//一切可养殖/种植的物品基类 
{
	private:
		Growth_time growth_time;//生长耗时 
		Harvest harvest;//收获物品 
		Consumption consumption;//消耗量 
		int plant_health;//健康状态,0-100
		bool illness;//疾病状态
		bool fresh_flag;//是否已经完成初始化
		int type;//存储自身种类 
	public:
		base_farm(){fresh_flag=false;} 
		~base_farm(){}
		void set_all(Growth_time g_time,Harvest h,Consumption c,int now_type);//初始化函数，由于初始化设定过多所以用这个代替构造函数 
		Consumption get_consumption();//获取消耗信息 
		void set_consumption(Consumption now_consumption);//设定消耗信息
		virtual Harvest get_harvest(bool time_flag);//获取收获的物品
		int get_health();//获取健康状态
		void set_health(int delta_health);//设定（加减）健康状态
		bool get_illness();//获取当前的疾病状态
		void set_illness(bool now_illness);//设定疾病状态
		int get_growth_step(double time);//获取当前生长阶段 
		int get_max_step()//返回可达到的生长最高阶段 
		{
			return growth_time.level_num; 
		}
		int get_type();//获取当前物品的种类
		bool is_fresh(){return fresh_flag;}
		base_farm& operator = (const base_farm& other)//重载等于号 
		{
			if(this!=&other)//防止自我赋值 
			{
				growth_time=other.growth_time;
				harvest=other.harvest;
				consumption=other.consumption;
				plant_health=other.plant_health;
				illness=other.illness;
				fresh_flag=other.fresh_flag;
				type=other.type;
			}	
			return *this;
		}
}; 
void base_farm::set_all(Growth_time g_time,Harvest h,Consumption c,int now_type)//初始化函数的实现 
{
	illness=false;//初始不处于疾病状态 
	plant_health=100;//设定初始健康度为100 
	growth_time=g_time;//逐个将参数进行赋值
	harvest=h; 
	consumption=c;
	fresh_flag=true; //将初始化状态置为true 
	type=now_type;
	return;
}
int base_farm::get_type()//获取当前物品的种类
{
	return type;
}
Consumption base_farm::get_consumption()//获取消耗量 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		return consumption;
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_consumption(Consumption now_consumption)//设定消耗量 
{
	consumption=now_consumption;
}
Harvest base_farm::get_harvest(bool time_flag)//获取收获物资 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		if(time_flag==true)
		{
			return harvest; 
		}
		else//时间不够就返回的话什么返回一个空收获 
		{
			Harvest empty;
			empty.harvest_type=-1;
			empty.max_harvest_num=0;
			return empty;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
} 
int base_farm::get_health()//获取健康状态 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		return plant_health;
	}
	return -1;
	//此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_health(int delta_health)//设定健康状态 
{
	if(plant_health==0)//健康为0说明已经死亡，无法再调整（否则那叫复活） 
	{
		return;
	}
	plant_health+=delta_health;//对健康度进行调整 
	if(plant_health>100)
	{
		plant_health=100;//防止溢出 
	} 
	if(plant_health<0)
	{
		plant_health=0;//防止溢出 
	} 
}
bool base_farm::get_illness()//获取疾病状态 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		return illness; 
	}
	 //此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_illness(bool now_illness)//设定疾病状态
{
	illness=now_illness;
}
int base_farm::get_growth_step(double time)//获取当前生长阶段 
{
	if(time>growth_time.growth_time[growth_time.level_num-1])
	{
		return growth_time.level_num-1;
	} 
	if(fresh_flag)
	{
		for(int i=0;i<growth_time.level_num;i++)
		{
			if(growth_time.growth_time[i]>time)
			{
				return i;
			}
		}
		return growth_time.level_num;//数组下标从0开始，这里要+1 
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}

class base_plant:public base_farm//由基本农场类派生而来的植物类 
{
	public:
		base_plant():base_farm(){};//默认构造函数 
		Harvest get_harvest(bool time_flag);//重写获取收获的物品函数 
		base_plant & operator = (const base_plant& other)
		{
			base_farm::operator = (other); 
			return *this; 
		}
};
Harvest base_plant::get_harvest(bool time_flag)//收获函数 
{
	if(is_fresh())//确保初始化了才能返回 
	{
		if(time_flag==true)
		{
			return base_farm::get_harvest(time_flag);//使用基类的收获函数 
		}
		else//时间不够就返回的话什么都不返回 
		{
			Harvest harvest_seed;
//			empty.harvest_type=-1;//此处应修改为对应作物种子对应的编号，由于还没有写就先空下 
			harvest_seed.max_harvest_num=1;//最多返还一个种子 
			return harvest_seed;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}

class base_animal:public base_farm//由基本农场类派生而来的动物类 
{
	public:
		base_animal():base_farm(){};//默认构造函数 
		Harvest get_harvest(bool time_flag);//重写获取收获的物品函数 
		base_animal & operator = (const base_animal& other)
		{
			base_farm::operator = (other); 
			return *this; 
		}
};
Harvest base_animal::get_harvest(bool time_flag)//收获函数 
{
	if(is_fresh())//确保初始化了才能返回 
	{
		if(time_flag==true)
		{
			return base_farm::get_harvest(time_flag);//使用基类的收获函数 
		}
		else//时间不够就返回的话什么都不返回 
		{
			Harvest harvest_young=base_farm::get_harvest(true);//先拿到基类的总数居 
			harvest_young.max_harvest_num=1;//最多返还一个收获物品 
			return harvest_young;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}
