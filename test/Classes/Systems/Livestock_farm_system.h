#pragma once
#include "Corral_system.h"
#include "Constant.h"
#include "cocos2d.h"
#include "../Utils/MapUtil.h"

class Liverstock_farm_system//5x5���ص�ʵ�� 
{
private:
	Corral corral_land[5];//1x5������ 
	Sprite* plantSprite[5];
	int base_add_x;//���Ͻ����ص����Ͻ�x���� 
	int base_add_y;//���Ͻ����ص����Ͻ�y���� 
public:
	std::map<int, std::string> crop_names{ {PIG_PLANT, "pig"} };
	Liverstock_farm_system(int x = LIVE_FARM_OFFSET_X * 16, int y = LIVE_FARM_OFFSET_Y * 16);
	static Liverstock_farm_system* getInstance() {
		static Liverstock_farm_system liverstock_farm_system;
		return &liverstock_farm_system;
	}
	// ���»������������о���
	void drawFarm();
	void drawFarm(int x);
	bool update_conditon(int x, int y, int day);//����ָ��λ�õ�����״̬����
	void update_all();//�������е����� 
	bool plant_seed(int seed, int x, int y);//��ֳ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
	Harvest get_harvest(int x, int y);//�ջ���
	bool add_food(double fertilizer_num, int x, int y);//ιʳ����������ֵ�Ƿ���ιʳ 
	bool add_water(double water_num, int x, int y);//��ˮ�����������ܷ�ˮ 
	bool add_medicine(int x, int y);//���ƺ��� 
	out_info get_info(int x, int y);//��ȡ���ڸ���ǰ�˵���Ϣ
	void get_closest_corral(int x, int y, int& add_x);//������ת��Ϊ�����±�
};