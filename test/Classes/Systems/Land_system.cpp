#include "Land_system.h"

Land::Land()//���캯�����г�ʼ�� 
{
	growth_time = 0;
	water_condition = 25;//��ʼˮΪ25 
	fertilizer_condition = 0;//��ʼû�з��� 
	planted_flag = false;
}
void Land::update_conditon(int now_season)//ÿ��״̬���º�������Ҫ�����ڷ������ʱִ�� 
{
	if (planted_flag == false)//���ֺ���и��� 
	{
		return;
	}
	//		cout<<"update"<<endl;
	if (plant.get_health() == 0)//���˾Ͳ�������
	{
		return;
	}
	Consumption now_consumption = plant.get_consumption();//�Ȼ�ȡ��ֲ������������� 
	//���¸���ȨֵӦ�����ü�������У�����ʱ������û��д����������¶�����Ȩֵ����
	double water_weight, fertilizer_weight, growth_speed;
	//		cout<<"now_season: "<<now_season<<endl;
	switch (now_season)
	{
		case 1:
			water_weight = 1, fertilizer_weight = 1, growth_speed = 1;//����Ȩ�� 
			break;
		case 2:
			water_weight = 2, fertilizer_weight = 2, growth_speed = 2;//����Ȩ�� 
			break;
		case 3:
			water_weight = 1.5, fertilizer_weight = 0.5, growth_speed = 1;//����Ȩ�� 
			break;
		case 4:
			water_weight = 0.5, fertilizer_weight = 0.5, growth_speed = 0.5;//����Ȩ�� 
			break;
	}
	now_consumption.fertilizer_consumption *= fertilizer_weight;//����Ȩ�ظ��������� 
	now_consumption.water_consumption *= water_weight;
	//		cout<<"fertilizer_condition: "<<fertilizer_condition<<endl;
	if (water_condition >= now_consumption.water_consumption && fertilizer_condition >= now_consumption.fertilizer_consumption && plant.get_illness() == false)//����������������Ҳ���������״̬ 
	{
		//			cout<<"health"<<endl;
		water_condition -= now_consumption.water_consumption;//����ˮ�ͷ��� 
		fertilizer_condition -= now_consumption.fertilizer_consumption;
		growth_time += growth_speed;//��������״̬
		int rand_val = rand();
		plant.set_health(10);//ÿ��ָ�10�㽡����������ϱߴ�����ˣ� 
		if (rand_val % 1111 == 1)
		{
			plant.set_illness(1);//���������1/1111�ļ������� 
		}
		return;
	}
	if (plant.get_illness() == true)//����״̬���� 
	{
		//����Ҳ������ˮ�ͷ��� 
		if (water_condition >= now_consumption.water_consumption)//���ˮ���� 
		{
			water_condition -= now_consumption.water_consumption;//����ˮ
		}
		if (fertilizer_condition >= now_consumption.fertilizer_consumption)//������ϻ��� 
		{
			fertilizer_condition -= now_consumption.fertilizer_consumption;//���ķ���
		}
		plant.set_health(-20);//ÿ�콡��-20 
		//			cout<<"health: "<<plant.get_health()<<endl;
		return;
	}
	if (water_condition < now_consumption.water_consumption || fertilizer_condition < now_consumption.fertilizer_consumption)//�����������������
	{
		int rand_weight = 2;
		//			cout<<water_condition<<" "<<fertilizer_condition<<endl;
		if (water_condition >= now_consumption.water_consumption)//���ˮ���� 
		{
			water_condition -= now_consumption.water_consumption;//����ˮ
			rand_weight--;//���Ȩ�ؽ��� 
		}
		if (fertilizer_condition >= now_consumption.fertilizer_consumption)//������ϻ��� 
		{
			fertilizer_condition -= now_consumption.fertilizer_consumption;//���ķ���
			rand_weight--;//���Ȩ�ؽ���
		}
		//�˴�ֲ�ﲻ�����Ҳ��ָ�����ֵ 
		int rand_val = rand();
		if (rand_val % (22 / rand_weight) == 1)
		{
			plant.set_illness(1);//��������������1/11�ļ������� 
		}
		//			plant.set_illness(1);
	}
}
bool Land::plant_seed(int seed)//���ֺ��� 
{
	if (planted_flag == true)
	{
		return false;//һ��ز����ظ��������� 
	}
	plant = prop_system.get_plant(seed + 10); //�˴����ձ�������ȡ���Ӷ�Ӧ�������� 
	planted_flag = true;//���µ�ǰΪֹ�Ĳ���״̬ 
	return true;
}
bool Land::add_medicine()//���ƺ��� 
{
	if (plant.get_illness() == true)//�в� 
	{
		plant.set_illness(false);//���� 
		return true;
	}
	return false;//û����Ϲ��ʲô 
}
bool Land::add_fertilizer(double fertilizer_num)//ʩ�ʺ���������ʩ���Ƿ�ɹ� 
{
	if (fertilizer_condition >= 100)//����������� 
	{
		return false;
	}
	else
	{
		fertilizer_condition += fertilizer_num;
		if (fertilizer_condition > 100)
		{
			fertilizer_condition = 100.0;
		}
		return true;
	}
}
bool Land::add_water(double water_num)//��ˮ���������ؽ�ˮ�Ƿ�ɹ� 
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
Harvest Land::get_harvest()//�ջ��� 
{
	Harvest empty_harvest = plant.get_harvest(false);
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
	if (plant.get_health() == 0)//����ջ������������ 
	{
		return empty_harvest;//����һ�����ջ� 
	}
	int growth_step = plant.get_growth_step(growth_time);//��ȡ�����׶� 
	if (growth_step < plant.get_max_step())//��û���ջ񼾽� 
	{
		//		cout<<"ztz22"<<endl;
		return plant.get_harvest(false);//������;�ջ��ֵ 
	}
	return plant.get_harvest(true);//���������ջ��ֵ 
}
out_info Land::get_info()//���ڸ�ǰ���ṩ�����õ���Ϣ 
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
	now_info.type = plant.get_type();
	if (plant.get_health() == 0)//����ֵΪ0 
	{
		now_info.death_flag = true;//����������� 
	}
	now_info.illness_flag = plant.get_illness();//�޸Ĳ������
	if (fertilizer_condition == 0)//ȱ������ 
	{
		now_info.fertilizer_flag = true;//�޸�ȱ���ϱ�� 
	}
	if (water_condition == 0)
	{
		now_info.water_flag = true;//�޸�ȱˮ��� 
	}
	//	cout<<"growth_time: "<<growth_time<<endl;
	now_info.step = plant.get_growth_step(growth_time);//�޸������׶� 
	return now_info;//����ǰ�������ֵ 
}