#pragma once
#include <cocos2d.h>
#include <map>
#include <vector>
//#include "Player.h"
using namespace cocos2d;
class Movable;
struct MotionManager
{
	// 环境参量
	enum Character { player, Abigail };
	// 角色对应的ID
	std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };
	// 玩家指针
    // Player* playerPtr;
	// 玩家位置
	Vec2 playerPosition;
	// 按键信息
	std::map<EventKeyboard::KeyCode, bool> keyMap;
	// 鼠标信息
	bool mouse_down;
	// 瓦片地图
	TMXTiledMap* tmxMap;

	// 好感度系统

	// 对象群体
	std::vector<Movable*> movableObjects;
	// 更新函数
	void update();
	// 添加对象的函数
	void add_movableObject(Movable* newObject);
	void del_object(Movable* objPtr);
};

class Movable
{
public:
	virtual void moveUpdate(MotionManager* information) = 0;
};