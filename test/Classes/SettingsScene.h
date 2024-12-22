#pragma once
#ifndef _SETTINGS_SCENE_H_
#define _SETTINGS_SCENE_H_

#include "cocos2d.h"

class SettingsScene : public cocos2d::Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(SettingsScene);
};
#endif // !_SETTINGS_SCENE_H_