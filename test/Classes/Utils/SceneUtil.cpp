#include "SceneUtil.h"
#include "Constant.h"
#include "PlayerData.h"
#include "Scenes/FarmScene.h"
#include "Scenes/TownScene.h"
#include "Scenes/WoodsScene.h"
#include "Scenes/CaveScene.h"
#include "Scenes/MountainScene.h"
#include "Scenes/FarmHouseScene.h"

extern PlayerInfo playerInfo;

namespace SceneUtil {
	void changeScene(Scene* scene) {

		auto director = Director::getInstance();
		auto nowScene = reinterpret_cast<MovableScene*>(director->getRunningScene());
		nowScene->getMotionManager()->setEnd();
		if (scene == nowScene) {
			return;
		}
		director->replaceScene(scene);
	}

	void goHome() {
		playerInfo = { HOME_X, HOME_Y, DOWN };
		changeScene(FarmScene::create());
	}
}

