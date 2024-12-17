#include "basic_plant_and_animal_class.h"

void base_farm::set_all(Growth_time g_time, Harvest h, Consumption c, int now_type)//��ʼ��������ʵ�� 
{
	illness = false;//��ʼ�����ڼ���״̬ 
	plant_health = 100;//�趨��ʼ������Ϊ100 
	growth_time = g_time;//������������и�ֵ
	harvest = h;
	consumption = c;
	fresh_flag = true; //����ʼ��״̬��Ϊtrue 
	type = now_type;
	return;
}
int base_farm::get_type()//��ȡ��ǰ��Ʒ������
{
	return type;
}
Consumption base_farm::get_consumption()//��ȡ������ 
{
	if (fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		return consumption;
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
	return Consumption();
}
void base_farm::set_consumption(Consumption now_consumption)//�趨������ 
{
	consumption = now_consumption;
}
Harvest base_farm::get_harvest(bool time_flag)//��ȡ�ջ����� 
{
	if (fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		if (time_flag == true)
		{
			return harvest;
		}
		else//ʱ�䲻���ͷ��صĻ�ʲô����һ�����ջ� 
		{
			Harvest empty;
			empty.harvest_type_a = -1;
			empty.max_harvest_num_a = 0;
			empty.harvest_type_b = -1;
			empty.max_harvest_num_b = 0;
			return empty;
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
	return Harvest();
}
int base_farm::get_health()//��ȡ����״̬ 
{
	if (fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		return plant_health;
	}
	return -1;
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}
void base_farm::set_health(int delta_health)//�趨����״̬ 
{
	if (plant_health == 0)//����Ϊ0˵���Ѿ��������޷��ٵ����������ǽи�� 
	{
		return;
	}
	plant_health += delta_health;//�Խ����Ƚ��е��� 
	if (plant_health > 100)
	{
		plant_health = 100;//��ֹ��� 
	}
	if (plant_health < 0)
	{
		plant_health = 0;//��ֹ��� 
	}
}
bool base_farm::get_illness()//��ȡ����״̬ 
{
	if (fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		return illness;
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
	return false;
}
void base_farm::set_illness(bool now_illness)//�趨����״̬
{
	illness = now_illness;
}
int base_farm::get_growth_step(double time)//��ȡ��ǰ�����׶� 
{
	if (fresh_flag)//���ֹ��Ĳ��ܻ�ȡ 
	{
		if (time > growth_time.growth_time[growth_time.level_num - 1])
		{
			return growth_time.level_num;//�������е������׶Σ���Ϊ��������׶� 
		}
		for (int i = 0; i < growth_time.level_num; i++)//�������ǰ׺�ͻ�ȡ�����׶� 
		{
			if (growth_time.growth_time[i] > time)
			{
				return i;
			}
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
	return -1;
}


Harvest base_plant::get_harvest(bool time_flag)//�ջ��� 
{
	if (is_fresh())//ȷ����ʼ���˲��ܷ��� 
	{
		Harvest now_harvest = base_farm::get_harvest(true);//�Ȼ�ȡ�ջ�ṹ�� 
		if (time_flag == true)//����ǳ�����ջ� 
		{
			return now_harvest;//ֱ�ӷ������е��ջ�ֵ 
		}
		else//ʱ�䲻����ֻ�������� 
		{
			now_harvest.max_harvest_num_a = 0;//�ջ������
			now_harvest.max_harvest_num_b = 1;//���ӵ���󷵻�ֵ���1 
			return now_harvest;
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
	return Harvest();
}


Harvest base_animal::get_harvest(bool time_flag)//�ջ��� 
{
	if (is_fresh())//ȷ����ʼ���˲��ܷ��� 
	{
		Harvest now_harvest = base_farm::get_harvest(time_flag);//�Ȼ�ȡ�ջ�ṹ�� 
		if (time_flag == true)//����ǳ�����ջ� 
		{
			return now_harvest;//ֱ�ӷ������е��ջ�ֵ 
		}
		else//ʱ�䲻����ʲôҲ������ 
		{
			now_harvest.max_harvest_num_a = 0;//�ջ������
			now_harvest.max_harvest_num_b = 0;//���̵ķ���ֵ���� 
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
	return Harvest();
}