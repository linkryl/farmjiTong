#include"Time_system.h" 
class main_system
{
	private:
		Time_system *time_system;//时间系统 
//		Farm_system farm_system;//农场系统 
//		Bag_system bag_system;//背包系统 
	public:
		main_system();
		~main_system();
		void load_save();//读取存档操作
		void update_all();//当day切换时更新所有的与日期相关的东西 
};
main_system::main_system()
{
	time_system=new Time_system;
}
int main()
{

}
