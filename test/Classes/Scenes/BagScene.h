#pragma once
#include "cocos2d.h"
#include "BackpackManager.h"
#include "Skill.h" // 添加 Skill 头文件

USING_NS_CC;

class BagScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(BagScene);
};