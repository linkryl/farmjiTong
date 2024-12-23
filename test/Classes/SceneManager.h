#pragma once
#include "cocos2d.h"
#include "MotionManager.h"
#include <string>
#include <map>
class SceneManager : public Movable, public Node
{
private:
	std::map<std::string, Scene*> sceneList;
public:
	static SceneManager* getInstance()
	{
		static SceneManager* res = new SceneManager();
		return res;
	}
	void add_scene(Scene* new_scene, const std::string& scene_name)
	{
		sceneList[scene_name] = new_scene;
	}
	void moveUpdate(MotionManager* information)
	{
		if (information->keyMap[EventKeyboard::KeyCode::KEY_E])
		{
			information->keyMap[EventKeyboard::KeyCode::KEY_E] = false;
			Director::getInstance()->pushScene(CoopScene::createScene());
		}
	}
	void regist(MotionManager* motionManager, Node* father)
	{
		motionManager->add_movableObject(this);
		if (father != nullptr)
			father->addChild(this);
	}
};