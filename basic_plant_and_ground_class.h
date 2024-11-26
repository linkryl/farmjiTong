//#include<cocos.h>
#include<iostream>
#include<cstdio>
//#include<unordered_map>
#include<map> 
#include<cstdlib>
using namespace std;

struct Harvest//收获结构体 
{
	int harvest_type;//收获物种类
	int max_harvest_num;//收获的最大量 
	Harvest& operator =(const Harvest& other)//重载等于号 
	{
		if(this!=&other)
		{
			harvest_type=other.harvest_type;
			max_harvest_num=other.max_harvest_num;
		}
		return *this;
	}
}; 
struct Consumption//消耗量结构体
{ 
	double water_consumption;//耗水量
	double fertilizer_consumption;//肥料消耗量
	double food_consumption;//食物消耗量
	Consumption& operator = (const Consumption& other)//重载等于号 
	{
		if(this!=&other)
		{
			water_consumption=other.water_consumption;
			fertilizer_consumption=other.fertilizer_consumption;
			food_consumption=other.food_consumption;
		}	
		return *this;
	}
}; 
struct Growth_time//生长耗时结构体 
{
	int level_num;//生长的阶段数
	int *growth_time;//每段的消耗时间，使用前缀和进行存储 
	~Growth_time()//由于有动态申请，所以要写析构函数 
	{
		if(growth_time!=NULL)
		{
			delete[] growth_time;
		}
	}
	Growth_time& operator = (const Growth_time& other)//重载等于号 
	{
		if(this!=&other)
		{
			if(growth_time==NULL)
			{
				delete[] growth_time;
			}
			level_num=other.level_num;
			growth_time=new int[level_num];
			for(int i=0;i<level_num;i++)
			{
				growth_time[i]=other.growth_time[i];
			}
		} 
		return *this;
	} 
};
//class base_plant:node//还没有放到引擎中，先打标记 
class base_farm//一切可养殖/种植的物品基类 
{
	private:
		Growth_time growth_time;//生长耗时 
		Harvest harvest;//收获物品 
		Consumption consumption;//消耗量 
		int plant_health;//健康状态,0-100
		bool illness;//疾病状态
		bool fresh_flag;//是否已经完成初始化
		int type;//存储自身种类 
	public:
		base_farm(){fresh_flag=false;} 
		~base_farm(){}
		void set_all(Growth_time g_time,Harvest h,Consumption c,int now_type);//初始化函数，由于初始化设定过多所以用这个代替构造函数 
		Consumption get_consumption();//获取消耗信息 
		void set_consumption(Consumption now_consumption);//设定消耗信息
		virtual Harvest get_harvest(bool time_flag);//获取收获的物品
		int get_health();//获取健康状态
		void set_health(int delta_health);//设定（加减）健康状态
		bool get_illness();//获取当前的疾病状态
		void set_illness(bool now_illness);//设定疾病状态
		int get_growth_step(double time);//获取当前生长阶段 
		int get_max_step()//返回可达到的生长最高阶段 
		{
			return growth_time.level_num; 
		}
		int get_type();//获取当前物品的种类 
		bool is_fresh(){return fresh_flag;}
		base_farm& operator = (const base_farm& other)//重载等于号 
		{
			if(this!=&other)//防止自我赋值 
			{
				growth_time=other.growth_time;
				harvest=other.harvest;
				consumption=other.consumption;
				plant_health=other.plant_health;
				illness=other.illness;
				fresh_flag=other.fresh_flag;
				type=other.type;
			}	
			return *this;
		}
}; 
void base_farm::set_all(Growth_time g_time,Harvest h,Consumption c,int now_type)//初始化函数的实现 
{
	illness=false;//初始不处于疾病状态 
	plant_health=100;//设定初始健康度为100 
	growth_time=g_time;//逐个将参数进行赋值
	harvest=h; 
	consumption=c;
	fresh_flag=true; //将初始化状态置为true 
	type=now_type;
	return;
}
Consumption base_farm::get_consumption()//获取消耗量 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		return consumption;
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_consumption(Consumption now_consumption)//设定消耗量 
{
	consumption=now_consumption;
}
Harvest base_farm::get_harvest(bool time_flag)//获取收获物资 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		if(time_flag==true)
		{
			return harvest; 
		}
		else//时间不够就返回的话什么返回一个空收获 
		{
			Harvest empty;
			empty.harvest_type=-1;
			empty.max_harvest_num=0;
			return empty;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
} 
int base_farm::get_health()//获取健康状态 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		return plant_health;
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_health(int delta_health)//设定健康状态 
{
	if(plant_health==0)//健康为0说明已经死亡，无法再调整（否则那叫复活） 
	{
		return;
	}
	plant_health+=delta_health;//对健康度进行调整 
	if(plant_health>100)
	{
		plant_health=100;//防止溢出 
	} 
	if(plant_health<0)
	{
		plant_health=0;//防止溢出 
	} 
}
bool base_farm::get_illness()//获取疾病状态 
{
	if(fresh_flag)//确保初始化了才能返回 
	{
		return illness; 
	}
	 //此处应有抛出异常机制，但是没决定好怎么写 
}
void base_farm::set_illness(bool now_illness)//设定疾病状态
{
	illness=now_illness;
}
int base_farm::get_growth_step(double time)//获取当前生长阶段 
{
	if(time>growth_time.growth_time[growth_time.level_num-1])
	{
		return growth_time.level_num-1;
	} 
	if(fresh_flag)
	{
		int l=0,r=growth_time.level_num;
		while(l<r)//二分查找寻找对应阶段 
		{
			int mid=(l+r)/2;
			if(time>growth_time.growth_time[mid])
			{
				l=mid;
			}
			else
			{
				r=mid;
			}
		}
		return l+1;//数组下标从0开始，这里要+1 
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}

class base_plant:public base_farm//由基本农场类派生而来的植物类 
{
	public:
		base_plant():base_farm(){};//默认构造函数 
		Harvest get_harvest(bool time_flag);//重写获取收获的物品函数 
		base_plant & operator = (const base_plant& other)
		{
			base_farm::operator = (other); 
			return *this; 
		}
};
Harvest base_plant::get_harvest(bool time_flag)//收获函数 
{
	if(is_fresh())//确保初始化了才能返回 
	{
		if(time_flag==true)
		{
			return base_farm::get_harvest(time_flag);//使用基类的收获函数 
		}
		else//时间不够就返回的话什么都不返回 
		{
			Harvest harvest_seed;
//			empty.harvest_type=-1;//此处应修改为对应作物种子对应的编号，由于还没有写就先空下 
			harvest_seed.max_harvest_num=1;//最多返还一个种子 
			return harvest_seed;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}

class base_animal:public base_farm//由基本农场类派生而来的动物类 
{
	public:
		base_animal():base_farm(){};//默认构造函数 
		Harvest get_harvest(bool time_flag);//重写获取收获的物品函数 
		base_animal & operator = (const base_animal& other)
		{
			base_farm::operator = (other); 
			return *this; 
		}
};
Harvest base_animal::get_harvest(bool time_flag)//收获函数 
{
	if(is_fresh())//确保初始化了才能返回 
	{
		if(time_flag==true)
		{
			return base_farm::get_harvest(time_flag);//使用基类的收获函数 
		}
		else//时间不够就返回的话什么都不返回 
		{
			Harvest harvest_young=base_farm::get_harvest(true);//先拿到基类的总数居 
			harvest_young.max_harvest_num=1;//最多返还一个收获物品 
			return harvest_young;
		}
	}
	//此处应有抛出异常机制，但是没决定好怎么写 
}

//class plant_farm:node
class plant_farm//土地种植类 
{
	private:
		double water_condition;//水状态 
		double fertilizer_condition;//肥料状态
		bool hoed_flag;//是否被锄过 
		bool planted_flag;//是否已经播种
		double planted_time;//生长时间
		base_plant plant;//植物类，用于存放当前地块上 
		int season;//同步时间线上的季节 
	public:
		plant_farm();
		~plant_farm(){}
		void update_conditon(int now_weather);//更新作物状态函数，1，2，3，4分别为春夏秋冬，在每天开始时执行 
		int plant_seed(int seed);//种植函数，返回1表示播种成功，-1为未锄地，-2为已经播种 
		bool hoe_ground();//锄地函数
		Harvest get_harvest();//收获函数
		double add_fertilizer(double fertilizer_num);//施肥函数，返回值为多余的肥量 
		double add_water(double water_num);//浇水函数，返回值为剩余的水量 
		bool add_medicine();//治疗函数  
}; 
plant_farm::plant_farm()//构造函数进行初始化 
{
	hoed_flag=false;
	planted_time=false;
	water_condition=25;//初始水为25 
	fertilizer_condition=0;//初始没有肥料 
}
void plant_farm::update_conditon(int now_weather)//每日状态更新函数，需要在日期发生变更时执行 
{
	if(planted_flag!=false)//播种后才有更新 
	{
		if(plant.get_health()==0)//死了就不更新了，需要重新锄地 
		{
			return;
		} 
		Consumption now_consumption=plant.get_consumption();//先获取种植的作物的消耗量 
		//以下更新权值应当利用季节类进行，但是时间总线没有写，所以用裸露在外的权值代替
		double water_weight,fertilizer_weight,growth_speed;
		switch(now_weather)
		{ 
			case 1:
				water_weight=1,fertilizer_weight=1,growth_speed=1;//春天权重 
				break;
			case 2:
				water_weight=2,fertilizer_weight=2,growth_speed=2;//夏天权重 
				break;
			case 3:
				water_weight=1.5,fertilizer_weight=0.5,growth_speed=1;//秋天权重 
				break;
			case 4:
				water_weight=0.5,fertilizer_weight=0.5,growth_speed=0.5;//冬天权重 
				break;
		}
		now_consumption.fertilizer_consumption*=fertilizer_weight;//根据权重更新消耗量 
		now_consumption.water_consumption*=water_weight;
		if(water_condition>=now_consumption.water_consumption&&fertilizer_condition>=now_consumption.fertilizer_consumption&&plant.get_illness()==false)//如果满足消耗需求且不属于生病状态 
		{
			water_condition-=now_consumption.water_consumption;//消耗水和肥料 
			fertilizer_condition-=now_consumption.fertilizer_consumption;
			planted_time+=growth_speed;//更新生长状态
			int rand_val=rand();
			plant.set_health(10);//每天恢复10点健康（溢出在上边处理过了） 
			if(rand_val%1111==1)
			{
				plant.set_illness(1);//正常情况有1/1111的几率生病 
			}
		}
		if(plant.get_illness()==true)//生病状态仍在 
		{
			//病了也会消耗水和肥料 
			if(water_condition>=now_consumption.water_consumption)//如果水还够 
			{
				water_condition-=now_consumption.water_consumption;//消耗水
			} 
			if(fertilizer_condition>=now_consumption.fertilizer_consumption)//如果肥料还够 
			{
				fertilizer_condition-=now_consumption.fertilizer_consumption;//消耗肥料
			}
			plant.set_health(-20);//每天健康-20 
		}
		if(water_condition<now_consumption.water_consumption||fertilizer_condition<now_consumption.fertilizer_consumption)//如果不满足消耗需求
		{
			int rand_weight=2;
			if(water_condition>=now_consumption.water_consumption)//如果水还够 
			{
				water_condition-=now_consumption.water_consumption;//消耗水
				rand_weight--;//随机权重降低 
			} 
			if(fertilizer_condition>=now_consumption.fertilizer_consumption)//如果肥料还够 
			{
				fertilizer_condition-=now_consumption.fertilizer_consumption;//消耗肥料
				rand_weight--;//随机权重降低
			}
			//此处植物不生长且不恢复健康值 
			int rand_val=rand();
			if(rand_val%(22/rand_weight)==1)
			{
				plant.set_illness(1);//不正常情况有最高1/11的几率生病 
			}
		}
		if(plant.get_health()==0)//如果植物已经死了 
		{
			hoed_flag=false;//锄地标签还原为没锄过 
		} 
	} 
}
bool plant_farm::hoe_ground()//锄地函数
{
	if(hoed_flag==false)//如果没锄过 
	{
		hoed_flag=true;//更新为已经锄过 
		return true; 
	}
	return false;//否则返回false 
} 
int plant_farm::plant_seed(int seed)//播种函数 
{
	if(hoed_flag==false)
	{
		return -1;//没锄过地不能播种 
	} 
	if(planted_flag==true)
	{
		return -2;//一块地不能重复播种两次 
	} 
	
//	plant= //此处为使用map获取种子对应的作物，由于由于UI和背包还没有写所以暂时跳过
	planted_flag=true;//更新当前为止的播种状态 
	return 1;
}
bool plant_farm::add_medicine()//治疗函数 
{
	if(plant.get_illness()==true)//有病 
	{
		plant.set_illness(false);//就治 
		return true; 
	}
	return false;//没病你瞎治什么 
} 
double plant_farm::add_fertilizer(double fertilizer_num)//施肥函数 
{
	if(fertilizer_condition+fertilizer_num>100)
	{
		double return_fertilizer=fertilizer_condition+fertilizer_num-100;//计算多余的肥料值 
		fertilizer_condition=100;
		return return_fertilizer;
	}
	else
	{
		fertilizer_condition+=fertilizer_num;
		return 0;
	} 
}
double plant_farm::add_water(double water_num)//浇水函数 
{
	if(water_condition+water_num>100)
	{
		double return_water=water_condition+water_num-100;//计算多余的水量 
		water_condition=100;
		return return_water;
	}
	else
	{
		water_condition+=water_num;
		return 0;
	} 
}
Harvest plant_farm::get_harvest()//收获函数 
{
	int growth_step=plant.get_growth_step(planted_time);
	if(growth_step<plant.get_max_step())//还没到收获季节 
	{
		return plant.get_harvest(false);//返回中途收获的值 
	} 
	return plant.get_harvest(true);//返回完整收获的值 
} 
