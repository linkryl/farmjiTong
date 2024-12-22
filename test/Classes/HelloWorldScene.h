#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <map>
#include "cocos2d.h"


class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void update(float delta);
    
    // implement the "static create()" method manuallya
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
