#include "Livestock_farm_system.h"

Liverstock_farm_system::Liverstock_farm_system(int x, int y) : base_add_x(x), base_add_y(y)
{
	//������Ĭ��ֵŪ����0��ǰ��д�ú�ǵ��޸�
}
bool Liverstock_farm_system::update_conditon(int x, int y, int day)//���ݵ�ǰ�������͵�ַ����ָ�������������� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ��������� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	corral_land[add_x].update_conditon();
}
void Liverstock_farm_system::update_all()//������������ 
{
	for (int i = 0; i < 5; i++)
	{
		corral_land[i].update_conditon();//����ÿһ������ 
	}
}
bool Liverstock_farm_system::plant_seed(int seed, int x, int y)//���ֲ��� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return corral_land[add_x].plant_seed(seed);//���ж�ָ�����صĲ��ֲ��� 
}
Harvest Liverstock_farm_system::get_harvest(int x, int y)//�ջ���
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	//	cout<<endl<<add_x<<" "<<add_y<<endl<<endl;
	if (add_x == -1)//������ 
	{
		Harvest empty_harvest;
		empty_harvest.harvest_type_a = -1;
		empty_harvest.harvest_type_b = -1;
		empty_harvest.max_harvest_num_a = 0;
		empty_harvest.max_harvest_num_b = 0;
		return empty_harvest;//����һ�����ջ� 
	}
	//	cout<<"ztz11"<<endl;
	return corral_land[add_x].get_harvest();
}
bool Liverstock_farm_system::add_food(double food_num, int x, int y)//ιʳ���� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return corral_land[add_x].add_food(food_num);
}
bool Liverstock_farm_system::add_water(double water_num, int x, int y)//��ˮ���� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return corral_land[add_x].add_water(water_num);
}
bool Liverstock_farm_system::add_medicine(int x, int y)//���ƺ��� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return corral_land[add_x].add_medicine();
}
out_info Liverstock_farm_system::get_info(int x, int y)//��ȡ���ڸ���ǰ�˵���Ϣ
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	//��������ʼ�� 
	out_info now_info;
	now_info.death_flag = false;
	now_info.fertilizer_flag = false;
	now_info.illness_flag = false;
	now_info.food_flag = false;
	now_info.type = 0;
	now_info.step = 0;
	now_info.water_flag = false;
	if (add_x == -1)//������ 
	{
		return now_info;//���ؿ���Ϣ 
	}
	return corral_land[add_x].get_info();
}
void Liverstock_farm_system::get_closest_corral(int x, int y, int& add_x)//������ת��Ϊũ���±�
{
	//��ɽ�����λ����8���ڼ��ɽ��н��� 
	add_x = -1;
	if (x <= (base_add_x - 8) || x >= (base_add_x + 72))//xԽ�� 
	{
		return;
	}
	//��Խ��Ļ� 
	add_x = (x + 8) / 16;//�������������ȡֵ 
}