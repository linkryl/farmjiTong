#include "StartupScene.h"
#include "InitialScene.h"
#include "Constant.h"
#include "AudioPlayer.h"
#include "HoverButton.h"
#include "InitialScene.h"
#include "SettingsScene.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* StartupScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

// on "init" you need to initialize your instance
bool StartupScene::init()
{
    // ��������
    if ( !Scene::init() )
    {
        return false;
    }

    // ��������
    audioPlayer("../Resources/Music/stardew.mp3", true);//δȷ��

    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/startgamescene.png");//δȷ��
    background->setContentSize(screenSize);
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ʼ��Ϸ��ť
    auto startButton = HoverButton::create("../Resources/StartDefaultButton.png",
      "../Resources/StartPressedButton.png",
      "../Resources/StartDefaultButton.png");

    startButton->setScale(0.51f * 1.25);

    // ���ÿ�ʼ��Ϸ��ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2 - 185*1.25, screenSize.height / 2 - 311 * 1.25));
    // Ϊ��ʼ��Ϸ��ť����¼�������
    startButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        //Director::getInstance()->pushScene(CoopScene::createScene());
        //Director::getInstance()->pushScene(SkillScene::createScene());
        Director::getInstance()->pushScene(InitialScene::createScene());
        //Director::getInstance()->pushScene(EntrustScene::createScene());

      }
    });

    // ����ʼ��Ϸ��ť��ӵ�������
    this->addChild(startButton);

    // ����������Ϸ��ť
    auto loadButton = HoverButton::create("../Resources/LoadDefaultButton.png",
      "../Resources/LoadPressedButton.png",
      "../Resources/LoadDefaultButton.png");

    loadButton->setScale(0.51f * 1.25);

    // ����������Ϸ��ťλ��
    loadButton->setPosition(Vec2(screenSize.width / 2 - 61 * 1.25, screenSize.height / 2 - 311 * 1.25));

    // Ϊ������Ϸ��ť����¼�������
    loadButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // ���ص����Ч
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
        }
      });

    // ��������Ϸ��ť��ӵ�������
    this->addChild(loadButton);

    // ����������Ϸ��ť
    auto coopButton = HoverButton::create("../Resources/CoopDefaultButton.png",
      "../Resources/CoopPressedButton.png",
      "../Resources/CoopDefaultButton.png");

    coopButton->setScale(0.51f * 1.25);

    // ����������Ϸ��ťλ��
    coopButton->setPosition(Vec2(screenSize.width / 2 + 61 * 1.25, screenSize.height / 2 - 311 * 1.25));

    // Ϊ������Ϸ��ť����¼�������
    coopButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // ���ص����Ч
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
        }
      });

    // ��������Ϸ��ť��ӵ�������
    this->addChild(coopButton);

    // �����˳���Ϸ��ť
    auto exitButton = HoverButton::create("../Resources/ExitDefaultButton.png",
      "../Resources/ExitPressedButton.png",
      "../Resources/ExitDefaultButton.png");

    exitButton->setScale(0.51f * 1.25);

    // �����˳���Ϸ��ťλ��
    exitButton->setPosition(Vec2(screenSize.width / 2 + 184 * 1.25, screenSize.height / 2 - 311 * 1.25));

    // Ϊ�˳���Ϸ��ť����¼�������
    exitButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // ���ص����Ч
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          // �˳�����
          Director::getInstance()->end();
        }
      });

    // ���˳���Ϸ��ť��ӵ�������
    this->addChild(exitButton);

    // �������ð�ť
    auto setButton = HoverButton::create("../Resources/SetButtonDefault.png",
      "../Resources/SetButtonPressed.png",
      "../Resources/SetButtonDefault.png");

    setButton->setScale(0.3f * 1.25);

    // �������ð�ťλ��
    setButton->setPosition(Vec2(screenSize.width / 2 - 621 * 1.25, screenSize.height / 2 + 345 * 1.25));

    // Ϊ���ð�ť����¼�������
    setButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // ���ص����Ч
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          Director::getInstance()->pushScene(SettingsScene::createScene());
        }
      });

    // �����ð�ť��ӵ�������
    this->addChild(setButton);

    return true;
}