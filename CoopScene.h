#pragma once
#include "2d/CCScene.h"

#include "SocialInfo.h"

USING_NS_CC;

class CoopScene : public cocos2d::Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(CoopScene);
};