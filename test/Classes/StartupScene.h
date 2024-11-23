#pragma once
#ifndef _STARTUP_SCENE_H_
#define _STARTUP_SCENE_H_

#include "cocos2d.h"

class StartupScene : public cocos2d::Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartupScene);
};
#endif // !_STARTUP_SCENE_H_