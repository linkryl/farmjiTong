#include "Corral_system.h"

Corral::Corral()//构造函数进行初始化 
{
	growth_time = 0;
	water_condition = 0;//初始水为25 
	food_condition = 0;//初始没有食物 
	planted_flag = false;
}
void Corral::update_conditon()//每日状态更新函数，需要在日期发生变更时执行 
{
	if (planted_flag != false)//播种后才有更新 
	{
		//		cout<<"update"<<endl;
		if (animal.get_health() == 0)//死了就不更新了
		{
			return;
		}
		Consumption now_consumption = animal.get_consumption();//先获取种植的作物的消耗量 
		//		cout<<"fertilizer_condition: "<<fertilizer_condition<<endl;
		if (water_condition >= now_consumption.water_consumption && food_condition >= now_consumption.food_consumption && animal.get_illness() == false)//如果满足消耗需求且不属于生病状态 
		{
			//			cout<<"health"<<endl;
			water_condition -= now_consumption.water_consumption;//消耗水和食物 
			food_condition -= now_consumption.food_consumption;
			growth_time += 1;//更新生长状态
			int rand_val = rand();
			animal.set_health(10);//每天恢复10点健康（溢出在上边处理过了） 
			if (rand_val % 1111 == 1)
			{
				animal.set_illness(1);//正常情况有1/1111的几率生病 
			}
			return;
		}
		if (animal.get_illness() == true)//生病状态仍在 
		{
			//病了也会消耗水和食物 
			if (water_condition >= now_consumption.water_consumption)//如果水还够 
			{
				water_condition -= now_consumption.water_consumption;//消耗水
			}
			if (food_condition >= now_consumption.food_consumption)//如果食物还够 
			{
				food_condition -= now_consumption.food_consumption;//消耗食物
			}
			animal.set_health(-20);//每天健康-20 
			//			cout<<"health: "<<plant.get_health()<<endl;
			return;
		}
		if (water_condition < now_consumption.water_consumption || food_condition < now_consumption.food_consumption)//如果不满足消耗需求
		{
			int rand_weight = 2;
			//			cout<<water_condition<<" "<<fertilizer_condition<<endl;
			if (water_condition >= now_consumption.water_consumption)//如果水还够 
			{
				water_condition -= now_consumption.water_consumption;//消耗水
				rand_weight--;//随机权重降低 
			}
			if (food_condition >= now_consumption.food_consumption)//如果食物还够 
			{
				food_condition -= now_consumption.food_consumption;//消耗食物
				rand_weight--;//随机权重降低
			}
			//此处植物不生长且不恢复健康值 
			int rand_val = rand();
			if (rand_val % (22 / rand_weight) == 1)
			{
				animal.set_illness(1);//不正常情况有最高1/11的几率生病 
			}
			//			plant.set_illness(1);
		}
	}
}
bool Corral::plant_seed(int seed)//播种函数 
{
	if (planted_flag == true)
	{
		return false;//一块地不能重复播种两次 
	}
	animal = prop_system.get_animal(seed + 10); //此处按照编码规则获取种子对应的作物编号 
	planted_flag = true;//更新当前为止的播种状态 
	return true;
}
bool Corral::add_medicine()//治疗函数 
{
	if (animal.get_illness() == true)//有病 
	{
		animal.set_illness(false);//就治 
		return true;
	}
	return false;//没病你瞎治什么 
}
bool Corral::add_food(double food_num)//喂食函数，返回喂食是否成功 
{
	if (food_condition >= 100)//如果食物已满 
	{
		return false;
	}
	else
	{
		food_condition += food_num;
		if (food_condition > 100)
		{
			food_condition = 100.0;
		}
		return true;
	}
}
bool Corral::add_water(double water_num)//浇水函数，返回浇水是否成功 
{
	if (water_condition >= 100)//如果水已满 
	{
		return false;
	}
	else
	{
		water_condition += water_num;
		if (water_condition > 100)
		{
			water_condition = 100.0;
		}
		return true;
	}
}
Harvest Corral::get_harvest()//收获函数 
{
	Harvest empty_harvest = animal.get_harvest(false);
	empty_harvest.harvest_type_a = -1;
	empty_harvest.harvest_type_b = -1;
	empty_harvest.max_harvest_num_a = 0;
	empty_harvest.max_harvest_num_b = 0;
	//	cout<<endl<<planted_flag<<endl; /
	if (planted_flag == false)//如果这块土地没有被播种过 
	{
		return empty_harvest;//返回空收获 
	}
	planted_flag = false;//土地还原为未播种的状态 
	if (animal.get_health() == 0)//如果收获的是死的作物 
	{
		return empty_harvest;//返回一个空收获 
	}
	int growth_step = animal.get_growth_step(growth_time);//获取生长阶段 
	if (growth_step < animal.get_max_step())//还没到收获季节 
	{
		//		cout<<"ztz22"<<endl;
		return animal.get_harvest(false);//返回中途收获的值 
	}
	return animal.get_harvest(true);//返回完整收获的值 
}
out_info Corral::get_info()//用于给前端提供更新用的信息 
{
	//声明并初始化返回值 
	out_info now_info;
	now_info.death_flag = false;
	now_info.fertilizer_flag = false;
	now_info.illness_flag = false;
	now_info.food_flag = false;
	now_info.type = 0;
	now_info.step = 0;
	now_info.water_flag = false;
	if (planted_flag == false)//没播种的话
	{
		return now_info;//直接返回默认值 
	}
	now_info.type = animal.get_type();
	if (animal.get_health() == 0)//健康值为0 
	{
		now_info.death_flag = true;//激活死亡标记 
	}
	now_info.illness_flag = animal.get_illness();//修改病害标记
	if (food_condition == 0)//缺乏食物 
	{
		now_info.food_flag = true;//修改缺食物标记 
	}
	if (water_condition == 0)
	{
		now_info.water_flag = true;//修改缺水标记 
	}
	//	cout<<"growth_time: "<<growth_time<<endl;
	now_info.step = animal.get_growth_step(growth_time);//修改生长阶段 
	return now_info;//返回前端需求的值 
}