#pragma once
#ifndef ztz11
#define ztz11
#include<iostream>
#include<cstdio>
using namespace std;
#endif
class Skill
{
public:
  //���������ޣ�������֮�����й�������������ޱ��ⱬint 
	int farm_EXP;//ũ������ 
	int collect_EXP;//�ɼ����� 
	int fishing_EXP;//���㾭�� 
	//�������еȼ���������5�� 
	int farm_level;//ũ���ȼ� 
	int collect_level;//�ɼ��ȼ� 
	int fishing_level;//����ȼ� 
	const double corral_lucky[6] = { 0,0.5,0.7,0.7,1.0,1.0 };//��ֳ����ֵ 
	const double field_lucky[6] = { 0,0.5,0.5,0.8,0.8,1.5 };//��������ֵ 
	const double collect_speed[6] = { 0,1.0,1.5,1.5,2.0,2.0 };//�ɼ��ٶ�ϵ�� 
	const double collect_lucky[6] = { 0,0.5,0.5,0.8,0.8,1.5 };//�ɼ�����ֵ 
	const double fishing_success_rate[6] = { 0,0.5,0.5,0.7,0.7,1.0 };//����ɹ��� 
	const double fishing_lucky[6] = { 0,0.5,0.7,0.7,1.0,1.0 };//��������ֵ
	const int level_exp[6] = { -1,0,10,50,150,300 };//����� 
	Skill()
	{
		farm_EXP = 0;
		collect_EXP = 0;
		fishing_EXP = 0;
		farm_level = 1;
		collect_level = 1;
		fishing_level = 1;
	}//Ĭ�Ϲ��캯�� 
	Skill::Skill(int fa_exp, int co_exp, int fi_exp)//���浵�õĹ��캯�� 
	{
		farm_EXP = fa_exp;
		collect_EXP = co_exp;
		fishing_EXP = fi_exp;
		farm_level = 1;
		collect_level = 1;
		fishing_level = 1;
		update_level();//�ǵ�Ҫ�Ѿ���ֵ����һ�� 
	}
	static Skill* Skill::getInstance()
	{
		static Skill* res = new Skill;
		return res;
	}
	void Skill::update_level()
	{
		if (farm_level < 5)//���ũ���ȼ���û������ 
		{
			while (farm_EXP >= level_exp[farm_level + 1] && farm_level < 5)//���������Ը�����δ����
			{
				farm_level++;//ũ����ȼ����� 
			}
		}
		else
		{
			farm_EXP = level_exp[5];//�������������ޱ������ 
		}
		if (collect_level < 5)//����ɼ��ȼ���û������ 
		{
			while (collect_EXP >= level_exp[collect_level + 1] && collect_level < 5)//���������Ը�����δ����
			{
				collect_level++;//�ɼ��ȼ����� 
			}
		}
		else
		{
			collect_EXP = level_exp[5];//�������������ޱ������ 
		}
		if (fishing_level < 5)//�������ȼ���û������ 
		{
			while (fishing_EXP >= level_exp[fishing_level + 1] && fishing_level < 5)//���������Ը�����δ����
			{
				fishing_level++;//����ȼ����� 
			}
		}
		else
		{
			fishing_EXP = level_exp[5];//�������������ޱ������ 
		}
	}
	void add_farm_exp(int val)//����ũ������
	{
		farm_EXP += val;
		update_level();
	}
	void add_collect_exp(int val)//���Ӳɼ����� 
	{
		collect_EXP += val;
		update_level();
	}
	void add_fishing_exp(int val)//���ӵ��㾭��
	{
		fishing_EXP += val;
		update_level();
	}
	double get_corral_lucky()//��ȡ��ֳ����ֵ
	{
		return corral_lucky[farm_level];
	}
	double get_field_lucky()//��ȡ��������ֵ
	{
		return field_lucky[farm_level];
	}
	double get_collect_speed()//��ȡ�ɼ��ٶ�ϵ��
	{
		return collect_speed[collect_level];
	}
	double get_collect_lucky()//��ȡ�ɼ�����ֵ
	{
		return collect_lucky[collect_level];
	}
	double get_fishing_success_rate()//��ȡ����ɹ��� 
	{
		return fishing_success_rate[fishing_level];
	}
	double get_fishing_lucky()//��ȡ��������ֵ
	{
		return fishing_lucky[fishing_level];
	}
};