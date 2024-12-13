#include"map_system.h" 

class Corral//������ֲ�� 
{
	private:
		double water_condition;//ˮ״̬ 
		double food_condition;//����״̬
		bool planted_flag;//�Ƿ��Ѿ����֣���ֳ�� 
		double growth_time;//����ֳʱ��
		Prop_system prop_system;//��Ʒӳ��� 
		base_animal animal;//ֲ���࣬���ڴ�ŵ�ǰ�ؿ�����ֲ��ֲ�� 
	public:
		Corral();
		~Corral(){}
		void update_conditon();//���¶���״̬��������ÿ�쿪ʼʱִ�� 
		bool plant_seed(int seed);//��ֲ����������true��ʾ��ֳ�ɹ���falseΪ��ֳʧ�� 
		Harvest get_harvest();//�ջ���
		bool add_food(double food_num);//��ʳ����������ֵ�Ƿ���ʩ�� 
		bool add_water(double water_num);//��ˮ�����������ܷ��ˮ 
		bool add_medicine();//���ƺ��� 
		out_info get_info();//��ȡ���ڸ���ǰ�˵���Ϣ 
}; 
Corral::Corral()//���캯�����г�ʼ�� 
{
	growth_time=false;
	water_condition=0;//��ʼˮΪ0 
	food_condition=0;//��ʼû��ʳ�� 
}
void Corral::update_conditon()//ÿ��״̬���º�������Ҫ�����ڷ������ʱִ�� 
{
	if(planted_flag!=false)//��ֳ����и��� 
	{
		if(animal.get_health()==0)//���˾Ͳ������� 
		{
			return;
		} 
		Consumption now_consumption=animal.get_consumption();//�Ȼ�ȡ��ֳ�Ķ���������� 
		if(water_condition>=now_consumption.water_consumption&&food_condition>=now_consumption.food_consumption&&animal.get_illness()==false)//����������������Ҳ���������״̬ 
		{
			water_condition-=now_consumption.water_consumption;//����ˮ�ͷ��� 
			food_condition-=now_consumption.food_consumption;
			growth_time+=1;//��������״̬
			int rand_val=rand();
			animal.set_health(10);//ÿ��ָ�10�㽡����������ϱߴ�����ˣ� 
			if(rand_val%1111==1)
			{
				animal.set_illness(1);//���������1/1111�ļ������� 
			}
		}
		if(animal.get_illness()==true)//����״̬
		{
			//����Ҳ������ˮ�ͷ��� 
			if(water_condition>=now_consumption.water_consumption)//���ˮ���� 
			{
				water_condition-=now_consumption.water_consumption;//����ˮ
			} 
			if(food_condition>=now_consumption.food_consumption)//������ϻ��� 
			{
				food_condition-=now_consumption.food_consumption;//���ķ���
			}
			animal.set_health(-20);//ÿ�콡��-20 
		}
		if(water_condition<now_consumption.water_consumption||food_condition<now_consumption.food_consumption)//�����������������
		{
			int rand_weight=2;
			if(water_condition>=now_consumption.water_consumption)//���ˮ���� 
			{
				water_condition-=now_consumption.water_consumption;//����ˮ
				rand_weight--;//���Ȩ�ؽ��� 
			} 
			if(food_condition>=now_consumption.food_consumption)//���ʳ�ﻹ�� 
			{
				food_condition-=now_consumption.food_consumption;//����ʳ��
				rand_weight--;//���Ȩ�ؽ���
			}
			//�˴�ֲ�ﲻ�����Ҳ��ָ�����ֵ 
			int rand_val=rand();
			if(rand_val%(22/rand_weight)==1)
			{
				animal.set_illness(1);//��������������1/11�ļ������� 
			}
		}
	} 
}
bool Corral::plant_seed(int seed)//���ֺ��� 
{
	if(planted_flag==true)
	{
		return false;//һ��ز����ظ��������� 
	} 
	animal=prop_system.get_animal(seed+10); //�˴����ձ�������ȡ���Ӷ�Ӧ�������� 
	planted_flag=true;//���µ�ǰΪֹ�Ĳ���״̬ 
	return true;
}
bool Corral::add_medicine()//���ƺ��� 
{
	if(animal.get_illness()==true)//�в� 
	{
		animal.set_illness(false);//���� 
		return true; 
	}
	return false;//û����Ϲ��ʲô 
} 
bool Corral::add_food(double food_num)//ʩ�ʺ���������ʩ���Ƿ�ɹ� 
{
	if(food_condition>=100)//���ʳ������ 
	{
		return false;
	}
	else
	{
		food_condition+=food_num;
		if(food_condition>100)//����� 
		{
			food_condition=100.0;
		}
		return true;
	} 
}
bool Corral::add_water(double water_num)//��ˮ���������ؽ�ˮ�Ƿ�ɹ� 
{
	if(water_condition>=100)//���ˮ���� 
	{
		return false;
	}
	else
	{
		water_condition+=water_num;
		if(water_condition>100)//����� 
		{
			water_condition=100.0;
		}
		return true;
	} 
}
Harvest Corral::get_harvest()//�ջ��� 
{
	int growth_step=animal.get_growth_step(growth_time);
	planted_flag=false;//������ԭΪδ��ֳ��״̬ 
	if(growth_step<animal.get_max_step())//��û���ջ񼾽� 
	{
		return animal.get_harvest(false);//������;�ջ��ֵ 
	}
	return animal.get_harvest(true);//���������ջ��ֵ 
}
out_info Corral::get_info()//���ڸ�ǰ���ṩ�����õ���Ϣ 
{
	//��������ʼ������ֵ 
	out_info now_info;
	now_info.death_flag=false;
	now_info.fertilizer_flag=false;
	now_info.illness_flag=false;
	now_info.food_flag=false; 
	now_info.type=0;
	now_info.step=0;
	now_info.water_flag=false;
	if(planted_flag==false)//û���ֵĻ�
	{
		return now_info;//ֱ�ӷ���Ĭ��ֵ 
	}
	now_info.type=animal.get_type();
	if(animal.get_health()==0)//����ֵΪ0 
	{
		now_info.death_flag=true;//����������� 
	}
	now_info.illness_flag=animal.get_illness();//�޸Ĳ������
	if(food_condition==0)//ȱ��ʳ�� 
	{
		now_info.food_flag=true;//�޸�ȱʳ��
	} 
	if(water_condition==0)
	{
		now_info.water_flag=true;//�޸�ȱˮ��� 
	}
	now_info.step=animal.get_growth_step(growth_time);//�޸������׶� 
	return now_info;//����ǰ�������ֵ 
} 
