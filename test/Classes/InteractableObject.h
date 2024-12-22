#include "cocos2d.h"
#include "MotionManager.h"
#include "Scenes/MovableScene.h"
#include "TPMap.h"

USING_NS_CC;

class InteractableObject : public Node, public Movable {
public:
	//void moveUpdate(MotionManager* information) = 0;
	void regist(MotionManager* motionManager, Node* father) override {

	}
};

class TeleportPoint : public InteractableObject {
private:
	TPMap toMap;
	MovableScene* movableScene;
public:
	virtual void moveUpdate(MotionManager* information) override;
	TeleportPoint(TPMap toMap, MovableScene* movableScene) : toMap(toMap), movableScene(movableScene) {}
};