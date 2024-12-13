#include"Farm_system.h"
#include"Time_system.h"
Farm_system now_farm;
void print_out_info(out_info now_info)
{
	cout<<"type: "<<now_info.type<<endl;
	cout<<"step: "<<now_info.step<<endl;
	cout<<"death_flag: "<<now_info.death_flag<<endl;
	cout<<"illness_flag: "<<now_info.illness_flag<<endl;
	cout<<"water_flag: "<<now_info.water_flag<<endl;
	cout<<"fertilizer_flag: "<<now_info.fertilizer_flag<<endl;
	cout<<"food_flag: "<<now_info.food_flag<<endl;
}
void print_harvest(Harvest now_harvest)
{
	cout<<"type_a: "<<now_harvest.harvest_type_a<<endl;
	cout<<"max_num_a: "<<now_harvest.max_harvest_num_a<<endl;
	cout<<"type_b: "<<now_harvest.harvest_type_b<<endl;
	cout<<"max_num_b: "<<now_harvest.max_harvest_num_b<<endl;
}
Time_system time_system;
int main()
{
	out_info now_info;
	now_farm.plant_seed(1100,-4,6);
	now_farm.add_fertilizer(10,7,7);
	for(int i=1;i<=6;i++)
	{
		now_farm.update_conditon(0,0,i);
//		now_farm.add_fertilizer(2,0,1);
	}
	now_farm.add_medicine(1,1);
	now_farm.add_fertilizer(10,0,1);
//	now_farm.update_conditon(0,0,7);
//	Harvest now_harvest=now_farm.get_harvest(7,7);
//	print_harvest(now_harvest);
	now_info=now_farm.get_info(0,0);
	print_out_info(now_info);
}
