#pragma once
#include <cocos2d.h>
#include <map>
#include <vector>
#include <memory>

using namespace cocos2d;

class Movable;

struct MotionManager
{
	// ��������
	enum Character { player, Abigail, TRANSPORT };
	// ��ɫ��Ӧ��ID
	std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114}, {TRANSPORT, 42} };
	// ���λ��
	Vec2 playerPosition;
	// ������Ϣ
	std::map<EventKeyboard::KeyCode, bool> keyMap;
	// �����Ϣ
	bool mouse_down;
	// ��Ƭ��ͼ
	TMXTiledMap* tmxMap;

	// �øж�ϵͳ


	// �Ƿ����
	bool isReplaced = false;

	void setEnd() {
		isReplaced = true;
	}
	bool isEnd() {
		return isReplaced;
	}

	// ����Ⱥ��
	std::vector<Movable*> movableObjects;

	// ���º���
	void update();
	// ��Ӷ���ĺ���
	void add_movableObject(Movable* newObject);
	void del_object(Movable* objPtr);
};

class Movable
{
public:
	virtual void moveUpdate(MotionManager* information) = 0;
};