//#include<cocos.h>
#include<iostream>
#include<cstdio>
//#include<unordered_map>
#include<map> 
#include<cstdlib>
using namespace std;

struct Harvest//�ջ�ṹ�� 
{
	int harvest_type;//�ջ�������
	int max_harvest_num;//�ջ������� 
	Harvest& operator =(const Harvest& other)//���ص��ں� 
	{
		if(this!=&other)
		{
			harvest_type=other.harvest_type;
			max_harvest_num=other.max_harvest_num;
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
	int *growth_time;//ÿ�ε�����ʱ�䣬ʹ��ǰ׺�ͽ��д洢 
	~Growth_time()//�����ж�̬���룬����Ҫд�������� 
	{
		if(growth_time!=NULL)
		{
			delete[] growth_time;
		}
	}
	Growth_time& operator = (const Growth_time& other)//���ص��ں� 
	{
		if(this!=&other)
		{
			if(growth_time==NULL)
			{
				delete[] growth_time;
			}
			level_num=other.level_num;
			growth_time=new int[level_num];
			for(int i=0;i<level_num;i++)
			{
				growth_time[i]=other.growth_time[i];
			}
		} 
		return *this;
	} 
};
//class base_plant:node//��û�зŵ������У��ȴ��� 
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
			empty.harvest_type=-1;
			empty.max_harvest_num=0;
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
	if(time>growth_time.growth_time[growth_time.level_num-1])
	{
		return growth_time.level_num-1;
	} 
	if(fresh_flag)
	{
		int l=0,r=growth_time.level_num;
		while(l<r)//���ֲ���Ѱ�Ҷ�Ӧ�׶� 
		{
			int mid=(l+r)/2;
			if(time>growth_time.growth_time[mid])
			{
				l=mid;
			}
			else
			{
				r=mid;
			}
		}
		return l+1;//�����±��0��ʼ������Ҫ+1 
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
		if(time_flag==true)
		{
			return base_farm::get_harvest(time_flag);//ʹ�û�����ջ��� 
		}
		else//ʱ�䲻���ͷ��صĻ�ʲô�������� 
		{
			Harvest harvest_seed;
//			empty.harvest_type=-1;//�˴�Ӧ�޸�Ϊ��Ӧ�������Ӷ�Ӧ�ı�ţ����ڻ�û��д���ȿ��� 
			harvest_seed.max_harvest_num=1;//��෵��һ������ 
			return harvest_seed;
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
		if(time_flag==true)
		{
			return base_farm::get_harvest(time_flag);//ʹ�û�����ջ��� 
		}
		else//ʱ�䲻���ͷ��صĻ�ʲô�������� 
		{
			Harvest harvest_young=base_farm::get_harvest(true);//���õ������������ 
			harvest_young.max_harvest_num=1;//��෵��һ���ջ���Ʒ 
			return harvest_young;
		}
	}
	//�˴�Ӧ���׳��쳣���ƣ�����û��������ôд 
}

//class plant_farm:node
class plant_farm//������ֲ�� 
{
	private:
		double water_condition;//ˮ״̬ 
		double fertilizer_condition;//����״̬
		bool hoed_flag;//�Ƿ񱻳��� 
		bool planted_flag;//�Ƿ��Ѿ�����
		double planted_time;//����ʱ��
		base_plant plant;//ֲ���࣬���ڴ�ŵ�ǰ�ؿ��� 
		int season;//ͬ��ʱ�����ϵļ��� 
	public:
		plant_farm();
		~plant_farm(){}
		void update_conditon(int now_weather);//��������״̬������1��2��3��4�ֱ�Ϊ�����ﶬ����ÿ�쿪ʼʱִ�� 
		int plant_seed(int seed);//��ֲ����������1��ʾ���ֳɹ���-1Ϊδ���أ�-2Ϊ�Ѿ����� 
		bool hoe_ground();//���غ���
		Harvest get_harvest();//�ջ���
		double add_fertilizer(double fertilizer_num);//ʩ�ʺ���������ֵΪ����ķ��� 
		double add_water(double water_num);//��ˮ����������ֵΪʣ���ˮ�� 
		bool add_medicine();//���ƺ���  
}; 
plant_farm::plant_farm()//���캯�����г�ʼ�� 
{
	hoed_flag=false;
	planted_time=false;
	water_condition=25;//��ʼˮΪ25 
	fertilizer_condition=0;//��ʼû�з��� 
}
void plant_farm::update_conditon(int now_weather)//ÿ��״̬���º�������Ҫ�����ڷ������ʱִ�� 
{
	if(planted_flag!=false)//���ֺ���и��� 
	{
		if(plant.get_health()==0)//���˾Ͳ������ˣ���Ҫ���³��� 
		{
			return;
		} 
		Consumption now_consumption=plant.get_consumption();//�Ȼ�ȡ��ֲ������������� 
		//���¸���ȨֵӦ�����ü�������У�����ʱ������û��д����������¶�����Ȩֵ����
		double water_weight,fertilizer_weight,growth_speed;
		switch(now_weather)
		{ 
			case 1:
				water_weight=1,fertilizer_weight=1,growth_speed=1;//����Ȩ�� 
				break;
			case 2:
				water_weight=2,fertilizer_weight=2,growth_speed=2;//����Ȩ�� 
				break;
			case 3:
				water_weight=1.5,fertilizer_weight=0.5,growth_speed=1;//����Ȩ�� 
				break;
			case 4:
				water_weight=0.5,fertilizer_weight=0.5,growth_speed=0.5;//����Ȩ�� 
				break;
		}
		now_consumption.fertilizer_consumption*=fertilizer_weight;//����Ȩ�ظ��������� 
		now_consumption.water_consumption*=water_weight;
		if(water_condition>=now_consumption.water_consumption&&fertilizer_condition>=now_consumption.fertilizer_consumption&&plant.get_illness()==false)//����������������Ҳ���������״̬ 
		{
			water_condition-=now_consumption.water_consumption;//����ˮ�ͷ��� 
			fertilizer_condition-=now_consumption.fertilizer_consumption;
			planted_time+=growth_speed;//��������״̬
			int rand_val=rand();
			plant.set_health(10);//ÿ��ָ�10�㽡����������ϱߴ�����ˣ� 
			if(rand_val%1111==1)
			{
				plant.set_illness(1);//���������1/1111�ļ������� 
			}
		}
		if(plant.get_illness()==true)//����״̬���� 
		{
			//����Ҳ������ˮ�ͷ��� 
			if(water_condition>=now_consumption.water_consumption)//���ˮ���� 
			{
				water_condition-=now_consumption.water_consumption;//����ˮ
			} 
			if(fertilizer_condition>=now_consumption.fertilizer_consumption)//������ϻ��� 
			{
				fertilizer_condition-=now_consumption.fertilizer_consumption;//���ķ���
			}
			plant.set_health(-20);//ÿ�콡��-20 
		}
		if(water_condition<now_consumption.water_consumption||fertilizer_condition<now_consumption.fertilizer_consumption)//�����������������
		{
			int rand_weight=2;
			if(water_condition>=now_consumption.water_consumption)//���ˮ���� 
			{
				water_condition-=now_consumption.water_consumption;//����ˮ
				rand_weight--;//���Ȩ�ؽ��� 
			} 
			if(fertilizer_condition>=now_consumption.fertilizer_consumption)//������ϻ��� 
			{
				fertilizer_condition-=now_consumption.fertilizer_consumption;//���ķ���
				rand_weight--;//���Ȩ�ؽ���
			}
			//�˴�ֲ�ﲻ�����Ҳ��ָ�����ֵ 
			int rand_val=rand();
			if(rand_val%(22/rand_weight)==1)
			{
				plant.set_illness(1);//��������������1/11�ļ������� 
			}
		}
		if(plant.get_health()==0)//���ֲ���Ѿ����� 
		{
			hoed_flag=false;//���ر�ǩ��ԭΪû���� 
		} 
	} 
}
bool plant_farm::hoe_ground()//���غ���
{
	if(hoed_flag==false)//���û���� 
	{
		hoed_flag=true;//����Ϊ�Ѿ����� 
		return true; 
	}
	return false;//���򷵻�false 
} 
int plant_farm::plant_seed(int seed)//���ֺ��� 
{
	if(hoed_flag==false)
	{
		return -1;//û�����ز��ܲ��� 
	} 
	if(planted_flag==true)
	{
		return -2;//һ��ز����ظ��������� 
	} 
	
//	plant= //�˴�Ϊʹ��map��ȡ���Ӷ�Ӧ�������������UI�ͱ�����û��д������ʱ����
	planted_flag=true;//���µ�ǰΪֹ�Ĳ���״̬ 
	return 1;
}
bool plant_farm::add_medicine()//���ƺ��� 
{
	if(plant.get_illness()==true)//�в� 
	{
		plant.set_illness(false);//���� 
		return true; 
	}
	return false;//û����Ϲ��ʲô 
} 
double plant_farm::add_fertilizer(double fertilizer_num)//ʩ�ʺ��� 
{
	if(fertilizer_condition+fertilizer_num>100)
	{
		double return_fertilizer=fertilizer_condition+fertilizer_num-100;//�������ķ���ֵ 
		fertilizer_condition=100;
		return return_fertilizer;
	}
	else
	{
		fertilizer_condition+=fertilizer_num;
		return 0;
	} 
}
double plant_farm::add_water(double water_num)//��ˮ���� 
{
	if(water_condition+water_num>100)
	{
		double return_water=water_condition+water_num-100;//��������ˮ�� 
		water_condition=100;
		return return_water;
	}
	else
	{
		water_condition+=water_num;
		return 0;
	} 
}
Harvest plant_farm::get_harvest()//�ջ��� 
{
	int growth_step=plant.get_growth_step(planted_time);
	if(growth_step<plant.get_max_step())//��û���ջ񼾽� 
	{
		return plant.get_harvest(false);//������;�ջ��ֵ 
	} 
	return plant.get_harvest(true);//���������ջ��ֵ 
} 
