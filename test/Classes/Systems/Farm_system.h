#ifndef FARM_SYSTEM_H
#define FARM_SYSTEM_H

#include "Land_system.h"
#include "../Utils/MapUtil.h"
#include "Constant.h"
#include "cocos2d.h"
//#include "FarmScene.h"

class Farm_system//5x5���ص�ʵ�� 
{
public:
	Land farm_land[5][5];//5x5������
	Sprite* plantSprite[5][5];
	int base_add_x;//���½����ص����½�x���� 
	int base_add_y;//���½����ص����½�y���� 
public:
	std::map<int, std::string> crop_names{ {PARSNIP_PLANT, "parsnip"}, { WHEAT_PLANT, "wheat" } };
	Farm_system(int x = FARM_OFFSET_X * 16, int y = FARM_OFFSET_Y * 16);
	static Farm_system* getInstance() {
		static Farm_system instance;
		return &instance;
	}
	// ���»���ũ�������о���
	void drawFarm();
	void drawFarm(int x, int y, bool demo = false);
	bool update_conditon(int x, int y, int day);//����ָ��λ�õ�����״̬����
	void update_all(int day);//�������ڸ������е����� 
	bool plant_seed(int seed, int x, int y, bool isTile = false);//��ֲ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
	Harvest get_harvest(int x, int y);//�ջ���
	bool add_fertilizer(double fertilizer_num, int x, int y, bool isTile = false);//ʩ�ʺ���������ֵ�Ƿ���ʩ�� 
	bool add_water(double water_num, int x, int y, bool isTile = false);//��ˮ�����������ܷ�ˮ 
	bool add_medicine(int x, int y, bool isTile = false);//���ƺ��� 
	out_info get_info(int x, int y, bool isTile = false);//��ȡ���ڸ���ǰ�˵���Ϣ
	void get_closest_land(int x, int y, int& add_x, int& add_y);//������ת��Ϊũ���±�
};


#endif