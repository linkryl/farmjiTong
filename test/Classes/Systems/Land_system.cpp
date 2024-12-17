#include "Land_system.h"

Land::Land()//构造函数进行初始化 
{
	growth_time = 0;
	water_condition = 25;//初始水为25 
	fertilizer_condition = 0;//初始没有肥料 
	planted_flag = false;
}
void Land::update_conditon(int now_season)//每日状态更新函数，需要在日期发生变更时执行 
{
	if (planted_flag == false)//播种后才有更新 
	{
		return;
	}
	//		cout<<"update"<<endl;
	if (plant.get_health() == 0)//死了就不更新了
	{
		return;
	}
	Consumption now_consumption = plant.get_consumption();//先获取种植的作物的消耗量 
	//以下更新权值应当利用季节类进行，但是时间总线没有写，所以用裸露在外的权值代替
	double water_weight, fertilizer_weight, growth_speed;
	//		cout<<"now_season: "<<now_season<<endl;
	switch (now_season)
	{
		case 1:
			water_weight = 1, fertilizer_weight = 1, growth_speed = 1;//春天权重 
			break;
		case 2:
			water_weight = 2, fertilizer_weight = 2, growth_speed = 2;//夏天权重 
			break;
		case 3:
			water_weight = 1.5, fertilizer_weight = 0.5, growth_speed = 1;//秋天权重 
			break;
		case 4:
			water_weight = 0.5, fertilizer_weight = 0.5, growth_speed = 0.5;//冬天权重 
			break;
	}
	now_consumption.fertilizer_consumption *= fertilizer_weight;//根据权重更新消耗量 
	now_consumption.water_consumption *= water_weight;
	//		cout<<"fertilizer_condition: "<<fertilizer_condition<<endl;
	if (water_condition >= now_consumption.water_consumption && fertilizer_condition >= now_consumption.fertilizer_consumption && plant.get_illness() == false)//如果满足消耗需求且不属于生病状态 
	{
		//			cout<<"health"<<endl;
		water_condition -= now_consumption.water_consumption;//消耗水和肥料 
		fertilizer_condition -= now_consumption.fertilizer_consumption;
		growth_time += growth_speed;//更新生长状态
		int rand_val = rand();
		plant.set_health(10);//每天恢复10点健康（溢出在上边处理过了） 
		if (rand_val % 1111 == 1)
		{
			plant.set_illness(1);//正常情况有1/1111的几率生病 
		}
		return;
	}
	if (plant.get_illness() == true)//生病状态仍在 
	{
		//病了也会消耗水和肥料 
		if (water_condition >= now_consumption.water_consumption)//如果水还够 
		{
			water_condition -= now_consumption.water_consumption;//消耗水
		}
		if (fertilizer_condition >= now_consumption.fertilizer_consumption)//如果肥料还够 
		{
			fertilizer_condition -= now_consumption.fertilizer_consumption;//消耗肥料
		}
		plant.set_health(-20);//每天健康-20 
		//			cout<<"health: "<<plant.get_health()<<endl;
		return;
	}
	if (water_condition < now_consumption.water_consumption || fertilizer_condition < now_consumption.fertilizer_consumption)//如果不满足消耗需求
	{
		int rand_weight = 2;
		//			cout<<water_condition<<" "<<fertilizer_condition<<endl;
		if (water_condition >= now_consumption.water_consumption)//如果水还够 
		{
			water_condition -= now_consumption.water_consumption;//消耗水
			rand_weight--;//随机权重降低 
		}
		if (fertilizer_condition >= now_consumption.fertilizer_consumption)//如果肥料还够 
		{
			fertilizer_condition -= now_consumption.fertilizer_consumption;//消耗肥料
			rand_weight--;//随机权重降低
		}
		//此处植物不生长且不恢复健康值 
		int rand_val = rand();
		if (rand_val % (22 / rand_weight) == 1)
		{
			plant.set_illness(1);//不正常情况有最高1/11的几率生病 
		}
		//			plant.set_illness(1);
	}
}
bool Land::plant_seed(int seed)//播种函数 
{
	if (planted_flag == true)
	{
		return false;//一块地不能重复播种两次 
	}
	plant = prop_system.get_plant(seed + 10); //此处按照编码规则获取种子对应的作物编号 
	planted_flag = true;//更新当前为止的播种状态 
	return true;
}
bool Land::add_medicine()//治疗函数 
{
	if (plant.get_illness() == true)//有病 
	{
		plant.set_illness(false);//就治 
		return true;
	}
	return false;//没病你瞎治什么 
}
bool Land::add_fertilizer(double fertilizer_num)//施肥函数，返回施肥是否成功 
{
	if (fertilizer_condition >= 100)//如果肥料已满 
	{
		return false;
	}
	else
	{
		fertilizer_condition += fertilizer_num;
		if (fertilizer_condition > 100)
		{
			fertilizer_condition = 100.0;
		}
		return true;
	}
}
bool Land::add_water(double water_num)//浇水函数，返回浇水是否成功 
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
Harvest Land::get_harvest()//收获函数 
{
	Harvest empty_harvest = plant.get_harvest(false);
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
	if (plant.get_health() == 0)//如果收获的是死的作物 
	{
		return empty_harvest;//返回一个空收获 
	}
	int growth_step = plant.get_growth_step(growth_time);//获取生长阶段 
	if (growth_step < plant.get_max_step())//还没到收获季节 
	{
		//		cout<<"ztz22"<<endl;
		return plant.get_harvest(false);//返回中途收获的值 
	}
	return plant.get_harvest(true);//返回完整收获的值 
}
out_info Land::get_info()//用于给前端提供更新用的信息 
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
	now_info.type = plant.get_type();
	if (plant.get_health() == 0)//健康值为0 
	{
		now_info.death_flag = true;//激活死亡标记 
	}
	now_info.illness_flag = plant.get_illness();//修改病害标记
	if (fertilizer_condition == 0)//缺乏肥料 
	{
		now_info.fertilizer_flag = true;//修改缺肥料标记 
	}
	if (water_condition == 0)
	{
		now_info.water_flag = true;//修改缺水标记 
	}
	//	cout<<"growth_time: "<<growth_time<<endl;
	now_info.step = plant.get_growth_step(growth_time);//修改生长阶段 
	return now_info;//返回前端需求的值 
}