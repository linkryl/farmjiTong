#include"Land_system.h"
class Farm_system//5x5���ص�ʵ�� 
{
	private:
		Land farm_land[5][5];//5x5������
		int base_add_x;//���Ͻ����ص����Ͻ�x���� 
		int base_add_y;//���Ͻ����ص����Ͻ�y���� 
	public:
		Farm_system* Farm_system::getInstance()
		{
			static Farm_system instance;
			return &instance;
		}  
		Farm_system();
		bool update_conditon(int x,int y,int day);//����ָ��λ�õ�����״̬����
		void update_all(int day);//�������ڸ������е����� 
		bool plant_seed(int seed,int x,int y);//��ֲ����������true��ʾ���ֳɹ���falseΪ����ʧ�� 
		Harvest get_harvest(int x,int y);//�ջ���
		bool add_fertilizer(double fertilizer_num,int x,int y);//ʩ�ʺ���������ֵ�Ƿ���ʩ�� 
		bool add_water(double water_num,int x,int y);//��ˮ�����������ܷ�ˮ 
		bool add_medicine(int x,int y);//���ƺ��� 
		out_info get_info(int x,int y);//��ȡ���ڸ���ǰ�˵���Ϣ
		void get_closest_land(int x,int y,int &add_x,int &add_y);//������ת��Ϊũ���±�
};
Farm_system::Farm_system()
{
	base_add_x=0;//������Ĭ��ֵŪ����0��ǰ��д�ú�ǵ��޸�
	base_add_y=0;
}
bool Farm_system::update_conditon(int x,int y,int day)//���ݵ�ǰ�������͵�ַ����ָ�������������� 
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
	if(add_x==-1||add_y==-1)//������ 
	{
		return false;//û���ܲ����� 
	} 
	int weather=day/90;
	weather%=4;//��ȡ���ڣ�����һ��360�죬ÿ������90�������� 
	weather++;
//	cout<<weather<<endl; 
	farm_land[add_x][add_y].update_conditon(weather);
}
void Farm_system::update_all(int day)//���ݵ�ǰ��������������ũ�� 
{
	int weather=day/90;
	weather%=4;//��ȡ���ڣ�����һ��360�죬ÿ������90�������� 
	weather++;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			farm_land[i][j].update_conditon(weather);//����ÿһ������ 
		}
	}
}
bool Farm_system::plant_seed(int seed,int x,int y)//���ֲ��� 
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
	if(add_x==-1||add_y==-1)//������ 
	{
		return false;//û���ܲ����� 
	} 
	return farm_land[add_x][add_y].plant_seed(seed);//���ж�ָ�����صĲ��ֲ��� 
}
Harvest Farm_system::get_harvest(int x,int y)//�ջ���
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
//	cout<<endl<<add_x<<" "<<add_y<<endl<<endl;
	if(add_x==-1||add_y==-1)//������ 
	{
		Harvest empty_harvest;
		empty_harvest.harvest_type_a=-1;
		empty_harvest.harvest_type_b=-1;
		empty_harvest.max_harvest_num_a=0;
		empty_harvest.max_harvest_num_b=0;
		return empty_harvest;//����һ�����ջ� 
	}
//	cout<<"ztz11"<<endl;
	return farm_land[add_x][add_y].get_harvest();
}
bool Farm_system::add_fertilizer(double fertilizer_num,int x,int y)//ʩ�ʺ��� 
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
	if(add_x==-1||add_y==-1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return farm_land[add_x][add_y].add_fertilizer(fertilizer_num);
}
bool Farm_system::add_water(double water_num,int x,int y)//��ˮ���� 
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
	if(add_x==-1||add_y==-1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return farm_land[add_x][add_y].add_water(water_num);
}
bool Farm_system::add_medicine(int x,int y)//���ƺ��� 
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
	if(add_x==-1||add_y==-1)//������ 
	{
		return false;//û���ܲ����� 
	}
	return farm_land[add_x][add_y].add_medicine();
}
out_info Farm_system::get_info(int x,int y)//��ȡ���ڸ���ǰ�˵���Ϣ
{
	int add_x,add_y;
	get_closest_land(x,y,add_x,add_y);//��ȡ�ܲ�����ũ�� 
	//��������ʼ�� 
	out_info now_info;
	now_info.death_flag=false;
	now_info.fertilizer_flag=false;
	now_info.illness_flag=false;
	now_info.food_flag=false; 
	now_info.type=0;
	now_info.step=0;
	now_info.water_flag=false;
	if(add_x==-1||add_y==-1)//������ 
	{
		return now_info;//���ؿ���Ϣ 
	}
	return farm_land[add_x][add_y].get_info();
}
void Farm_system::get_closest_land(int x,int y,int &add_x,int &add_y)//������ת��Ϊũ���±�
{
	//��ɽ�����λ����8���ڼ��ɽ��н��� 
	add_x=-1;
	add_y=-1;
	if(x<=(base_add_x-8)||x>=(base_add_x+72))//xԽ�� 
	{
		return;
	}
	if(y<=(base_add_x-8)||y>=(base_add_x+72))//yԽ�� 
	{
		return;
	}
	//��Խ��Ļ� 
	add_x=(x+8)/16;
	add_y=(y+8)/16;//�������������ȡֵ 
}
