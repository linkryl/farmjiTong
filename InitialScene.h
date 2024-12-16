#pragma once
#ifndef _INITIAL_SCENE_H_
#define _INITIAL_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

/*
 * Class Name:     InitialScene
 * Class Function: ��ʼ������
 */
class InitialScene : public Scene {
public:
  // ��������
  static Scene* createScene();

  // ��ʼ������
  virtual bool init();

  // ʵ�� InitialScene ��� create ����
  CREATE_FUNC(InitialScene);

private:
  // ����ַ��Ϸ���
  bool isValidCharacter(const char32_t ch);

  // ����ַ����Ϸ���
  bool isValidString(const std::string& str);
};

#endif // !_INITIAL_SCENE_H_#pragma once