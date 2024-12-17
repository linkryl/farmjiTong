#pragma once
#ifndef _ENTRUSTSCENE_H_
#define _ENTRUSTSCENE_H_
#include "cocos2d.h"

#include "SocialInfo.h"

USING_NS_CC;

class EntrustScene : public Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(EntrustScene);
};
#endif