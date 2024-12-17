#pragma once
#include "map_system.h" 

class Corral//������ 
{
private:
	double water_condition;//ˮ״̬ 
	double food_condition;//ʳ��״̬
	bool planted_flag;//�Ƿ��Ѿ�����
	double growth_time;//������ʱ��
	Prop_system prop_system;//��Ʒӳ��� 
	base_animal animal;//ֲ���࣬���ڴ�ŵ�ǰ�ؿ�����ֲ��ֲ�� 
public:
	Corral();
	~Corral() {}
	void update_conditon();//��������״̬�������뼾���޹� 
	bool plant_seed(int seed);//��ֲ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
	Harvest get_harvest();//�ջ���
	bool add_food(double food_num);//ιʳ����������ֵ�Ƿ���ιʳ 
	bool add_water(double water_num);//��ˮ�����������ܷ�ˮ 
	bool add_medicine();//���ƺ��� 
	out_info get_info();//��ȡ���ڸ���ǰ�˵���Ϣ 
};
