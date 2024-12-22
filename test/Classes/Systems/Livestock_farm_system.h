#pragma once
#include "Corral_system.h"
#include "Constant.h"
#include "cocos2d.h"
#include "../Utils/MapUtil.h"

class Liverstock_farm_system//5x5耕地的实现 
{
private:
	Corral corral_land[5];//1x5的畜栏 
	Sprite* plantSprite[5];
	int base_add_x;//左上角土地的左上角x坐标 
	int base_add_y;//左上角土地的左上角y坐标 
public:
	std::map<int, std::string> crop_names{ {PIG_PLANT, "pig"} };
	Liverstock_farm_system(int x = LIVE_FARM_OFFSET_X * 16, int y = LIVE_FARM_OFFSET_Y * 16);
	static Liverstock_farm_system* getInstance() {
		static Liverstock_farm_system liverstock_farm_system;
		return &liverstock_farm_system;
	}
	// 重新绘制牧场的所有精灵
	void drawFarm();
	void drawFarm(int x);
	bool update_conditon(int x, int y, int day);//更新指定位置的作物状态函数
	void update_all();//更新所有的畜栏 
	bool plant_seed(int seed, int x, int y);//养殖函数，返回true表示播种成功，false为播种失败 
	Harvest get_harvest(int x, int y);//收获函数
	bool add_food(double fertilizer_num, int x, int y);//喂食函数，返回值是否能喂食 
	bool add_water(double water_num, int x, int y);//浇水函数，返回能否浇水 
	bool add_medicine(int x, int y);//治疗函数 
	out_info get_info(int x, int y);//获取用于更新前端的信息
	void get_closest_corral(int x, int y, int& add_x);//将坐标转化为畜栏下标
};