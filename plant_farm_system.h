#include"map_system.h" 
#include<cstdlib>
//class plant_farm:node
class plant_farm//������ֲ�� 
{
	private:
		double water_condition;//ˮ״̬ 
		double fertilizer_condition;//����״̬
		bool hoed_flag;//�Ƿ񱻳��� 
		bool planted_flag;//�Ƿ��Ѿ�����
		double planted_time;//����ʱ��
		Prop_system *prop_system;//��Ʒӳ��
//		const Time_system* time_system;
	public:
		plant_farm();
		~plant_farm(){}
		base_plant *plant;//ֲ���࣬���ڴ�ŵ�ǰ�ؿ��� 
//		void set_time(const Time_system* main_time);
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
	plant = new base_plant;
	prop_system = new Prop_system;
}
//void plant_farm::set_time(const Time_system* main_time)
//{
//	time_system=main_time;
//}
void plant_farm::update_conditon(int now_season)//ÿ��״̬���º�������Ҫ�����ڷ������ʱִ�� 
{
	if(planted_flag!=false)//���ֺ���и��� 
	{
		if(plant->get_health()==0)//���˾Ͳ������ˣ���Ҫ���³��� 
		{
			return;
		} 
		Consumption now_consumption=plant->get_consumption();//�Ȼ�ȡ��ֲ������������� 
		//���¸���ȨֵӦ�����ü�������У�����ʱ������û��д����������¶�����Ȩֵ����
		double water_weight,fertilizer_weight,growth_speed;
		switch(now_season)
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
		if(water_condition>=now_consumption.water_consumption&&fertilizer_condition>=now_consumption.fertilizer_consumption&&plant->get_illness()==false)//����������������Ҳ���������״̬ 
		{
			water_condition-=now_consumption.water_consumption;//����ˮ�ͷ��� 
			fertilizer_condition-=now_consumption.fertilizer_consumption;
			planted_time+=growth_speed;//��������״̬
			int rand_val=rand();
			plant->set_health(10);//ÿ��ָ�10�㽡����������ϱߴ�����ˣ� 
			if(rand_val%1111==1)
			{
				plant->set_illness(1);//���������1/1111�ļ������� 
			}
		}
		if(plant->get_illness()==true)//����״̬���� 
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
			plant->set_health(-20);//ÿ�콡��-20 
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
				plant->set_illness(1);//��������������1/11�ļ������� 
			}
		}
		if(plant->get_health()==0)//���ֲ���Ѿ����� 
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
	
	*plant=prop_system->get_plant(seed+10); //�˴����ձ�������ȡ���Ӷ�Ӧ�������� 
	planted_flag=true;//���µ�ǰΪֹ�Ĳ���״̬ 
	return 1;
}
bool plant_farm::add_medicine()//���ƺ��� 
{
	if(plant->get_illness()==true)//�в� 
	{
		plant->set_illness(false);//���� 
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
	int growth_step=plant->get_growth_step(planted_time);
	if(growth_step<plant->get_max_step())//��û���ջ񼾽� 
	{
		return plant->get_harvest(false);//������;�ջ��ֵ 
	} 
	return plant->get_harvest(true);//���������ջ��ֵ 
} 
