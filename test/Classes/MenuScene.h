#pragma once
#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
  // ��������
  static cocos2d::Scene* createScene();

  // ��ʼ������
  virtual bool init();

  // ʵ�� MenuScene ��� create ����
  CREATE_FUNC(MenuScene);
};
#endif // !_MENU_SCENE_H_#pragma once
