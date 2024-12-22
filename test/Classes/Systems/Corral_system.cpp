#include "Corral_system.h"

Corral::Corral()//���캯�����г�ʼ�� 
{
	growth_time = 0;
	water_condition = 0;//��ʼˮΪ25 
	food_condition = 0;//��ʼû��ʳ�� 
	planted_flag = false;
}
void Corral::update_conditon()//ÿ��״̬���º�������Ҫ�����ڷ������ʱִ�� 
{
	if (planted_flag != false)//���ֺ���и��� 
	{
		//		cout<<"update"<<endl;
		if (animal.get_health() == 0)//���˾Ͳ�������
		{
			return;
		}
		Consumption now_consumption = animal.get_consumption();//�Ȼ�ȡ��ֲ������������� 
		//		cout<<"fertilizer_condition: "<<fertilizer_condition<<endl;
		if (water_condition >= now_consumption.water_consumption && food_condition >= now_consumption.food_consumption && animal.get_illness() == false)//����������������Ҳ���������״̬ 
		{
			//			cout<<"health"<<endl;
			water_condition -= now_consumption.water_consumption;//����ˮ��ʳ�� 
			food_condition -= now_consumption.food_consumption;
			growth_time += 1;//��������״̬
			int rand_val = rand();
			animal.set_health(10);//ÿ��ָ�10�㽡����������ϱߴ�����ˣ� 
			if (rand_val % 1111 == 1)
			{
				animal.set_illness(1);//���������1/1111�ļ������� 
			}
			return;
		}
		if (animal.get_illness() == true)//����״̬���� 
		{
			//����Ҳ������ˮ��ʳ�� 
			if (water_condition >= now_consumption.water_consumption)//���ˮ���� 
			{
				water_condition -= now_consumption.water_consumption;//����ˮ
			}
			if (food_condition >= now_consumption.food_consumption)//���ʳ�ﻹ�� 
			{
				food_condition -= now_consumption.food_consumption;//����ʳ��
			}
			animal.set_health(-20);//ÿ�콡��-20 
			//			cout<<"health: "<<plant.get_health()<<endl;
			return;
		}
		if (water_condition < now_consumption.water_consumption || food_condition < now_consumption.food_consumption)//�����������������
		{
			int rand_weight = 2;
			//			cout<<water_condition<<" "<<fertilizer_condition<<endl;
			if (water_condition >= now_consumption.water_consumption)//���ˮ���� 
			{
				water_condition -= now_consumption.water_consumption;//����ˮ
				rand_weight--;//���Ȩ�ؽ��� 
			}
			if (food_condition >= now_consumption.food_consumption)//���ʳ�ﻹ�� 
			{
				food_condition -= now_consumption.food_consumption;//����ʳ��
				rand_weight--;//���Ȩ�ؽ���
			}
			//�˴�ֲ�ﲻ�����Ҳ��ָ�����ֵ 
			int rand_val = rand();
			if (rand_val % (22 / rand_weight) == 1)
			{
				animal.set_illness(1);//��������������1/11�ļ������� 
			}
			//			plant.set_illness(1);
		}
	}
}
bool Corral::plant_seed(int seed)//���ֺ��� 
{
	if (planted_flag == true)
	{
		return false;//һ��ز����ظ��������� 
	}
	animal = prop_system.get_animal(seed + 10); //�˴����ձ�������ȡ���Ӷ�Ӧ�������� 
	planted_flag = true;//���µ�ǰΪֹ�Ĳ���״̬ 
	return true;
}
bool Corral::add_medicine()//���ƺ��� 
{
	if (animal.get_illness() == true)//�в� 
	{
		animal.set_illness(false);//���� 
		return true;
	}
	return false;//û����Ϲ��ʲô 
}
bool Corral::add_food(double food_num)//ιʳ����������ιʳ�Ƿ�ɹ� 
{
	if (food_condition >= 100)//���ʳ������ 
	{
		return false;
	}
	else
	{
		food_condition += food_num;
		if (food_condition > 100)
		{
			food_condition = 100.0;
		}
		return true;
	}
}
bool Corral::add_water(double water_num)//��ˮ���������ؽ�ˮ�Ƿ�ɹ� 
{
	if (water_condition >= 100)//���ˮ���� 
	{
		return false;
	}
	else
	{
		water_condition += water_num;
		if (water_condition > 100)
		{
			water_condition = 100.0;
		}
		return true;
	}
}
Harvest Corral::get_harvest()//�ջ��� 
{
	Harvest empty_harvest = animal.get_harvest(false);
	empty_harvest.harvest_type_a = -1;
	empty_harvest.harvest_type_b = -1;
	empty_harvest.max_harvest_num_a = 0;
	empty_harvest.max_harvest_num_b = 0;
	//	cout<<endl<<planted_flag<<endl; /
	if (planted_flag == false)//����������û�б����ֹ� 
	{
		return empty_harvest;//���ؿ��ջ� 
	}
	planted_flag = false;//���ػ�ԭΪδ���ֵ�״̬ 
	if (animal.get_health() == 0)//����ջ������������ 
	{
		return empty_harvest;//����һ�����ջ� 
	}
	int growth_step = animal.get_growth_step(growth_time);//��ȡ�����׶� 
	if (growth_step < animal.get_max_step())//��û���ջ񼾽� 
	{
		//		cout<<"ztz22"<<endl;
		return animal.get_harvest(false);//������;�ջ��ֵ 
	}
	return animal.get_harvest(true);//���������ջ��ֵ 
}
out_info Corral::get_info()//���ڸ�ǰ���ṩ�����õ���Ϣ 
{
	//��������ʼ������ֵ 
	out_info now_info;
	now_info.death_flag = false;
	now_info.fertilizer_flag = false;
	now_info.illness_flag = false;
	now_info.food_flag = false;
	now_info.type = 0;
	now_info.step = 0;
	now_info.water_flag = false;
	if (planted_flag == false)//û���ֵĻ�
	{
		return now_info;//ֱ�ӷ���Ĭ��ֵ 
	}
	now_info.type = animal.get_type();
	if (animal.get_health() == 0)//����ֵΪ0 
	{
		now_info.death_flag = true;//����������� 
	}
	now_info.illness_flag = animal.get_illness();//�޸Ĳ������
	if (food_condition == 0)//ȱ��ʳ�� 
	{
		now_info.food_flag = true;//�޸�ȱʳ���� 
	}
	if (water_condition == 0)
	{
		now_info.water_flag = true;//�޸�ȱˮ��� 
	}
	//	cout<<"growth_time: "<<growth_time<<endl;
	now_info.step = animal.get_growth_step(growth_time);//�޸������׶� 
	return now_info;//����ǰ�������ֵ 
}