//#include"Corral_system.h"
#include"Field_system.h"
class Farm_system//只是一个耦合剂，用于将农田和畜栏合并在一起 
{
	private:
		const Time_system* time_system;//时间接口 
	public:
//		Corral_system corral;//畜栏类 
		Field_system field;//农田类 
}; 
