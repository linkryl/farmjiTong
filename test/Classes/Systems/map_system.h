#pragma once
#include <map>
#include "basic_plant_and_animal_class.h"

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
	map<int, Harvest> Harvest_map;
	map<int, base_plant> Plant_map;
	map<int, base_animal> Animal_map;
public:
	Prop_system();
	Harvest get_harvset(int num);//用于查找获取编号对应的收获物
	base_plant get_plant(int num);//用于查找获取编号对应的作物
	base_animal get_animal(int num);//用于查找获取编号对应的动物 
};
