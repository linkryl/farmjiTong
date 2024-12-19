/*
	场景工具类
	Author: 潘越
*/

#pragma once
#include "cocos2d.h"
#include "string"

USING_NS_CC;
namespace SceneUtil {

	// 切换场景
	// 
	// @ scene   欲切换的场景
	void changeScene(Scene* scene);

	// 直接回家，回到家门口
	void goHome();
}