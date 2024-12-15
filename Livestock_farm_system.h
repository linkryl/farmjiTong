#include"Corral_system.h"
class Liverstock_farm_system//5x5耕地的实现 
{
	private:
		Corral corral_land[5];//1x5的畜栏 
		int base_add_x;//左上角土地的左上角x坐标 
		int base_add_y;//左上角土地的左上角y坐标 
	public:
		Liverstock_farm_system();
		bool update_conditon(int x,int y,int day);//更新指定位置的作物状态函数
		void update_all();//更新所有的畜栏 
		bool plant_seed(int seed,int x,int y);//养殖函数，返回true表示播种成功，false为播种失败 
		Harvest get_harvest(int x,int y);//收获函数
		bool add_food(double fertilizer_num,int x,int y);//喂食函数，返回值是否能喂食 
		bool add_water(double water_num,int x,int y);//浇水函数，返回能否浇水 
		bool add_medicine(int x,int y);//治疗函数 
		out_info get_info(int x,int y);//获取用于更新前端的信息
		void get_closest_corral(int x,int y,int &add_x);//将坐标转化为畜栏下标
};
Liverstock_farm_system::Liverstock_farm_system()
{
	base_add_x=0;//我这里默认值弄成了0，前端写好后记得修改
	base_add_y=0;
}
bool Liverstock_farm_system::update_conditon(int x,int y,int day)//根据当前的天数和地址进行指定坐标的作物更新 
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的畜栏 
	if(add_x==-1)//如果溢出 
	{
		return false;//没有能操作的 
	} 
	corral_land[add_x].update_conditon();
}
void Liverstock_farm_system::update_all()//更新所有畜栏 
{
	for(int i=0;i<5;i++)
	{
		corral_land[i].update_conditon();//更新每一块土地 
	}
}
bool Liverstock_farm_system::plant_seed(int seed,int x,int y)//播种操作 
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的农田 
	if(add_x==-1)//如果溢出 
	{
		return false;//没有能操作的 
	} 
	return corral_land[add_x].plant_seed(seed);//进行对指定土地的播种操作 
}
Harvest Liverstock_farm_system::get_harvest(int x,int y)//收获函数
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的农田 
//	cout<<endl<<add_x<<" "<<add_y<<endl<<endl;
	if(add_x==-1)//如果溢出 
	{
		Harvest empty_harvest;
		empty_harvest.harvest_type_a=-1;
		empty_harvest.harvest_type_b=-1;
		empty_harvest.max_harvest_num_a=0;
		empty_harvest.max_harvest_num_b=0;
		return empty_harvest;//返回一个空收获 
	}
//	cout<<"ztz11"<<endl;
	return corral_land[add_x].get_harvest();
}
bool Liverstock_farm_system::add_food(double food_num,int x,int y)//喂食函数 
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的农田 
	if(add_x==-1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	return corral_land[add_x].add_food(food_num);
}
bool Liverstock_farm_system::add_water(double water_num,int x,int y)//浇水函数 
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的农田 
	if(add_x==-1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	return corral_land[add_x].add_water(water_num);
}
bool Liverstock_farm_system::add_medicine(int x,int y)//治疗函数 
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的农田 
	if(add_x==-1)//如果溢出 
	{
		return false;//没有能操作的 
	}
	return corral_land[add_x].add_medicine();
}
out_info Liverstock_farm_system::get_info(int x,int y)//获取用于更新前端的信息
{
	int add_x;
	get_closest_corral(x,y,add_x);//获取能操作的农田 
	//声明并初始化 
	out_info now_info;
	now_info.death_flag=false;
	now_info.fertilizer_flag=false;
	now_info.illness_flag=false;
	now_info.food_flag=false; 
	now_info.type=0;
	now_info.step=0;
	now_info.water_flag=false;
	if(add_x==-1)//如果溢出 
	{
		return now_info;//返回空信息 
	}
	return corral_land[add_x].get_info();
}
void Liverstock_farm_system::get_closest_corral(int x,int y,int &add_x)//将坐标转化为农田下标
{
	//与可交互点位置在8以内即可进行交互 
	add_x=-1;
	if(x<=(base_add_x-8)||x>=(base_add_x+72))//x越界 
	{
		return;
	}
	//不越界的话 
	add_x=(x+8)/16;//进行四舍五入的取值 
}
