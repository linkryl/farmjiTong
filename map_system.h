
#include<map>
#include"basic_plant_and_animal_class.h"

struct out_info//���ݷ����� 
{
	int type;//��ʾ�������� 
	bool death_flag;//true��ʾ�����Ѿ����� 
	bool water_flag;//true��ʾ����ȱˮ 
	bool fertilizer_flag;//true��ʾ����ȱ�ٷ���
	bool illness_flag;//true��ʾ������������ 
	bool food_flag;//true��ʾ����ȱ��ʳ�� 
	int step;//��ʾ����������׶� 
}; 

class Prop_system
{
	private:
		map<int,Harvest> Harvest_map;
		map<int,base_plant> Plant_map;
		map<int,base_animal> Animal_map;
	public:
		Prop_system();
		Harvest get_harvset(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ���ջ���
		base_plant get_plant(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ������
		base_animal get_animal(int num);//���ڲ��һ�ȡ��Ŷ�Ӧ�Ķ��� 
};
Prop_system::Prop_system()
{
	//��Ʒӳ���������±��룺 
	//1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
	//1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ��� 
	//2110Ϊ��2100Ϊ���У�2120Ϊ���� 
	//��ʼ���ջ����� 
	Harvest vegetable_harvest;
	Harvest corn_harvest;
	Harvest pig_harvest;
	vegetable_harvest.harvest_type_a=1120;
	vegetable_harvest.max_harvest_num_a=1;
	vegetable_harvest.harvest_type_b=1100;
	vegetable_harvest.max_harvest_num_b=2;//�����ջ񷵻�2�� 
	corn_harvest.harvest_type_a=1121;
	corn_harvest.max_harvest_num_b=2;
	corn_harvest.harvest_type_b=1101;
	corn_harvest.max_harvest_num_b=2;//�����ջ񷵻�2�� 
	pig_harvest.harvest_type_a=2120;
	pig_harvest.max_harvest_num_a=3;
	pig_harvest.harvest_type_b=2100;
	pig_harvest.max_harvest_num_b=2;//�����ջ񷵻�2�� 
	
	//��ʼ����������
	Growth_time vegetable_growth_time;
	Growth_time corn_growth_time;
	Growth_time pig_growth_time;
	vegetable_growth_time.level_num=4;
	vegetable_growth_time.growth_time[0]=0;
	vegetable_growth_time.growth_time[1]=1;
	vegetable_growth_time.growth_time[2]=3;
	vegetable_growth_time.growth_time[3]=6;
	corn_growth_time.level_num=5;
	corn_growth_time.growth_time[0]=0;
	corn_growth_time.growth_time[1]=2;
	corn_growth_time.growth_time[2]=4;
	corn_growth_time.growth_time[3]=6;
	corn_growth_time.growth_time[4]=8;
	pig_growth_time.level_num=3;
	pig_growth_time.growth_time[0]=0;
	pig_growth_time.growth_time[1]=5;
	pig_growth_time.growth_time[2]=10;
	
	//��ʼ������������
	Consumption vegetable_consumption;
	Consumption corn_consumption;
	Consumption pig_consumption;
	vegetable_consumption.fertilizer_consumption=2;//�߲˲�����ʳ���ˮ2���ķ�2 
	vegetable_consumption.water_consumption=2;
	vegetable_consumption.food_consumption=0;
	corn_consumption.fertilizer_consumption=1;//���ﲻ����ʳ���ˮ2���ķ�1 
	corn_consumption.water_consumption=2;
	corn_consumption.food_consumption=0;
	pig_consumption.fertilizer_consumption=0;//�����ķ��ϣ���ˮ1����ʳ2 
	pig_consumption.water_consumption=1;
	pig_consumption.food_consumption=2;
	
	//��ʼ�������� 
	base_plant vegetable;
	base_plant corn;
	base_animal pig; 
	vegetable.set_all(vegetable_growth_time,vegetable_harvest,vegetable_consumption,1110);
	corn.set_all(corn_growth_time,corn_harvest,corn_consumption,1111);
	pig.set_all(pig_growth_time,pig_harvest,pig_consumption,2110);
	
	//������õĲ���ѹ��map
	Harvest_map.insert(std::make_pair(1100,vegetable_harvest));
	Harvest_map.insert(std::make_pair(1101,corn_harvest));
	Harvest_map.insert(std::make_pair(2101,pig_harvest));
	Plant_map.insert(std::make_pair(1110,vegetable));
	Plant_map.insert(std::make_pair(1111,corn));
	Animal_map.insert(std::make_pair(2110,pig));
	
	
	//����Ϊ���ɱ䲿�ֵ���Ʒmap
	Harvest stone_harvest;
	Harvest tree_harvest;
	Harvest ironstone_harvest;
	
	//��ʼ���ջ�����
	stone_harvest.harvest_type_a=3020;//��ʯ���3020 
	stone_harvest.max_harvest_num_a=2;//������2 
	stone_harvest.harvest_type_b=0;//�ջ�ṹ��ĵڶ���Ϊ�� 
	stone_harvest.max_harvest_num_b=0;
	tree_harvest.harvest_type_a=3021;//3021��ľͷ 
	tree_harvest.max_harvest_num_a=3;//������3 
	tree_harvest.harvest_type_b=0;//�ջ�ṹ��ĵڶ���Ϊ�� 
	tree_harvest.max_harvest_num_b=0; 
	ironstone_harvest.harvest_type_a=3022;//3022������ 
	ironstone_harvest.max_harvest_num_a=1;//������1 
	ironstone_harvest.harvest_type_b=0;//�ջ�ṹ��ĵڶ���Ϊ�� 
	ironstone_harvest.max_harvest_num_b=0; 
	
	//������õĲ���ѹ��map
	Harvest_map.insert(std::make_pair(3010,stone_harvest));//3010��ʯͷ
	Harvest_map.insert(std::make_pair(3011,stone_harvest));//3011����
	Harvest_map.insert(std::make_pair(3012,stone_harvest));//3012������ʯ 
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
base_animal Prop_system::get_animal(int num)
{
	std::map<int,base_animal>::iterator it;
	it=Animal_map.find(num);
	if(it!=Animal_map.end())
	{
		return it->second;
	}
}
