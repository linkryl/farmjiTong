#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct Harvest//�ջ�ṹ�� 
{
	int harvest_type_a, harvest_type_b;//�ջ������࣬aΪ�ջ��bΪ���� 
	int max_harvest_num_a, max_harvest_num_b;//�ջ�������
	Harvest& operator =(const Harvest& other)//���ص��ں� 
	{
		if (this != &other)
		{
			harvest_type_a = other.harvest_type_a;
			max_harvest_num_a = other.max_harvest_num_a;
			harvest_type_b = other.harvest_type_b;
			max_harvest_num_b = other.max_harvest_num_b;
		}
		return *this;
	}
};
struct Consumption//�������ṹ��
{
	double water_consumption;//��ˮ��
	double fertilizer_consumption;//����������
	double food_consumption;//ʳ��������
	Consumption& operator = (const Consumption& other)//���ص��ں� 
	{
		if (this != &other)
		{
			water_consumption = other.water_consumption;
			fertilizer_consumption = other.fertilizer_consumption;
			food_consumption = other.food_consumption;
		}
		return *this;
	}
};
struct Growth_time//������ʱ�ṹ�� 
{
	int level_num;//�����Ľ׶���
	int growth_time[10];//ÿ�ε�����ʱ�䣬ʹ��ǰ׺�ͽ��д洢 
	Growth_time& operator = (const Growth_time& other)//���ص��ں� 
	{
		if (this != &other)
		{
			level_num = other.level_num;
			for (int i = 0; i < level_num; i++)
			{
				growth_time[i] = other.growth_time[i];
			}
		}
		return *this;
	}
};
class base_farm//һ�п���ֳ/��ֲ����Ʒ���� 
{
private:
	Growth_time growth_time;//������ʱ 
	Harvest harvest;//�ջ���Ʒ 
	Consumption consumption;//������ 
	int plant_health;//����״̬,0-100
	bool illness;//����״̬
	bool fresh_flag;//�Ƿ��Ѿ���ɳ�ʼ��
	int type;//�洢�������� 
public:
	base_farm() { fresh_flag = false; }
	~base_farm() {}
	void set_all(Growth_time g_time, Harvest h, Consumption c, int now_type);//��ʼ�����������ڳ�ʼ���趨����������������湹�캯�� 
	Consumption get_consumption();//��ȡ������Ϣ 
	void set_consumption(Consumption now_consumption);//�趨������Ϣ
	virtual Harvest get_harvest(bool time_flag);//��ȡ�ջ����Ʒ
	int get_health();//��ȡ����״̬
	void set_health(int delta_health);//�趨���Ӽ�������״̬
	bool get_illness();//��ȡ��ǰ�ļ���״̬
	void set_illness(bool now_illness);//�趨����״̬
	int get_growth_step(double time);//��ȡ��ǰ�����׶� 
	int get_max_step()//���ؿɴﵽ��������߽׶� 
	{
		return growth_time.level_num;
	}
	int get_type();//��ȡ��ǰ��Ʒ������
	bool is_fresh() { return fresh_flag; }
	base_farm& operator = (const base_farm& other)//���ص��ں� 
	{
		if (this != &other)//��ֹ���Ҹ�ֵ 
		{
			growth_time = other.growth_time;
			harvest = other.harvest;
			consumption = other.consumption;
			plant_health = other.plant_health;
			illness = other.illness;
			fresh_flag = other.fresh_flag;
			type = other.type;
		}
		return *this;
	}
};

class base_plant :public base_farm//�ɻ���ũ��������������ֲ���� 
{
public:
	base_plant() :base_farm() {};//Ĭ�Ϲ��캯�� 
	Harvest get_harvest(bool time_flag);//��д��ȡ�ջ����Ʒ���� 
	base_plant& operator = (const base_plant& other)
	{
		base_farm::operator = (other);
		return *this;
	}
};

class base_animal :public base_farm//�ɻ���ũ�������������Ķ����� 
{
public:
	base_animal() :base_farm() {};//Ĭ�Ϲ��캯�� 
	Harvest get_harvest(bool time_flag);//��д��ȡ�ջ����Ʒ���� 
	base_animal& operator = (const base_animal& other)
	{
		base_farm::operator = (other);
		return *this;
	}
};