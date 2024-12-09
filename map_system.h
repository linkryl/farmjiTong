
#include<map>
#include"basic_plant_and_ground_class.h"

class Prop_system
{
	private:
		map<int,Harvest> Harvest_map;
		map<int,int> Seed_map;
		map<int,base_plant> Plant_map;
	public:
		Prop_system();
		Harvest get_harvset(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ���ջ���
		base_plant get_plant(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ������ 
};
Prop_system::Prop_system()
{
	//��Ʒӳ���������±��룺 
	//1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
	//1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ��� 
	//��ʼ���ջ����� 
	Harvest vegetable_harvest;
	Harvest corn_harvest;
	vegetable_harvest.harvest_type=1120;
	vegetable_harvest.max_harvest_num=1;
	corn_harvest.harvest_type=1121;
	corn_harvest.max_harvest_num=2;
	
	//��ʼ����������
	Growth_time vegetable_growth_time;
	Growth_time corn_growth_time;
	vegetable_growth_time.level_num=6;
	vegetable_growth_time.growth_time[0]=1;
	vegetable_growth_time.growth_time[1]=3;
	vegetable_growth_time.growth_time[2]=5;
	vegetable_growth_time.growth_time[3]=8;
	vegetable_growth_time.growth_time[4]=10;
	vegetable_growth_time.growth_time[5]=12;
	corn_growth_time.level_num=5;
	corn_growth_time.growth_time[0]=1;
	corn_growth_time.growth_time[1]=3;
	corn_growth_time.growth_time[2]=5;
	corn_growth_time.growth_time[3]=7;
	corn_growth_time.growth_time[4]=9;
	
	//��ʼ������������
	Consumption vegetable_consumption;
	Consumption corn_consumption;
	vegetable_consumption.fertilizer_consumption=2;
	vegetable_consumption.water_consumption=1;
	vegetable_consumption.food_consumption=0;
	corn_consumption.fertilizer_consumption=1;
	corn_consumption.water_consumption=2;
	corn_consumption.food_consumption=0;
	
	//��ʼ�������� 
	base_plant vegetable;
	base_plant corn;
	vegetable.set_all(vegetable_growth_time,vegetable_harvest,vegetable_consumption,1110);
	corn.set_all(corn_growth_time,corn_harvest,corn_consumption,1111);
	
	//������õĲ���ѹ��map
	Harvest_map.insert(std::make_pair(1100,vegetable_harvest));
	Harvest_map.insert(std::make_pair(1101,corn_harvest));
	Plant_map.insert(std::make_pair(1110,vegetable));
	Plant_map.insert(std::make_pair(1111,corn));
}
Harvest Prop_system::get_harvset(int num)
{
	std::map<int,Harvest>::iterator it;
	it=Harvest_map.find(num);
	if(it!=Harvest_map.end())
	{
		return it->second;
	}
}
base_plant Prop_system::get_plant(int num)
{
	std::map<int,base_plant>::iterator it;
	it=Plant_map.find(num);
	if(it!=Plant_map.end())
	{
		return it->second;
	}
} 

