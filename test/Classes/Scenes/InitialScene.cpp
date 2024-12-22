#include <locale>
#include <codecvt>
#include "InitialScene.h"
#include "HoverButton.h"
#include "Constant.h"
#include "AudioPlayer.h"
#include "StartupScene.h"
#include "BackpackManager.h"

// ��������
Scene* InitialScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool InitialScene::init()
{
  // ��������
  if (!Scene::init())
  {
    return false;
  }
  
  // ���ر���
  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/initialscene.png");
  background->setContentSize(screenSize);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background);

  // ����������Ϸ��ť
  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
    "../Resources/BackPressedButton.png",
    "../Resources/BackDefaultButton.png");

  backButton->setScale(0.46f);

  // ���÷��ذ�ťλ��
  backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

  // Ϊ���ذ�ť����¼�������
  backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        Director::getInstance()->popScene();
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(backButton);

  // ����������ť
  auto bagButton = HoverButton::create("../Resources/BackHold.png",
    "../Resources/BackHold.png",
    "../Resources/BackHold.png");

  bagButton->setScale(0.46f);

  // ���ñ�����ťλ��
  bagButton->setPosition(Vec2(screenSize.width / 2 + 365, screenSize.height / 2 + 127));

  // Ϊ������ť����¼�������
  bagButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        // ����������Ϸ��ť
        auto backButton = HoverButton::create("../Resources/ExitBack.png",
          "../Resources/ExitPressed.png",
          "../Resources/ExitBack.png");

        backButton->setScale(0.46f);

        const auto screenSize = Director::getInstance()->getVisibleSize();

        // ���÷��ذ�ťλ��
        backButton->setPosition(Vec2(screenSize.width / 2 + 165, screenSize.height / 2 + 327));

        // Ϊ���ذ�ť����¼�������
        backButton->addTouchEventListener([this, backButton](Ref* sender, ui::Widget::TouchEventType type)
          {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
              // ���ص����Ч
              audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
              
              BackpackManager::getInstance()->hideBackpack();
              this->removeChild(backButton);
            }
          });

        // �����ذ�ť��ӵ�������
        this->addChild(backButton);
        //BackpackManager::getInstance()->showBackpack(this);
      }
    });

  // ��������ť��ӵ�������
  this->addChild(bagButton);

  return true;
}