#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "MotionManager.h"

USING_NS_CC;

class MovableScene : public Scene, public Movable {
private:
	TMXTiledMap* tmxMap;
	Player* player;
	MotionManager motionManager;
public:
	MotionManager* getMotionManager() {
		return &(this->motionManager);
	}
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

	// 计算以(x, y)为中心点的场景所处坐标
	// x, y 为像素坐标
	Vec2 getMiddlePosition(double x, double y);

	Vec2 getMiddlePosition(Vec2 position);

	// 当前场景处于(x, y)像素坐标时，进行修正，防止露黑边
	Vec2 getCorrectionPosition(Vec2 position);

	void returnMiddlePosition();
};