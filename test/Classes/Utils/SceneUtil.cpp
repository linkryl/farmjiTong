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

	void gotoFarm(int x, int y, Direction faceTo) {
		playerInfo = { x, y, faceTo };
		changeScene(FarmScene::create());
	}

	void gotoHouse(int x, int y, Direction faceTo) {
		playerInfo = { x, y, faceTo };
		changeScene(FarmHouseScene::create());
		//Director::getInstance()->pushScene(FarmHouseScene::create());
	}

	void gotoTown(int x, int y, Direction faceTo) {
		playerInfo = { x, y, faceTo };
		changeScene(TownScene::create());
	}

	void gotoMountain(int x, int y, Direction faceTo) {
		playerInfo = { x, y, faceTo };
		changeScene(MountainScene::create());
	}

	void gotoWoods(int x, int y, Direction faceTo) {
		playerInfo = { x, y, faceTo };
		changeScene(WoodsScene::create());
	}

	void gotoCave(int x, int y, Direction faceTo) {
		playerInfo = { x, y, faceTo };
		changeScene(CaveScene::create());
	}
}

