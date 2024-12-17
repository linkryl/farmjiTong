#ifndef FARM_SYSTEM_H
#define FARM_SYSTEM_H

#include "Land_system.h"
#include "../Utils/MapUtil.h"

class Farm_system//5x5���ص�ʵ�� 
{
private:
	Land farm_land[5][5];//5x5������
	int base_add_x;//���½����ص����½�x���� 
	int base_add_y;//���½����ص����½�y���� 
public:
	Farm_system(int x = 0, int y = 0);
	bool update_conditon(int x, int y, int day);//����ָ��λ�õ�����״̬����
	void update_all(int day);//�������ڸ������е����� 
	bool plant_seed(int seed, int x, int y);//��ֲ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
	Harvest get_harvest(int x, int y);//�ջ���
	bool add_fertilizer(double fertilizer_num, int x, int y);//ʩ�ʺ���������ֵ�Ƿ���ʩ�� 
	bool add_water(double water_num, int x, int y);//��ˮ�����������ܷ�ˮ 
	bool add_medicine(int x, int y);//���ƺ��� 
	out_info get_info(int x, int y);//��ȡ���ڸ���ǰ�˵���Ϣ
	void get_closest_land(int x, int y, int& add_x, int& add_y);//������ת��Ϊũ���±�
};


#endif