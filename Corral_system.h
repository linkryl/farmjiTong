#include"map_system.h" 

class Corral//土地种植类 
{
	private:
		double water_condition;//水状态 
		double food_condition;//肥料状态
		bool planted_flag;//是否已经播种（养殖） 
		double growth_time;//已养殖时间
		Prop_system prop_system;//物品映射表 
		base_animal animal;//植物类，用于存放当前地块上种植的植物 
	public:
		Corral();
		~Corral(){}
		void update_conditon();//更新动物状态函数，在每天开始时执行 
		bool plant_seed(int seed);//养植函数，返回true表示养殖成功，false为养殖失败 
		Harvest get_harvest();//收获函数
		bool add_food(double food_num);//添食函数，返回值是否能施肥 
		bool add_water(double water_num);//加水函数，返回能否加水 
		bool add_medicine();//治疗函数 
		out_info get_info();//获取用于更新前端的信息 
}; 
Corral::Corral()//构造函数进行初始化 
{
	growth_time=false;
	water_condition=0;//初始水为0 
	food_condition=0;//初始没有食物 
}
void Corral::update_conditon()//每日状态更新函数，需要在日期发生变更时执行 
{
	if(planted_flag!=false)//养殖后才有更新 
	{
		if(animal.get_health()==0)//死了就不更新了 
		{
			return;
		} 
		Consumption now_consumption=animal.get_consumption();//先获取养殖的动物的消耗量 
		if(water_condition>=now_consumption.water_consumption&&food_condition>=now_consumption.food_consumption&&animal.get_illness()==false)//如果满足消耗需求且不属于生病状态 
		{
			water_condition-=now_consumption.water_consumption;//消耗水和肥料 
			food_condition-=now_consumption.food_consumption;
			growth_time+=1;//更新生长状态
			int rand_val=rand();
			animal.set_health(10);//每天恢复10点健康（溢出在上边处理过了） 
			if(rand_val%1111==1)
			{
				animal.set_illness(1);//正常情况有1/1111的几率生病 
			}
		}
		if(animal.get_illness()==true)//生病状态
		{
			//病了也会消耗水和肥料 
			if(water_condition>=now_consumption.water_consumption)//如果水还够 
			{
				water_condition-=now_consumption.water_consumption;//消耗水
			} 
			if(food_condition>=now_consumption.food_consumption)//如果肥料还够 
			{
				food_condition-=now_consumption.food_consumption;//消耗肥料
			}
			animal.set_health(-20);//每天健康-20 
		}
		if(water_condition<now_consumption.water_consumption||food_condition<now_consumption.food_consumption)//如果不满足消耗需求
		{
			int rand_weight=2;
			if(water_condition>=now_consumption.water_consumption)//如果水还够 
			{
				water_condition-=now_consumption.water_consumption;//消耗水
				rand_weight--;//随机权重降低 
			} 
			if(food_condition>=now_consumption.food_consumption)//如果食物还够 
			{
				food_condition-=now_consumption.food_consumption;//消耗食物
				rand_weight--;//随机权重降低
			}
			//此处植物不生长且不恢复健康值 
			int rand_val=rand();
			if(rand_val%(22/rand_weight)==1)
			{
				animal.set_illness(1);//不正常情况有最高1/11的几率生病 
			}
		}
	} 
}
bool Corral::plant_seed(int seed)//播种函数 
{
	if(planted_flag==true)
	{
		return false;//一块地不能重复播种两次 
	} 
	animal=prop_system.get_animal(seed+10); //此处按照编码规则获取种子对应的作物编号 
	planted_flag=true;//更新当前为止的播种状态 
	return true;
}
bool Corral::add_medicine()//治疗函数 
{
	if(animal.get_illness()==true)//有病 
	{
		animal.set_illness(false);//就治 
		return true; 
	}
	return false;//没病你瞎治什么 
} 
bool Corral::add_food(double food_num)//施肥函数，返回施肥是否成功 
{
	if(food_condition>=100)//如果食物已满 
	{
		return false;
	}
	else
	{
		food_condition+=food_num;
		if(food_condition>100)//防溢出 
		{
			food_condition=100.0;
		}
		return true;
	} 
}
bool Corral::add_water(double water_num)//浇水函数，返回浇水是否成功 
{
	if(water_condition>=100)//如果水已满 
	{
		return false;
	}
	else
	{
		water_condition+=water_num;
		if(water_condition>100)//防溢出 
		{
			water_condition=100.0;
		}
		return true;
	} 
}
Harvest Corral::get_harvest()//收获函数 
{
	int growth_step=animal.get_growth_step(growth_time);
	planted_flag=false;//畜栏还原为未养殖的状态 
	if(growth_step<animal.get_max_step())//还没到收获季节 
	{
		return animal.get_harvest(false);//返回中途收获的值 
	}
	return animal.get_harvest(true);//返回完整收获的值 
}
out_info Corral::get_info()//用于给前端提供更新用的信息 
{
	//声明并初始化返回值 
	out_info now_info;
	now_info.death_flag=false;
	now_info.fertilizer_flag=false;
	now_info.illness_flag=false;
	now_info.food_flag=false; 
	now_info.type=0;
	now_info.step=0;
	now_info.water_flag=false;
	if(planted_flag==false)//没播种的话
	{
		return now_info;//直接返回默认值 
	}
	now_info.type=animal.get_type();
	if(animal.get_health()==0)//健康值为0 
	{
		now_info.death_flag=true;//激活死亡标记 
	}
	now_info.illness_flag=animal.get_illness();//修改病害标记
	if(food_condition==0)//缺乏食物 
	{
		now_info.food_flag=true;//修改缺食物
	} 
	if(water_condition==0)
	{
		now_info.water_flag=true;//修改缺水标记 
	}
	now_info.step=animal.get_growth_step(growth_time);//修改生长阶段 
	return now_info;//返回前端需求的值 
} 
