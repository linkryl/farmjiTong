#pragma once
#ifndef _SKILLSCENE_H_
#define _SKILLSCENE_H_
#include "cocos2d.h"


USING_NS_CC;

class SkillScene : public Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(SkillScene);
};
#endif