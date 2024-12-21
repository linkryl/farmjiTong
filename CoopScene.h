#pragma once
#ifndef _COOPSCENE_H_
#define _COOPSCENE_H_
#include "cocos2d.h"

#include "SocialInfo.h"

USING_NS_CC;

class CoopScene : public cocos2d::Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  static CoopScene* create()
  {
      CoopScene* ret = new (std::nothrow) CoopScene();
      if (ret && ret->init())
      {
          ret->autorelease();
          return ret;
      }
      else
      {
          delete ret;
          ret = nullptr;
          return nullptr;
      }
  }
};
#endif