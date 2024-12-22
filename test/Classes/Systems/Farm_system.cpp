#include "Farm_system.h"

Farm_system::Farm_system(int x, int y) : base_add_x(x), base_add_y(y) {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			plantSprite[i][j] = nullptr;
		}
	}
}

// �ػ�����ũ��
void Farm_system::drawFarm() {
	for (int i = 0; i < 5; ++i) {
		for (int j = 4; j >= 0; --j) {
			drawFarm(i, j);
		}
	}
}
// �ػ�һ��ũ��
void Farm_system::drawFarm(int x, int y) {
	Scene* scene = Director::getInstance()->getRunningScene();
	if (plantSprite[x][y] != nullptr) {
		scene->removeChild(plantSprite[x][y]);
	}
	//int dx, dy;
	//get_closest_land(x, y, dx, dy);
	auto info = get_info(x, y, true);
	if (info.type == 0) {
		plantSprite[x][y] = nullptr;
		return;
	}
	auto str = "/Crops/" + crop_names[info.type] + "_" + std::to_string(info.step) + ".png";
	plantSprite[x][y] = Sprite::create("/Crops/" + crop_names[info.type] + "_" + std::to_string(info.step) + ".png");
	plantSprite[x][y]->setPosition(16 * (FARM_OFFSET_X + x), 16 * (FARM_OFFSET_Y + y));
	plantSprite[x][y]->setAnchorPoint(Vec2(0, 0));
	plantSprite[x][y]->setColor(ColorSystem::getPlantColor(info));
	scene->addChild(plantSprite[x][y]);
}

bool Farm_system::update_conditon(int x, int y, int day)//���ݵ�ǰ�������͵�ַ����ָ�������������� 
{
	int add_x, add_y;
	get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
	if (add_x == -1 || add_y == -1)//������ 
	{
		return false;//û���ܲ����� 
	}
	int weather = day / 90;
	weather %= 4;//��ȡ���ڣ�����һ��360�죬ÿ������90�������� 
	weather++;
	//	cout<<weather<<endl; 
	farm_land[add_x][add_y].update_conditon(weather);
	return true;
}
void Farm_system::update_all(int day)//���ݵ�ǰ��������������ũ�� 
{
	int weather = day / 90;
	weather %= 4;//��ȡ���ڣ�����һ��360�죬ÿ������90�������� 
	weather++;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			farm_land[i][j].update_conditon(weather);//����ÿһ������ 
		}
	}
}
bool Farm_system::plant_seed(int seed, int x, int y, bool isTile)//���ֲ��� 
{
	int add_x, add_y;
	if (isTile) {
		add_x = x, add_y = y;
	}
	else {
		get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
		if (add_x == -1 || add_y == -1)//������ 
		{
			return false;//û���ܲ����� 
		}
	}
	bool result = farm_land[add_x][add_y].plant_seed(seed);//���ж�ָ�����صĲ��ֲ��� 
	if (result) drawFarm(add_x, add_y);
	return result;
}
Harvest Farm_system::get_harvest(int x, int y)//�ջ���
{
	int add_x, add_y;
	get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
	//	cout<<endl<<add_x<<" "<<add_y<<endl<<endl;
	if (add_x == -1 || add_y == -1)//������ 
	{
		Harvest empty_harvest;
		empty_harvest.harvest_type_a = -1;
		empty_harvest.harvest_type_b = -1;
		empty_harvest.max_harvest_num_a = 0;
		empty_harvest.max_harvest_num_b = 0;
		return empty_harvest;//����һ�����ջ� 
	}
	//	cout<<"ztz11"<<endl;
	return farm_land[add_x][add_y].get_harvest();
}
bool Farm_system::add_fertilizer(double fertilizer_num, int x, int y, bool isTile)//ʩ�ʺ��� 
{
	int add_x, add_y;
	if (isTile) {
		add_x = x, add_y = y;
	}
	else {
		get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
		if (add_x == -1 || add_y == -1)//������ 
		{
			return false;//û���ܲ����� 
		}
	}
	bool result = farm_land[add_x][add_y].add_fertilizer(fertilizer_num);
	if (result) drawFarm(add_x, add_y);
	return result;
}
bool Farm_system::add_water(double water_num, int x, int y, bool isTile)//��ˮ���� 
{
	int add_x, add_y;
	if (isTile) {
		add_x = x, add_y = y;
	}
	else {
		get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
		if (add_x == -1 || add_y == -1)//������ 
		{
			return false;//û���ܲ����� 
		}
	}
	bool result = farm_land[add_x][add_y].add_water(water_num);
	if (result) drawFarm(add_x, add_y);
	return result;
}
bool Farm_system::add_medicine(int x, int y, bool isTile)//���ƺ��� 
{
	int add_x, add_y;
	if (isTile) {
		add_x = x, add_y = y;
	}
	else {
		get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
		if (add_x == -1 || add_y == -1)//������ 
		{
			return false;//û���ܲ����� 
		}
	}
	bool result = farm_land[add_x][add_y].add_medicine();
	if (result) drawFarm(add_x, add_y);
	return result;
}
// x,yΪ��������
out_info Farm_system::get_info(int x, int y, bool isTile)//��ȡ���ڸ���ǰ�˵���Ϣ
{
	int add_x, add_y;
	if (isTile) {
		add_x = x, add_y = y;
	}
	else {
		get_closest_land(x, y, add_x, add_y);//��ȡ�ܲ�����ũ�� 
	}

	//��������ʼ�� 
	out_info now_info;
	now_info.death_flag = false;
	now_info.fertilizer_flag = false;
	now_info.illness_flag = false;
	now_info.food_flag = false;
	now_info.type = 0;
	now_info.step = 0;
	now_info.water_flag = false;
	if (add_x == -1 || add_y == -1)//������ 
	{
		return now_info;//���ؿ���Ϣ 
	}
	return farm_land[add_x][add_y].get_info();
}
void Farm_system::get_closest_land(int x, int y, int& add_x, int& add_y)//������ת��Ϊũ���±�
{
	//��ɽ�����λ����8���ڼ��ɽ��н��� 
	add_x = -1;
	add_y = -1;
	if (x <= (base_add_x - 8) || x >= (base_add_x + 72))//xԽ�� 
	{
		return;
	}
	if (y <= (base_add_y - 8) || y >= (base_add_y + 72))//yԽ�� 
	{
		return;
	}
	//��Խ��Ļ� 
	add_x = (x + 8 - base_add_x) / 16;
	add_y = (y + 8 - base_add_y) / 16;//�������������ȡֵ 
}