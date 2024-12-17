#include "SceneUtil.h"

void changeScene(Scene *scene) {

	auto director = Director::getInstance();
	auto nowScene = director->getRunningScene();
	if (scene == nowScene) {
		return;
	}
	director->replaceScene(scene);
}