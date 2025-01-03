#include "InteractableObject.h"

void TeleportPoint::moveUpdate(MotionManager* information) {

	// �ɽ�������
	static const int limitDistance = 30;
	auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_T;
	if (information->keyMap[communicate]) {
		// ����ŷ�Ͼ���
		double distance = std::hypot(getPosition().x - information->playerPosition.x, getPosition().y - information->playerPosition.y);
		if (distance <= limitDistance) {
			information->keyMap[communicate] = false;
			movableScene->changeScene(toMap);
		}
	}
}
