#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct Harvest//�ջ�ṹ�� 
{
	int harvest_type_a,harvest_type_b;//�ջ������࣬aΪ�ջ��bΪ���� 
	int max_harvest_num_a,max_harvest_num_b;//�ջ�������
	Harvest() {}
	Harvest(int type_a, int type_b, int num_a, int num_b) 
	{
		harvest_type_a = type_a, harvest_type_b = type_b;
		max_harvest_num_a = num_a, max_harvest_num_b = num_b;
	}
	Harvest& operator =(const Harvest& other)//���ص��ں� 
	{
		if(this!=&other)
		{
			harvest_type_a=other.harvest_type_a;
			max_harvest_num_a=other.max_harvest_num_a;
			harvest_type_b=other.harvest_type_b;
			max_harvest_num_b=other.max_harvest_num_b;
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
		if(this!=&other)
		{
			water_consumption=other.water_consumption;
			fertilizer_consumption=other.fertilizer_consumption;
			food_consumption=other.food_consumption;
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
		if(this!=&other)
		{
			level_num=other.level_num;
			for(int i=0;i<level_num;i++)
			{
				growth_time[i]=other.growth_time[i];
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
		base_farm(){fresh_flag=false;} 
		~base_farm(){}
		void set_all(Growth_time g_time,Harvest h,Consumption c,int now_type);//��ʼ�����������ڳ�ʼ���趨����������������湹�캯�� 
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
		bool is_fresh(){return fresh_flag;}
		base_farm& operator = (const base_farm& other)//���ص��ں� 
		{
			if(this!=&other)//��ֹ���Ҹ�ֵ 
			{
				growth_time=other.growth_time;
				harvest=other.harvest;
				consumption=other.consumption;
				plant_health=other.plant_health;
				illness=other.illness;
				fresh_flag=other.fresh_flag;
				type=other.type;
			}	
			return *this;
		}
}; 
void base_farm::set_all(Growth_time g_time,Harvest h,Consumption c,int now_type)//��ʼ��������ʵ�� 
{
	illness=false;//��ʼ�����ڼ���״̬ 
	plant_health=100;//�趨��ʼ������Ϊ100 
	growth_time=g_time;//������������и�ֵ
	harvest=h; 
	consumption=c;
	fresh_flag=true; //����ʼ��״̬��Ϊtrue 
	type=now_type;
	return;
}
int base_farm::get_type()//��ȡ��ǰ��Ʒ������
{
	return type;
}
Consumption base_farm::get_consumption()//��ȡ������ 
{
	if(fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		return consumption;
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}
void base_farm::set_consumption(Consumption now_consumption)//�趨������ 
{
	consumption=now_consumption;
}
Harvest base_farm::get_harvest(bool time_flag)//��ȡ�ջ����� 
{
	if(fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		if(time_flag==true)
		{
			return harvest; 
		}
		else//ʱ�䲻���ͷ��صĻ�ʲô����һ�����ջ� 
		{
			Harvest empty;
			empty.harvest_type_a=-1;
			empty.max_harvest_num_a=0;
			empty.harvest_type_b=-1;
			empty.max_harvest_num_b=0;
			return empty;
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
} 
int base_farm::get_health()//��ȡ����״̬ 
{
	if(fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		return plant_health;
	}
	return -1;
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}
void base_farm::set_health(int delta_health)//�趨����״̬ 
{
	if(plant_health==0)//����Ϊ0˵���Ѿ��������޷��ٵ����������ǽи�� 
	{
		return;
	}
	plant_health+=delta_health;//�Խ����Ƚ��е��� 
	if(plant_health>100)
	{
		plant_health=100;//��ֹ��� 
	} 
	if(plant_health<0)
	{
		plant_health=0;//��ֹ��� 
	} 
}
bool base_farm::get_illness()//��ȡ����״̬ 
{
	if(fresh_flag)//ȷ����ʼ���˲��ܷ��� 
	{
		return illness; 
	}
	 //�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}
void base_farm::set_illness(bool now_illness)//�趨����״̬
{
	illness=now_illness;
}
int base_farm::get_growth_step(double time)//��ȡ��ǰ�����׶� 
{
	if(fresh_flag)//���ֹ��Ĳ��ܻ�ȡ 
	{
		if(time>growth_time.growth_time[growth_time.level_num-1])
		{
			return growth_time.level_num;//�������е������׶Σ���Ϊ��������׶� 
		} 
		for(int i=0;i<growth_time.level_num;i++)//�������ǰ׺�ͻ�ȡ�����׶� 
		{
			if(growth_time.growth_time[i]>time)
			{
				return i;
			}
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}

class base_plant:public base_farm//�ɻ���ũ��������������ֲ���� 
{
	public:
		base_plant():base_farm(){};//Ĭ�Ϲ��캯�� 
		Harvest get_harvest(bool time_flag);//��д��ȡ�ջ����Ʒ���� 
		base_plant & operator = (const base_plant& other)
		{
			base_farm::operator = (other); 
			return *this; 
		}
};
Harvest base_plant::get_harvest(bool time_flag)//�ջ��� 
{
	if(is_fresh())//ȷ����ʼ���˲��ܷ��� 
	{
		Harvest now_harvest=base_farm::get_harvest(true);//�Ȼ�ȡ�ջ�ṹ�� 
		if(time_flag==true)//����ǳ�����ջ� 
		{
			return now_harvest;//ֱ�ӷ������е��ջ�ֵ 
		}
		else//ʱ�䲻����ֻ�������� 
		{
			now_harvest.max_harvest_num_a=0;//�ջ������
			now_harvest.max_harvest_num_b=1;//���ӵ���󷵻�ֵ���1 
			return now_harvest;
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}

class base_animal:public base_farm//�ɻ���ũ�������������Ķ����� 
{
	public:
		base_animal():base_farm(){};//Ĭ�Ϲ��캯�� 
		Harvest get_harvest(bool time_flag);//��д��ȡ�ջ����Ʒ���� 
		base_animal & operator = (const base_animal& other)
		{
			base_farm::operator = (other); 
			return *this; 
		}
};
Harvest base_animal::get_harvest(bool time_flag)//�ջ��� 
{
	if(is_fresh())//ȷ����ʼ���˲��ܷ��� 
	{
		Harvest now_harvest=base_farm::get_harvest(time_flag);//�Ȼ�ȡ�ջ�ṹ�� 
		if(time_flag==true)//����ǳ�����ջ� 
		{
			return now_harvest;//ֱ�ӷ������е��ջ�ֵ 
		}
		else//ʱ�䲻����ʲôҲ������ 
		{
			now_harvest.max_harvest_num_a=0;//�ջ������
			now_harvest.max_harvest_num_b=0;//���̵ķ���ֵ���� 
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}
