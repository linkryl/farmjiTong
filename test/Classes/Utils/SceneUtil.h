/*
	场景工具类
	Author: 潘越
*/

#pragma once
#include "cocos2d.h"
#include "string"
#include "../Constant.h"
#include "../PlayerData.h"

USING_NS_CC;
namespace SceneUtil {

	// 切换场景
	// 
	// @ scene   欲切换的场景
	void changeScene(Scene* scene);

	// 直接回家，回到家门口
	void gotoFarm(int x = HOME_X, int y = HOME_Y, Direction faceTo = DOWN);

	void gotoHouse(int x = FARM_TO_HOUSE_INIT_X, int y = FARM_TO_HOUSE_INIT_Y, Direction faceTo = UP);

	void gotoTown(int x = FARM_TO_TOWN_INIT_X, int y = FARM_TO_TOWN_INIT_Y, Direction faceTo = RIGHT);

	void gotoMountain(int x = FARM_TO_MOUNTAIN_INIT_X, int y = FARM_TO_MOUNTAIN_INIT_Y, Direction faceTo = RIGHT);

	void gotoWoods(int x = FARM_TO_WOODS_INIT_X, int y = FARM_TO_WOODS_INIT_Y, Direction faceTo = LEFT);

	void gotoCave(int x = FARM_TO_CAVE_INIT_X, int y = FARM_TO_CAVE_INIT_Y, Direction faceTo = UP);
}