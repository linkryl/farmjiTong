#pragma once
#ifndef _INITIAL_SCENE_H_
#define _INITIAL_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

/*
 * Class Name:     InitialScene
 * Class Function: 初始场景类
 */
class InitialScene : public Scene {
public:
  // 创建场景
  static Scene* createScene();

  // 初始化场景
  virtual bool init();

  // 实现 InitialScene 类的 create 方法
  CREATE_FUNC(InitialScene);

private:
  // 检查字符合法性
  bool isValidCharacter(const char32_t ch);

  // 检查字符串合法性
  bool isValidString(const std::string& str);
};

#endif // !_INITIAL_SCENE_H_#pragma once