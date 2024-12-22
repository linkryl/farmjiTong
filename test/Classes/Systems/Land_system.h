#pragma once
#include "cocos2d.h"
#include "map_system.h" 

class Land//������ֲ�� 
{
private:
	double water_condition;//ˮ״̬ 
	double fertilizer_condition;//����״̬
	bool planted_flag;//�Ƿ��Ѿ�����
	double growth_time;//������ʱ��
	Prop_system prop_system;//��Ʒӳ��� 
	base_plant plant;//ֲ���࣬���ڴ�ŵ�ǰ�ؿ�����ֲ��ֲ�� 
public:
	Land();
	~Land() {}
	void update_conditon(int now_season);//��������״̬������1��2��3��4�ֱ�Ϊ�����ﶬ����ÿ�쿪ʼʱִ�� 
	bool plant_seed(int seed);//��ֲ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
	Harvest get_harvest();//�ջ���
	bool add_fertilizer(double fertilizer_num);//ʩ�ʺ���������ֵ�Ƿ���ʩ�� 
	bool add_water(double water_num);//��ˮ�����������ܷ�ˮ 
	bool add_medicine();//���ƺ��� 
	out_info get_info();//��ȡ���ڸ���ǰ�˵���Ϣ 
};