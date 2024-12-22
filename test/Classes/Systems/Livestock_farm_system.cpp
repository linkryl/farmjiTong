#include "Livestock_farm_system.h"

Liverstock_farm_system::Liverstock_farm_system(int x, int y) : base_add_x(x), base_add_y(y) {}

// 重绘整个牧场
void Liverstock_farm_system::drawFarm() {
	for (int i = 0; i < 5; ++i) {
		drawFarm(i);
	}
}
// 重绘一格牧场
void Liverstock_farm_system::drawFarm(int x) {
	Scene* scene = Director::getInstance()->getRunningScene();
	if (plantSprite[x] != nullptr) {
		scene->removeChild(plantSprite[x]);
	}
	auto info = get_info(16 * (LIVE_FARM_OFFSET_X + x * 3), 16 * LIVE_FARM_OFFSET_Y);
	if (info.type == 0) {
		plantSprite[x] = nullptr;
		return;
	}
	auto str = "/Animals/" + crop_names[info.type] + "_" + std::to_string(info.step) + ".png";
	plantSprite[x] = Sprite::create("/Animals/" + crop_names[info.type] + "_" + std::to_string(info.step) + ".png");
	plantSprite[x]->setPosition((16 * (LIVE_FARM_OFFSET_X + x * 3) - 8), (16 * LIVE_FARM_OFFSET_Y + 8));
	plantSprite[x]->setAnchorPoint(Vec2(0, 0));
	plantSprite[x]->setColor(ColorSystem::getPlantColor(info));
	scene->addChild(plantSprite[x]);
}

bool Liverstock_farm_system::update_conditon(int x, int y, int day)//根据当前的天数和地址进行指定坐标的作物更新 
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的畜栏 
	if (add_x == -1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	corral_land[add_x].update_conditon();
	return true;
}
void Liverstock_farm_system::update_all()//更新所有畜栏 
{
	for (int i = 0; i < 5; i++)
	{
		corral_land[i].update_conditon();//更新每一块土地 
	}
}
bool Liverstock_farm_system::plant_seed(int seed, int x, int y)//播种操作 
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的农田 
	if (add_x == -1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	bool result = corral_land[add_x].plant_seed(seed);//进行对指定土地的播种操作 
	if (result) drawFarm(add_x);
	return result;
}
Harvest Liverstock_farm_system::get_harvest(int x, int y)//收获函数
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的农田 
	//	cout<<endl<<add_x<<" "<<add_y<<endl<<endl;
	if (add_x == -1)//如果溢出 
	{
		Harvest empty_harvest;
		empty_harvest.harvest_type_a = -1;
		empty_harvest.harvest_type_b = -1;
		empty_harvest.max_harvest_num_a = 0;
		empty_harvest.max_harvest_num_b = 0;
		return empty_harvest;//返回一个空收获 
	}
	//	cout<<"ztz11"<<endl;
	return corral_land[add_x].get_harvest();
}
bool Liverstock_farm_system::add_food(double food_num, int x, int y)//喂食函数 
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的农田 
	if (add_x == -1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	bool result = corral_land[add_x].add_food(food_num);
	if (result) drawFarm(add_x);
	return result;
}
bool Liverstock_farm_system::add_water(double water_num, int x, int y)//浇水函数 
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的农田 
	if (add_x == -1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	bool result = corral_land[add_x].add_water(water_num);
	if (result) drawFarm(add_x);
	return result;
}
bool Liverstock_farm_system::add_medicine(int x, int y)//治疗函数 
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的农田 
	if (add_x == -1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	bool result = corral_land[add_x].add_medicine();
	if (result) drawFarm(add_x);
	return result;
}
out_info Liverstock_farm_system::get_info(int x, int y)//获取用于更新前端的信息
{
	int add_x;
	get_closest_corral(x, y, add_x);//获取能操作的畜栏 
	//声明并初始化 
	out_info now_info;
	now_info.death_flag = false;
	now_info.fertilizer_flag = false;
	now_info.illness_flag = false;
	now_info.food_flag = false;
	now_info.type = 0;
	now_info.step = 0;
	now_info.water_flag = false;
	if (add_x == -1)//如果溢出 
	{
		return now_info;//返回空信息 
	}
	return corral_land[add_x].get_info();
}
void Liverstock_farm_system::get_closest_corral(int x, int y, int& add_x)//将坐标转化为农田下标
{
	//与可交互点位置在8以内即可进行交互 
	add_x = -1;

	// y划定一个范围即可
	if (y <= (base_add_y - 8) || y >= (base_add_y + 48)) {
		return;
	}
	// x越界 
	if (x <= (base_add_x - 8) || x >= (base_add_x + 16 + 4 * 48)) {
		return;
	}
	//不越界的话 
	add_x = ((x + 8 - base_add_x) / 16 + 1) / 3;//进行四舍五入的取值 
}