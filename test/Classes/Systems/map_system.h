#pragma once
#include <map>
#include "basic_plant_and_animal_class.h"
#include "cocos2d.h"

USING_NS_CC;

struct out_info//���ݷ����� 
{
	int type;//��ʾ�������� 
	bool death_flag;//true��ʾ�����Ѿ����� 
	bool water_flag;//true��ʾ����ȱˮ 
	bool fertilizer_flag;//true��ʾ����ȱ�ٷ���
	bool illness_flag;//true��ʾ������������ 
	bool food_flag;//true��ʾ����ȱ��ʳ�� 
	int step;//��ʾ����������׶� 
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
	Harvest get_harvset(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ���ջ���
	base_plant get_plant(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ������
	base_animal get_animal(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ�Ķ��� 
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
