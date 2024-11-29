#pragma once
#include "cocos2d.h"
#include <map>
using namespace cocos2d;
enum Direction{UP, RIGHT, DOWN, LEFT};
class Player :public Sprite
{
private:
	// �������ֵ
	float luck;
	// ����ٶ�ֵ
	int speed;
public:
	Player() : luck(0.0f), speed(1) {}
	void go(const Direction direction);
	static Player* create(const std::string& path);
};