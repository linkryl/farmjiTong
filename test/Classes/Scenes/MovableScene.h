#pragma once
#include "cocos2d.h"
#include "Player.h"

class MovableScene : public Scene, public Movable {
private:
	TMXTiledMap* tmxMap;
	Player* player;
public:
	void setTiledMap(TMXTiledMap* tmxMap) {
		this->tmxMap = tmxMap;
	}
	TMXTiledMap* getTiledMap() {
		return this->tmxMap;
	}
	void setPlayer(Player* player) {
		this->player = player;
	}
	Player* getPlayer() {
		return this->player;
	}
	virtual void go(Direction direction);
	virtual void moveUpdate(MotionManager* information);

	// ������(x, y)Ϊ���ĵ�ĳ�����������
	// x, y Ϊ��������
	Vec2 getMiddlePosition(double x, double y);

	Vec2 getMiddlePosition(Vec2 position);
};