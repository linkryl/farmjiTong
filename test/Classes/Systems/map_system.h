#pragma once
#include <map>
#include "basic_plant_and_animal_class.h"
#include "cocos2d.h"

USING_NS_CC;

struct out_info//数据返回类 
{
	int type;//表示作物种类 
	bool death_flag;//true表示作物已经死亡 
	bool water_flag;//true表示作物缺水 
	bool fertilizer_flag;//true表示作物缺少肥料
	bool illness_flag;//true表示作物正在生病 
	bool food_flag;//true表示作物缺少食物 
	int step;//表示作物的生长阶段 
	out_info() {
		death_flag = false;
		fertilizer_flag = false;
		illness_flag = false;
		food_flag = false;
		type = 0;
		step = 0;
		water_flag = false;
	}
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

class ColorSystem {
public:
	static Color3B getPlantColor(out_info& info) {
		if (info.death_flag) {
			return Color3B::BLACK;
		}
		else if (info.illness_flag) {
			return Color3B::BLUE;
		}
		else if (info.water_flag) {
			return Color3B::RED;
		}
		else if (info.fertilizer_flag || info.food_flag) {
			return Color3B::GRAY;
		}
		else {
			return Color3B::WHITE;
		}
	}
};
