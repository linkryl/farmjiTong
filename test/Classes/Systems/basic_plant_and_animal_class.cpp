#include "basic_plant_and_animal_class.h"

void base_farm::set_all(Growth_time g_time, Harvest h, Consumption c, int now_type)//初始化函数的实现 
{
	illness = false;//初始不处于疾病状态 
	plant_health = 100;//设定初始健康度为100 
	growth_time = g_time;//逐个将参数进行赋值
	harvest = h;
	consumption = c;
	fresh_flag = true; //将初始化状态置为true 
	type = now_type;
	return;
}
int base_farm::get_type()//获取当前物品的种类
{
	return type;
}
Consumption base_farm::get_consumption()//获取消耗量 
{
	if (fresh_flag)//确保初始化了才能返回 
	{
		return consumption;
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
	return Consumption();
}
void base_farm::set_consumption(Consumption now_consumption)//设定消耗量 
{
	consumption = now_consumption;
}
Harvest base_farm::get_harvest(bool time_flag)//获取收获物资 
{
	if (fresh_flag)//确保初始化了才能返回 
	{
		if (time_flag == true)
		{
			return harvest;
		}
		else//时间不够就返回的话什么返回一个空收获 
		{
			Harvest empty;
			empty.harvest_type_a = -1;
			empty.max_harvest_num_a = 0;
			empty.harvest_type_b = -1;
			empty.max_harvest_num_b = 0;
			return empty;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
	return Harvest();
}
int base_farm::get_health()//获取健康状态 
{
	if (fresh_flag)//确保初始化了才能返回 
	{
		return plant_health;
	}
	return -1;
	//此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_health(int delta_health)//设定健康状态 
{
	if (plant_health == 0)//健康为0说明已经死亡，无法再调整（否则那叫复活） 
	{
		return;
	}
	plant_health += delta_health;//对健康度进行调整 
	if (plant_health > 100)
	{
		plant_health = 100;//防止溢出 
	}
	if (plant_health < 0)
	{
		plant_health = 0;//防止溢出 
	}
}
bool base_farm::get_illness()//获取疾病状态 
{
	if (fresh_flag)//确保初始化了才能返回 
	{
		return illness;
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
	return false;
}
void base_farm::set_illness(bool now_illness)//设定疾病状态
{
	illness = now_illness;
}
int base_farm::get_growth_step(double time)//获取当前生长阶段 
{
	if (fresh_flag)//播种过的才能获取 
	{
		if (time > growth_time.growth_time[growth_time.level_num - 1])
		{
			return growth_time.level_num;//大于所有的生长阶段，则为最大生长阶段 
		}
		for (int i = 0; i < growth_time.level_num; i++)//否则根据前缀和获取生长阶段 
		{
			if (growth_time.growth_time[i] > time)
			{
				return i;
			}
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
	return -1;
}


Harvest base_plant::get_harvest(bool time_flag)//收获函数 
{
	if (is_fresh())//确保初始化了才能返回 
	{
		Harvest now_harvest = base_farm::get_harvest(true);//先获取收获结构体 
		if (time_flag == true)//如果是成熟后收获 
		{
			return now_harvest;//直接返回所有的收获值 
		}
		else//时间不够就只返回种子 
		{
			now_harvest.max_harvest_num_a = 0;//收获物归零
			now_harvest.max_harvest_num_b = 1;//种子的最大返回值变成1 
			return now_harvest;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
	return Harvest();
}


Harvest base_animal::get_harvest(bool time_flag)//收获函数 
{
	if (is_fresh())//确保初始化了才能返回 
	{
		Harvest now_harvest = base_farm::get_harvest(time_flag);//先获取收获结构体 
		if (time_flag == true)//如果是成熟后收获 
		{
			return now_harvest;//直接返回所有的收获值 
		}
		else//时间不够就什么也不返回 
		{
			now_harvest.max_harvest_num_a = 0;//收获物归零
			now_harvest.max_harvest_num_b = 0;//幼崽的返回值归零 
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
	return Harvest();
}