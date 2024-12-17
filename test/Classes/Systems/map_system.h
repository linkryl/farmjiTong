#pragma once
#include <map>
#include "basic_plant_and_animal_class.h"

struct out_info//���ݷ����� 
{
	int type;//��ʾ�������� 
	bool death_flag;//true��ʾ�����Ѿ����� 
	bool water_flag;//true��ʾ����ȱˮ 
	bool fertilizer_flag;//true��ʾ����ȱ�ٷ���
	bool illness_flag;//true��ʾ������������ 
	bool food_flag;//true��ʾ����ȱ��ʳ�� 
	int step;//��ʾ����������׶� 
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
