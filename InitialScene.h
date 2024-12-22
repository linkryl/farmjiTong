#pragma once
#ifndef _INITIAL_SCENE_H_
#define _INITIAL_SCENE_H_

#include "cocos2d.h"
#include "Time_system.h"

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

  void updateLabel(float dt)
  {
    time_clock currentTime = _timeSystem->get_time();
    std::string timeString = StringUtils::format(
      "Day: %d, Hour: %02d:%02d, Weather: %d",
      currentTime.day,
      currentTime.now_hour,
      currentTime.half_hour ? 30 : 0,
      currentTime.weather
    );
    _label->setString(timeString);
  }

  // ʵ�� InitialScene ��� create ����
  CREATE_FUNC(InitialScene);

private:
  Label* _label;
  Sprite* _item;
  Time_system* _timeSystem = Time_system::getInstance();
};

#endif // !_INITIAL_SCENE_H_#pragma once