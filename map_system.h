
#include<map>
#include"basic_plant_and_animal_class.h"

struct out_info//数据返回类 
{
	int type;//表示作物种类 
	bool death_flag;//true表示作物已经死亡 
	bool water_flag;//true表示作物缺水 
	bool fertilizer_flag;//true表示作物缺少肥料
	bool illness_flag;//true表示作物正在生病 
	bool food_flag;//true表示作物缺少食物 
	int step;//表示作物的生长阶段 
}; 

class Prop_system
{
	private:
		map<int,Harvest> Harvest_map;
		map<int,base_plant> Plant_map;
		map<int,base_animal> Animal_map;
	public:
		Prop_system();
		Harvest get_harvset(int num);//用于查找获取编号对应的收获物
		base_plant get_plant(int num);//用于查找获取编号对应的作物
		base_animal get_animal(int num);//用于查找获取编号对应的动物 
};
Prop_system::Prop_system()
{
	//物品映射遵照如下编码： 
	//1110为蔬菜作物，1100为蔬菜种子，1120为收获的蔬菜 
	//1111为谷物作物，1101为谷物种子，1121为收获的谷物 
	//2110为猪，2100为猪仔，2120为猪肉 
	//初始化收获数据 
	Harvest vegetable_harvest;
	Harvest corn_harvest;
	Harvest pig_harvest;
	vegetable_harvest.harvest_type_a=1120;
	vegetable_harvest.max_harvest_num_a=1;
	vegetable_harvest.harvest_type_b=1100;
	vegetable_harvest.max_harvest_num_b=2;//种子收获返回2个 
	corn_harvest.harvest_type_a=1121;
	corn_harvest.max_harvest_num_b=2;
	corn_harvest.harvest_type_b=1101;
	corn_harvest.max_harvest_num_b=2;//种子收获返回2个 
	pig_harvest.harvest_type_a=2120;
	pig_harvest.max_harvest_num_a=3;
	pig_harvest.harvest_type_b=2100;
	pig_harvest.max_harvest_num_b=2;//幼崽收获返回2个 
	
	//初始化生长数据
	Growth_time vegetable_growth_time;
	Growth_time corn_growth_time;
	Growth_time pig_growth_time;
	vegetable_growth_time.level_num=4;
	vegetable_growth_time.growth_time[0]=0;
	vegetable_growth_time.growth_time[1]=1;
	vegetable_growth_time.growth_time[2]=3;
	vegetable_growth_time.growth_time[3]=6;
	corn_growth_time.level_num=5;
	corn_growth_time.growth_time[0]=0;
	corn_growth_time.growth_time[1]=2;
	corn_growth_time.growth_time[2]=4;
	corn_growth_time.growth_time[3]=6;
	corn_growth_time.growth_time[4]=8;
	pig_growth_time.level_num=3;
	pig_growth_time.growth_time[0]=0;
	pig_growth_time.growth_time[1]=5;
	pig_growth_time.growth_time[2]=10;
	
	//初始化消耗量数据
	Consumption vegetable_consumption;
	Consumption corn_consumption;
	Consumption pig_consumption;
	vegetable_consumption.fertilizer_consumption=2;//蔬菜不消耗食物，耗水2，耗肥2 
	vegetable_consumption.water_consumption=2;
	vegetable_consumption.food_consumption=0;
	corn_consumption.fertilizer_consumption=1;//谷物不消耗食物，耗水2，耗肥1 
	corn_consumption.water_consumption=2;
	corn_consumption.food_consumption=0;
	pig_consumption.fertilizer_consumption=0;//猪不消耗肥料，耗水1，耗食2 
	pig_consumption.water_consumption=1;
	pig_consumption.food_consumption=2;
	
	//初始化类数据 
	base_plant vegetable;
	base_plant corn;
	base_animal pig; 
	vegetable.set_all(vegetable_growth_time,vegetable_harvest,vegetable_consumption,1110);
	corn.set_all(corn_growth_time,corn_harvest,corn_consumption,1111);
	pig.set_all(pig_growth_time,pig_harvest,pig_consumption,2110);
	
	//将定义好的部分压入map
	Harvest_map.insert(std::make_pair(1100,vegetable_harvest));
	Harvest_map.insert(std::make_pair(1101,corn_harvest));
	Harvest_map.insert(std::make_pair(2101,pig_harvest));
	Plant_map.insert(std::make_pair(1110,vegetable));
	Plant_map.insert(std::make_pair(1111,corn));
	Animal_map.insert(std::make_pair(2110,pig));
	
	
	//以下为不可变部分的物品map
	Harvest stone_harvest;
	Harvest tree_harvest;
	Harvest ironstone_harvest;
	
	//初始化收获数据
	stone_harvest.harvest_type_a=3020;//碎石编号3020 
	stone_harvest.max_harvest_num_a=2;//最大掉落2 
	stone_harvest.harvest_type_b=0;//收获结构体的第二项为空 
	stone_harvest.max_harvest_num_b=0;
	tree_harvest.harvest_type_a=3021;//3021是木头 
	tree_harvest.max_harvest_num_a=3;//最大掉落3 
	tree_harvest.harvest_type_b=0;//收获结构体的第二项为空 
	tree_harvest.max_harvest_num_b=0; 
	ironstone_harvest.harvest_type_a=3022;//3022是铁锭 
	ironstone_harvest.max_harvest_num_a=1;//最大掉落1 
	ironstone_harvest.harvest_type_b=0;//收获结构体的第二项为空 
	ironstone_harvest.max_harvest_num_b=0; 
	
	//将定义好的部分压入map
	Harvest_map.insert(std::make_pair(3010,stone_harvest));//3010是石头
	Harvest_map.insert(std::make_pair(3011,stone_harvest));//3011是树
	Harvest_map.insert(std::make_pair(3012,stone_harvest));//3012是铁矿石 
}
Harvest Prop_system::get_harvset(int num)
{
	std::map<int,Harvest>::iterator it;
	it=Harvest_map.find(num);
	if(it!=Harvest_map.end())
	{
		return it->second;
	}
}
base_plant Prop_system::get_plant(int num)
{
	std::map<int,base_plant>::iterator it;
	it=Plant_map.find(num);
	if(it!=Plant_map.end())
	{
		return it->second;
	}
} 
base_animal Prop_system::get_animal(int num)
{
	std::map<int,base_animal>::iterator it;
	it=Animal_map.find(num);
	if(it!=Animal_map.end())
	{
		return it->second;
	}
}
