#include "Livestock_farm_system.h"

Liverstock_farm_system::Liverstock_farm_system(int x, int y) : base_add_x(x), base_add_y(y) {}

// �ػ���������
void Liverstock_farm_system::drawFarm() {
	for (int i = 0; i < 5; ++i) {
		drawFarm(i);
	}
}
// �ػ�һ������
void Liverstock_farm_system::drawFarm(int x) {
	Scene* scene = Director::getInstance()->getRunningScene();
	if (plantSprite[x] != nullptr) {
		scene->removeChild(plantSprite[x]);
	}
	auto info = get_info(16 * (LIVE_FARM_OFFSET_X + x * 3), 16 * LIVE_FARM_OFFSET_Y);
	if (info.type == 0) {
		plantSprite[x] = nullptr;
		return;
	}
	auto str = "/Animals/" + crop_names[info.type] + "_" + std::to_string(info.step) + ".png";
	plantSprite[x] = Sprite::create("/Animals/" + crop_names[info.type] + "_" + std::to_string(info.step) + ".png");
	plantSprite[x]->setPosition((16 * (LIVE_FARM_OFFSET_X + x * 3) - 8), (16 * LIVE_FARM_OFFSET_Y + 8));
	plantSprite[x]->setAnchorPoint(Vec2(0, 0));
	plantSprite[x]->setColor(ColorSystem::getPlantColor(info));
	scene->addChild(plantSprite[x]);
}

bool Liverstock_farm_system::update_conditon(int x, int y, int day)//���ݵ�ǰ�������͵�ַ����ָ�������������� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ��������� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	corral_land[add_x].update_conditon();
	return true;
}
void Liverstock_farm_system::update_all()//������������ 
{
	for (int i = 0; i < 5; i++)
	{
		corral_land[i].update_conditon();//����ÿһ������ 
	}
}
bool Liverstock_farm_system::plant_seed(int seed, int x, int y)//���ֲ��� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	bool result = corral_land[add_x].plant_seed(seed);//���ж�ָ�����صĲ��ֲ��� 
	if (result) drawFarm(add_x);
	return result;
}
Harvest Liverstock_farm_system::get_harvest(int x, int y)//�ջ���
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	//	cout<<endl<<add_x<<" "<<add_y<<endl<<endl;
	if (add_x == -1)//������ 
	{
		Harvest empty_harvest;
		empty_harvest.harvest_type_a = -1;
		empty_harvest.harvest_type_b = -1;
		empty_harvest.max_harvest_num_a = 0;
		empty_harvest.max_harvest_num_b = 0;
		return empty_harvest;//����һ�����ջ� 
	}
	//	cout<<"ztz11"<<endl;
	return corral_land[add_x].get_harvest();
}
bool Liverstock_farm_system::add_food(double food_num, int x, int y)//ιʳ���� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	bool result = corral_land[add_x].add_food(food_num);
	if (result) drawFarm(add_x);
	return result;
}
bool Liverstock_farm_system::add_water(double water_num, int x, int y)//��ˮ���� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	bool result = corral_land[add_x].add_water(water_num);
	if (result) drawFarm(add_x);
	return result;
}
bool Liverstock_farm_system::add_medicine(int x, int y)//���ƺ��� 
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	bool result = corral_land[add_x].add_medicine();
	if (result) drawFarm(add_x);
	return result;
}
out_info Liverstock_farm_system::get_info(int x, int y)//��ȡ���ڸ���ǰ�˵���Ϣ
{
	int add_x;
	get_closest_corral(x, y, add_x);//��ȡ�ܲ��������� 
	//��������ʼ�� 
	out_info now_info;
	now_info.death_flag = false;
	now_info.fertilizer_flag = false;
	now_info.illness_flag = false;
	now_info.food_flag = false;
	now_info.type = 0;
	now_info.step = 0;
	now_info.water_flag = false;
	if (add_x == -1)//������ 
	{
		return now_info;//���ؿ���Ϣ 
	}
	return corral_land[add_x].get_info();
}
void Liverstock_farm_system::get_closest_corral(int x, int y, int& add_x)//������ת��Ϊũ���±�
{
	//��ɽ�����λ����8���ڼ��ɽ��н��� 
	add_x = -1;

	// y����һ����Χ����
	if (y <= (base_add_y - 8) || y >= (base_add_y + 48)) {
		return;
	}
	// xԽ�� 
	if (x <= (base_add_x - 8) || x >= (base_add_x + 16 + 4 * 48)) {
		return;
	}
	//��Խ��Ļ� 
	add_x = ((x + 8 - base_add_x) / 16 + 1) / 3;//�������������ȡֵ 
}