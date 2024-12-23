#ifndef FARM_SYSTEM_H
#define FARM_SYSTEM_H

#include "Land_system.h"
#include "../Utils/MapUtil.h"
#include "Constant.h"
#include "cocos2d.h"
//#include "FarmScene.h"

class Farm_system//5x5耕地的实现 
{
public:
	Land farm_land[5][5];//5x5的土地
	Sprite* plantSprite[5][5];
	int base_add_x;//左下角土地的左下角x坐标 
	int base_add_y;//左下角土地的左下角y坐标 
public:
	std::map<int, std::string> crop_names{ {PARSNIP_PLANT, "parsnip"}, { WHEAT_PLANT, "wheat" } };
	Farm_system(int x = FARM_OFFSET_X * 16, int y = FARM_OFFSET_Y * 16);
	static Farm_system* getInstance() {
		static Farm_system instance;
		return &instance;
	}
	// 重新绘制农场的所有精灵
	void drawFarm();
	void drawFarm(int x, int y, bool demo = false);
	bool update_conditon(int x, int y, int day);//更新指定位置的作物状态函数
	void update_all(int day);//根据日期更新所有的作物 
	bool plant_seed(int seed, int x, int y, bool isTile = false);//种植函数，返回true表示播种成功，false为播种失败 
	Harvest get_harvest(int x, int y);//收获函数
	bool add_fertilizer(double fertilizer_num, int x, int y, bool isTile = false);//施肥函数，返回值是否能施肥 
	bool add_water(double water_num, int x, int y, bool isTile = false);//浇水函数，返回能否浇水 
	bool add_medicine(int x, int y, bool isTile = false);//治疗函数 
	out_info get_info(int x, int y, bool isTile = false);//获取用于更新前端的信息
	void get_closest_land(int x, int y, int& add_x, int& add_y);//将坐标转化为农田下标
};


#endif