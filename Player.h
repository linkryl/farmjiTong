﻿#pragma once
#include "cocos2d.h"
#include <map>
#include <string>
using namespace cocos2d;
enum Direction { UP, RIGHT, DOWN, LEFT };
enum Motion {GO, LIGHT_HIT, HEAVY_HIT, STAND};

class PlayerPart :public Sprite
{
private:
	// 玩家运气
	float luck;
	// 玩家速度
	int speed;
	std::string part_name;
	std::map<Motion, int> hashValue = { {GO, 147}, {LIGHT_HIT, 458}, {HEAVY_HIT, 749}, {STAND, 8674} };
	std::map<std::string, int> partNameHash = { {"body", 4556498}, {"arm", 843458} };
public:
	PlayerPart() : luck(0.0f), speed(1) {}
	PlayerPart(const std::string& part_name) : luck(0.0f), speed(1), part_name(part_name) {}
	void go(const Direction direction);
	virtual void stand(const Direction direction);
	virtual void light_hit(const Direction direction);
	virtual void heavy_hit(const Direction direction);

	static PlayerPart* create(const std::string& path, const std::string& part_name);
};
// 用于遍历Player的各个身体部分的宏
#define PLAYER_TRAVELSAL(part) for (const auto part : parts)

class Player : public Node
{
private:
	// 角色的身体各个部分
	Vector<PlayerPart*> parts;
	// 幸运值
	float luck;
	// 速度
	int speed;
	// 朝向方向
	Direction faceTo;
public:
	Player() : luck(0), speed(1), faceTo(DOWN) {}
	void add_part(const std::string& path, const std::string& part_name)
	{
		parts.pushBack(PlayerPart::create(path, part_name));
	}
	void go(Direction direction)
	{
		faceTo = direction;
		PLAYER_TRAVELSAL(part)
		{
			part->go(direction);
		}
	}
	void heavy_hit()
	{
		PLAYER_TRAVELSAL(part)
		{
			part->heavy_hit(faceTo);
		}
	}
	void light_hit()
	{
		PLAYER_TRAVELSAL(part)
		{
			part->light_hit(faceTo);
		}
	}
	void stand()
	{
		PLAYER_TRAVELSAL(part)
		{
			part->stand(faceTo);
		}
	}

	void setPosition(const Vec2& vec)
	{
		PLAYER_TRAVELSAL(part)
		{
			part->setPosition(vec);
		}
	}
	void setScale(const float scale)
	{
		PLAYER_TRAVELSAL(part)
		{
			part->setScale(scale);
		}
	}
	Vector<PlayerPart*> get_parts()
	{
		return parts;
	}
	static Player* create()
	{
		Player* player = new Player;
		if (player)
		{
			player->autorelease();
			return player;
		}
		CC_SAFE_DELETE(player);
		return nullptr;
	}
};

class ToolOrweapon : public PlayerPart
{
	virtual void stand(const Direction direction);
	virtual void light_hit(const Direction direction);
};