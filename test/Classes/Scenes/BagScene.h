#pragma once
#include "cocos2d.h"
#include "BackpackManager.h"
#include "Skill.h" // ��� Skill ͷ�ļ�

USING_NS_CC;

class BagScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(BagScene);
};