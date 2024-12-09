//#include"map_system.h"
#include"Plant_farm_system.h"
//#include<cstdlib>
#include"pic_map.h"
#include<cstring>
int main()
{
	plant_farm* test_farm=new plant_farm;
	test_farm->hoe_ground();//ณ๚ตุ
	test_farm->plant_seed(1100);
	cout<<test_farm->plant->get_health()<<endl;
	for (int i = 1; i <= 12; i++)
	{
	    test_farm->update_conditon(1);
	    test_farm->add_fertilizer(1.0);
	    test_farm->add_water(1.0);
	}
//	cout<<test_farm->plant->get_growth_step(12)<<endl;
	int now_step=test_farm->plant->get_growth_step(12.0);
	cout<<now_step<<endl;
	Pic_map p_map;
	
	string pic_name = p_map.make_pic(1111,3);
	cout<<pic_name;
} 
