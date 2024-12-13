#pragma once
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class MountainScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float delta);

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MountainScene);

};