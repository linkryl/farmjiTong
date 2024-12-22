#include <cocos2d.h>
#include "MotionManager.h"
#include <map>
#include <exception>
#include "CoopScene.h"
#include "Time_system.h"
using namespace cocos2d;


void MotionManager::update()
{
	deltaPlayerHealth = 0;
	for (auto object : movableObjects)
	{
		try
		{
			object->moveUpdate(this);
		}
		catch (std::bad_alloc)
		{
			continue;
		}
	}
	// E键切换到好感度界面
	auto coopSwith = EventKeyboard::KeyCode::KEY_E;
	if (keyMap[coopSwith])
	{
		keyMap[coopSwith] = false;
		Director::getInstance()->pushScene(CoopScene::createScene());
	}
	auto time_sys = Time_system::getInstance();
	time_sys->update_time();

	
}

void MotionManager::add_movableObject(Movable* newObject)
{
	movableObjects.push_back(newObject);
}
void MotionManager::del_object(Movable* objPtr)
{
	auto it = movableObjects.begin();
	for (it = movableObjects.begin(); it != movableObjects.end(); ++it) {
		if (*it == objPtr) {
			break;
		}
	}
	movableObjects.erase(it);
	//std::erase(movableObjects, objPtr);
}