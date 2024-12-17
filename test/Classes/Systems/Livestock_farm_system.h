#pragma once
#include "Corral_system.h"
class Liverstock_farm_system//5x5���ص�ʵ�� 
{
private:
	Corral corral_land[5];//1x5������ 
	int base_add_x;//���Ͻ����ص����Ͻ�x���� 
	int base_add_y;//���Ͻ����ص����Ͻ�y���� 
public:
	Liverstock_farm_system(int x = 0, int y = 0);
	bool update_conditon(int x, int y, int day);//����ָ��λ�õ�����״̬����
	void update_all();//�������е����� 
	bool plant_seed(int seed, int x, int y);//��ֳ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
	Harvest get_harvest(int x, int y);//�ջ���
	bool add_food(double fertilizer_num, int x, int y);//ιʳ����������ֵ�Ƿ���ιʳ 
	bool add_water(double water_num, int x, int y);//��ˮ�����������ܷ�ˮ 
	bool add_medicine(int x, int y);//���ƺ��� 
	out_info get_info(int x, int y);//��ȡ���ڸ���ǰ�˵���Ϣ
	void get_closest_corral(int x, int y, int& add_x);//������ת��Ϊ�����±�
};
