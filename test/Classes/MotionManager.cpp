#include <cocos2d.h>
#include "MotionManager.h"
#include <map>
#include <exception>
using namespace cocos2d;


void MotionManager::update()
{
	if (isEnd()) {
		return;
	}
	for (auto object : movableObjects)
	{
		try
		{
			object->moveUpdate(this);

		}
		catch (std::exception e)
		{
			CCLOG(e.what());
			continue;
		}
	}
}

void MotionManager::add_movableObject(Movable* newObject)
{
	movableObjects.push_back(newObject);
}
void MotionManager::del_object(Movable* objPtr)
{
	//std::erase(movableObjects, objPtr);
}