#pragma once
#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
  // 创建场景
  static cocos2d::Scene* createScene();

  // 初始化场景
  virtual bool init();

  // 实现 MenuScene 类的 create 方法
  CREATE_FUNC(MenuScene);
};
#endif // !_MENU_SCENE_H_#pragma once
