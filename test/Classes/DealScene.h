#pragma once
#ifndef _DEALSCENE_H_
#define _DEALSCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class DealScene : public Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(DealScene);
};
#endif