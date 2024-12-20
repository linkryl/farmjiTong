#include "InteractableObject.h"

void TeleportPoint::moveUpdate(MotionManager* information) {

	// ¿É½»»¥¾àÀë
	static const int limitDistance = 30;
	auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_C;
	if (information->keyMap[communicate]) {
		// ¼ÆËãÅ·ÊÏ¾àÀë
		double distance = std::hypot(getPosition().x - information->playerPosition.x, getPosition().y - information->playerPosition.y);
		if (distance <= limitDistance) {
			movableScene->changeScene(toMap);
		}
	}
}
