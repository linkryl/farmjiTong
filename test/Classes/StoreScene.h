#pragma once
#ifndef _STORESCENE_H_
#define _STORESCENE_H_
#include "cocos2d.h"
#include "CommercialSystem.h"

USING_NS_CC;

class StoreScene : public Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(StoreScene);
};
#endif