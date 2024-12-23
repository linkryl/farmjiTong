#pragma once
#ifndef _COOPSCENE_H_
#define _COOPSCENE_H_
#include "cocos2d.h"

#include "SocialInfo.h"

USING_NS_CC;

class CoopScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CoopScene);
};
#endif