#pragma once
#include "cocos2d.h"

class Test2Scene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float delta);

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Test2Scene);
};