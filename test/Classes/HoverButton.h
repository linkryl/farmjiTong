#pragma once
#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HoverButton : public cocos2d::ui::Button {
public:
  // ����һ���µ� HoverButton ʵ��
  static HoverButton* create(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

  // ��ʼ�� HoverButton ʵ��
  bool init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

private:
  std::string defaultButtonImage; // Ĭ��״̬��ťͼƬ·��
  std::string hoverButtonImage;   // ��ͣ״̬��ťͼƬ·��
  std::string activeButtonImage;  // ����״̬��ťͼƬ·��

  // ����ƶ��¼��Ĵ�����
  void onMouseMove(cocos2d::Event* event);

  // ����ͷ��¼��Ĵ�����
  void onMouseUp(cocos2d::Event* event);
};
#endif // !_HOVER_BUTTON_H_