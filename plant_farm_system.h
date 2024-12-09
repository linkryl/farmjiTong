#include"map_system.h" 
#include<cstdlib>
//class plant_farm:node
class plant_farm//土地种植类 
{
	private:
		double water_condition;//水状态 
		double fertilizer_condition;//肥料状态
		bool hoed_flag;//是否被锄过 
		bool planted_flag;//是否已经播种
		double planted_time;//生长时间
		Prop_system *prop_system;//物品映射
//		const Time_system* time_system;
	public:
		plant_farm();
		~plant_farm(){}
		base_plant *plant;//植物类，用于存放当前地块上 
//		void set_time(const Time_system* main_time);
		void update_conditon(int now_weather);//更新作物状态函数，1，2，3，4分别为春夏秋冬，在每天开始时执行 
		int plant_seed(int seed);//种植函数，返回1表示播种成功，-1为未锄地，-2为已经播种 
		bool hoe_ground();//锄地函数
		Harvest get_harvest();//收获函数
		double add_fertilizer(double fertilizer_num);//施肥函数，返回值为多余的肥量 
		double add_water(double water_num);//浇水函数，返回值为剩余的水量 
		bool add_medicine();//治疗函数  
}; 
plant_farm::plant_farm()//构造函数进行初始化 
{
	hoed_flag=false;
	planted_time=false;
	water_condition=25;//初始水为25 
	fertilizer_condition=0;//初始没有肥料 
	plant = new base_plant;
	prop_system = new Prop_system;
}
//void plant_farm::set_time(const Time_system* main_time)
//{
//	time_system=main_time;
//}
void plant_farm::update_conditon(int now_season)//每日状态更新函数，需要在日期发生变更时执行 
{
	if(planted_flag!=false)//播种后才有更新 
	{
		if(plant->get_health()==0)//死了就不更新了，需要重新锄地 
		{
			return;
		} 
		Consumption now_consumption=plant->get_consumption();//先获取种植的作物的消耗量 
		//以下更新权值应当利用季节类进行，但是时间总线没有写，所以用裸露在外的权值代替
		double water_weight,fertilizer_weight,growth_speed;
		switch(now_season)
		{ 
			case 1:
				water_weight=1,fertilizer_weight=1,growth_speed=1;//春天权重 
				break;
			case 2:
				water_weight=2,fertilizer_weight=2,growth_speed=2;//夏天权重 
				break;
			case 3:
				water_weight=1.5,fertilizer_weight=0.5,growth_speed=1;//秋天权重 
				break;
			case 4:
				water_weight=0.5,fertilizer_weight=0.5,growth_speed=0.5;//冬天权重 
				break;
		}
		now_consumption.fertilizer_consumption*=fertilizer_weight;//根据权重更新消耗量 
		now_consumption.water_consumption*=water_weight;
		if(water_condition>=now_consumption.water_consumption&&fertilizer_condition>=now_consumption.fertilizer_consumption&&plant->get_illness()==false)//如果满足消耗需求且不属于生病状态 
		{
			water_condition-=now_consumption.water_consumption;//消耗水和肥料 
			fertilizer_condition-=now_consumption.fertilizer_consumption;
			planted_time+=growth_speed;//更新生长状态
			int rand_val=rand();
			plant->set_health(10);//每天恢复10点健康（溢出在上边处理过了） 
			if(rand_val%1111==1)
			{
				plant->set_illness(1);//正常情况有1/1111的几率生病 
			}
		}
		if(plant->get_illness()==true)//生病状态仍在 
		{
			//病了也会消耗水和肥料 
			if(water_condition>=now_consumption.water_consumption)//如果水还够 
			{
				water_condition-=now_consumption.water_consumption;//消耗水
			} 
			if(fertilizer_condition>=now_consumption.fertilizer_consumption)//如果肥料还够 
			{
				fertilizer_condition-=now_consumption.fertilizer_consumption;//消耗肥料
			}
			plant->set_health(-20);//每天健康-20 
		}
		if(water_condition<now_consumption.water_consumption||fertilizer_condition<now_consumption.fertilizer_consumption)//如果不满足消耗需求
		{
			int rand_weight=2;
			if(water_condition>=now_consumption.water_consumption)//如果水还够 
			{
				water_condition-=now_consumption.water_consumption;//消耗水
				rand_weight--;//随机权重降低 
			} 
			if(fertilizer_condition>=now_consumption.fertilizer_consumption)//如果肥料还够 
			{
				fertilizer_condition-=now_consumption.fertilizer_consumption;//消耗肥料
				rand_weight--;//随机权重降低
			}
			//此处植物不生长且不恢复健康值 
			int rand_val=rand();
			if(rand_val%(22/rand_weight)==1)
			{
				plant->set_illness(1);//不正常情况有最高1/11的几率生病 
			}
		}
		if(plant->get_health()==0)//如果植物已经死了 
		{
			hoed_flag=false;//锄地标签还原为没锄过 
		} 
	} 
}
bool plant_farm::hoe_ground()//锄地函数
{
	if(hoed_flag==false)//如果没锄过 
	{
		hoed_flag=true;//更新为已经锄过 
		return true; 
	}
	return false;//否则返回false 
} 
int plant_farm::plant_seed(int seed)//播种函数 
{
	if(hoed_flag==false)
	{
		return -1;//没锄过地不能播种 
	} 
	if(planted_flag==true)
	{
		return -2;//一块地不能重复播种两次 
	} 
	
	*plant=prop_system->get_plant(seed+10); //此处按照编码规则获取种子对应的作物编号 
	planted_flag=true;//更新当前为止的播种状态 
	return 1;
}
bool plant_farm::add_medicine()//治疗函数 
{
	if(plant->get_illness()==true)//有病 
	{
		plant->set_illness(false);//就治 
		return true; 
	}
	return false;//没病你瞎治什么 
} 
double plant_farm::add_fertilizer(double fertilizer_num)//施肥函数 
{
	if(fertilizer_condition+fertilizer_num>100)
	{
		double return_fertilizer=fertilizer_condition+fertilizer_num-100;//计算多余的肥料值 
		fertilizer_condition=100;
		return return_fertilizer;
	}
	else
	{
		fertilizer_condition+=fertilizer_num;
		return 0;
	} 
}
double plant_farm::add_water(double water_num)//浇水函数 
{
	if(water_condition+water_num>100)
	{
		double return_water=water_condition+water_num-100;//计算多余的水量 
		water_condition=100;
		return return_water;
	}
	else
	{
		water_condition+=water_num;
		return 0;
	} 
}
Harvest plant_farm::get_harvest()//收获函数 
{
	int growth_step=plant->get_growth_step(planted_time);
	if(growth_step<plant->get_max_step())//还没到收获季节 
	{
		return plant->get_harvest(false);//返回中途收获的值 
	} 
	return plant->get_harvest(true);//返回完整收获的值 
} 
