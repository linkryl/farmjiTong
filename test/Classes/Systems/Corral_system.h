#pragma once
#include "map_system.h" 

class Corral//畜栏类 
{
private:
	double water_condition;//水状态 
	double food_condition;//食物状态
	bool planted_flag;//是否已经播种
	double growth_time;//已生长时间
	Prop_system prop_system;//物品映射表 
	base_animal animal;//植物类，用于存放当前地块上种植的植物 
public:
	Corral();
	~Corral() {}
	void update_conditon();//更新作物状态函数，与季节无关 
	bool plant_seed(int seed);//种植函数，返回true表示播种成功，false为播种失败 
	Harvest get_harvest();//收获函数
	bool add_food(double food_num);//喂食函数，返回值是否能喂食 
	bool add_water(double water_num);//浇水函数，返回能否浇水 
	bool add_medicine();//治疗函数 
	out_info get_info();//获取用于更新前端的信息 
};
