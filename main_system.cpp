#include"Time_system.h" 
class main_system
{
	private:
		Time_system *time_system;//ʱ��ϵͳ 
//		Farm_system farm_system;//ũ��ϵͳ 
//		Bag_system bag_system;//����ϵͳ 
	public:
		main_system();
		~main_system();
		void load_save();//��ȡ�浵����
		void update_all();//��day�л�ʱ�������е���������صĶ��� 
};
main_system::main_system()
{
	time_system=new Time_system;
}
int main()
{

}
