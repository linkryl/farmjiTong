#pragma once
#include <cocos2d.h>
#include <map>
#include <vector>
using namespace cocos2d;

class Movable;
struct MotionManager
{
	// ��������


	enum Character { player, Abigail };
	// ��ɫ��Ӧ��ID
	std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };
	// ���λ��
	Vec2 playerPosition;
	// ������Ϣ
	std::map<EventKeyboard::KeyCode, bool> keyMap;
	// �����Ϣ
	bool mouse_down;
	// ��Ƭ��ͼ
	TMXTiledMap* tmxMap;

	// ����Ⱥ��
	std::vector<Movable*> movableObjects;
	// ���º���
	void update();
	// ��Ӷ���ĺ���
	void add_movableObject(Movable* newObject);
};

class Movable
{
public:
	virtual void moveUpdate(MotionManager* information) = 0;
};