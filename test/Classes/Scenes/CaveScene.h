#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "MovableScene.h"

USING_NS_CC;

class CaveScene : public MovableScene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float delta);

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(CaveScene);

    void changeScene(TPMap toMap) override;

};