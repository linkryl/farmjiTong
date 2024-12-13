#ifndef ztz11
#define ztz11
#include<iostream>
#include<cstdio>
using namespace std;
#endif
class Skill{
	private:
		//经验无上限，但是在之后会进行归零至经验表上限避免爆int 
		int farm_EXP;//农场经验 
		int collect_EXP;//采集经验 
		int fishing_EXP;//钓鱼经验 
		//以下所有等级的上限是5级 
		int farm_level;//农场等级 
		int collect_level;//采集等级 
		int fishing_level;//钓鱼等级 
		const double corral_lucky[6]={0,1.0,1.4,1.4,2.0,2.0};//养殖幸运值 
		const double field_lucky[6]={0,1,1,1.6,1.6,3.0};//耕种幸运值 
		const double collect_speed[6]={0,1.0,1.5,1.5,2.0,2.0};//采集速度系数 
		const double collect_lucky[6]={0,1.0,1.0,1.6,1.6,3.0};//采集幸运值 
		const double fishing_success_rate[6]={0,0.5,0.5,0.7,0.7,1.0};//钓鱼成功率 
		const double fishing_lucky[6]={0,1.0,1.4,1.4,2.0,2.0};//钓鱼幸运值
		const int level_exp[6]={-1,0,10,50,150,300};//经验表 
	public:
		Skill();//默认构造函数 
		Skill(int fa_exp,int co_exp,int fi_exp);//读存档用的构造函数 
		void update_level();//根据当前经验更新等级 
		void add_farm_exp(int val)//增加农场经验
		{
			farm_EXP+=val;
			update_level();
		}
		void add_collect_exp(int val)//增加采集经验 
		{
			collect_EXP+=val;
			update_level();
		}
		void add_fishing_exp(int val)//增加钓鱼经验
		{
			fishing_EXP+=val;
			update_level();
		}
		double get_corral_lucky()//获取养殖幸运值
		{
			return corral_lucky[farm_level];
		}
		double get_field_lucky()//获取耕种幸运值
		{
			return field_lucky[farm_level];
		}
		double get_collect_speed()//获取采集速度系数
		{
			return collect_speed[collect_level];
		}
		double get_collect_lucky()//获取采集幸运值
		{
			return collect_lucky[collect_level];
		}
		double get_fishing_success_rate()//获取钓鱼成功率 
		{
			return fishing_success_rate[fishing_level];
		}
		double get_fishing_lucky()//获取钓鱼幸运值
		{
			return fishing_lucky[fishing_level];
		}
		int get_farm_level()//获取农场等级
		{
			return farm_level; 
		} 
		int get_collect_level()//获取采集等级
		{
			return collect_level; 
		} 
		int get_fishing_level()//获取钓鱼等级
		{
			return fishing_level; 
		} 
};
Skill::Skill()//默认构造函数 
{
	farm_EXP=0;
	collect_EXP=0;
	fishing_EXP=0;
	farm_level=1;
	collect_level=1;
	fishing_level=1;
}
Skill::Skill(int fa_exp,int co_exp,int fi_exp)//读存档用的构造函数 
{
	farm_EXP=fa_exp;
	collect_EXP=co_exp;
	fishing_EXP=fi_exp;
	farm_level=1;
	collect_level=1;
	fishing_level=1;
	update_level();//记得要把经验值更新一下 
}
void Skill::update_level()
{
	if(farm_level<5)//如果农场等级还没有满级 
	{
		while(farm_EXP>=level_exp[farm_level+1]&&farm_level<5)//如果经验可以更新且未满级
		{
			farm_level++;//农作物等级提升 
		}
	}
	else
	{
		farm_EXP=level_exp[5];//回退至经验上限避免溢出 
	}
	if(collect_level<5)//如果采集等级还没有满级 
	{
		while(collect_EXP>=level_exp[collect_level+1]&&collect_level<5)//如果经验可以更新且未满级
		{
			collect_level++;//采集等级提升 
		}
	}
	else
	{
		collect_EXP=level_exp[5];//回退至经验上限避免溢出 
	}
	if(fishing_level<5)//如果钓鱼等级还没有满级 
	{
		while(fishing_EXP>=level_exp[fishing_level+1]&&fishing_level<5)//如果经验可以更新且未满级
		{
			fishing_level++;//钓鱼等级提升 
		}
	}
	else
	{
		fishing_EXP=level_exp[5];//回退至经验上限避免溢出 
	}
} 
