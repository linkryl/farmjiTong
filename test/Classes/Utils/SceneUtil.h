/*
	����������
	Author: ��Խ
*/

#pragma once
#include "cocos2d.h"
#include "string"
#include "../Constant.h"
#include "../PlayerData.h"

USING_NS_CC;
namespace SceneUtil {

	// �л�����
	// 
	// @ scene   ���л��ĳ���
	void changeScene(Scene* scene);

	// ֱ�ӻؼң��ص����ſ�
	void gotoFarm(int x = HOME_X, int y = HOME_Y, Direction faceTo = DOWN);

	void gotoHouse(int x = FARM_TO_HOUSE_INIT_X, int y = FARM_TO_HOUSE_INIT_Y, Direction faceTo = UP);

	void gotoTown(int x = FARM_TO_TOWN_INIT_X, int y = FARM_TO_TOWN_INIT_Y, Direction faceTo = RIGHT);

	void gotoMountain(int x = FARM_TO_MOUNTAIN_INIT_X, int y = FARM_TO_MOUNTAIN_INIT_Y, Direction faceTo = RIGHT);

	void gotoWoods(int x = FARM_TO_WOODS_INIT_X, int y = FARM_TO_WOODS_INIT_Y, Direction faceTo = LEFT);

	void gotoCave(int x = FARM_TO_CAVE_INIT_X, int y = FARM_TO_CAVE_INIT_Y, Direction faceTo = UP);
}