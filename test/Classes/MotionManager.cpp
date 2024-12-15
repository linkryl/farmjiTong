#include <cocos2d.h>
#include "MotionManager.h"
#include <map>
using namespace cocos2d;


void MotionManager::update()
{
	for (auto object : movableObjects)
		object->moveUpdate(this);
}

void MotionManager::add_movableObject(Movable* newObject)
{
	movableObjects.push_back(newObject);
}