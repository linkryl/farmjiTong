#pragma once
#include "cocos2d.h"
#include "PlayerData.h"
#include "Util.h"
#include <map>
#include <string>
using namespace cocos2d;

// 用于遍历Player的各个身体部分的宏
#define PLAYER_TRAVELSAL(part) for (const auto part : parts)
#define TOOL_TRAVELSAL(tool) for (const auto tool : tools)

class Player;

class PlayerPart :public Sprite
{
protected:
	// 帧的宽度与高度
	const int width = 16, height = 32;
	// 玩家运气
	float luck;
	// 玩家速度
	int speed;
	// Player虚节点对象
	Player* player;
	std::string part_name;
	std::map<Motion, int> hashValue = { {GO, 147}, {LIGHT_HIT, 458}, {HEAVY_HIT, 749}, {STAND, 8674} };
	std::map<std::string, int> partNameHash = { {"body", 4556498}, {"arm", 843458}, {"axe", 43545364}};
public:
	PlayerPart() : luck(0.0f), speed(1) {}
	PlayerPart(const std::string& part_name, const int width_ = 16, const int height_ = 32) : luck(0.0f), speed(1), part_name(part_name), width(width_), height(height_)  {}
	void go(const Direction direction, const std::string catogory = "part");
	virtual void stand(const Direction direction);
	virtual void light_hit(const Direction direction);
	virtual void heavy_hit(const Direction direction);

	void setPlayer(Player* player) {
		this->player = player;
	}
	Player* getPlayer() {
		return this->player;
	}

	static PlayerPart* create(const std::string& path, const std::string& part_name);
};

class Player : public Node
{
private:
	// 角色的身体各个部分
	Vector<PlayerPart*> parts;
	// 角色手持的装备
	Vector<PlayerPart*> tools;
	// 幸运值
	float luck;
	// 速度
	int speed;
	// 朝向方向
	Direction faceTo;
	// 所在地图
	TMXTiledMap* tmxMap;
public:
	Player(TMXTiledMap* map = nullptr) : luck(0), speed(1), faceTo(DOWN) {
		tmxMap = map;
	}
	void setTiledMap(TMXTiledMap* map) {
		tmxMap = map;
	}
	TMXTiledMap* getTiledMap() {
		return this->tmxMap;
	}
	void add_part(const std::string& path, const std::string& part_name)
	{
		auto part = PlayerPart::create(path, part_name);
		part->setPlayer(this);
		part->setAnchorPoint(Vec2(0.5, 0));
		parts.pushBack(part);
	}
	void add_tool(const std::string& path, const std::string& tool_name)
	{
		auto part = PlayerPart::create(path, tool_name);
		part->setPlayer(this);
		part->setAnchorPoint(Vec2(0.5, 1.0/3));
		tools.pushBack(part);
		//tools.pushBack(PlayerPart::create(path, tool_name));
	}
	void go(Direction direction)
	{
		faceTo = direction;
		PLAYER_TRAVELSAL(part)
		{
			part->go(direction);
		}
		TOOL_TRAVELSAL(tool)
		{
			tool->go(direction, "tool");
		}
	}
	void heavy_hit()
	{
		PLAYER_TRAVELSAL(part)
		{
			part->heavy_hit(faceTo);
		}
		TOOL_TRAVELSAL(tool)
		{
			// 工具向上砍不好做，干脆不要了
			if (faceTo != UP)
				tool->heavy_hit(faceTo);
		}
	}
	void light_hit()
	{
		PLAYER_TRAVELSAL(part)
		{
			part->light_hit(faceTo);
		}
		TOOL_TRAVELSAL(tool)
		{
			tool->light_hit(faceTo);
		}
	}
	void stand()
	{
		PLAYER_TRAVELSAL(part)
		{
			part->stand(faceTo);
		}
		TOOL_TRAVELSAL(tool)
		{
			tool->stand(faceTo);
		}
	}

	void setPosition(const Vec2& vec)
	{
		Node::setPosition(vec);
		PLAYER_TRAVELSAL(part)
		{
			part->setPosition(vec);
		}
		TOOL_TRAVELSAL(tool)
		{
			tool->setPosition(vec);
		}
	}
	void setScale(const float scale)
	{
		PLAYER_TRAVELSAL(part)
		{
			part->setScale(scale);
		}
		TOOL_TRAVELSAL(tool)
		{
			tool->setScale(scale);
		}
	}
	Vector<PlayerPart*> get_parts()
	{
		return parts;
	}
	Vector<PlayerPart*> get_tools()
	{
		return tools;
	}
	static Player* create()
	{
		Player* player = new Player();
		if (player)
		{
			player->autorelease();
			return player;
		}
		CC_SAFE_DELETE(player);
		return nullptr;
	}
};
