#include <locale>
#include <codecvt>
#include "InitialScene.h"
#include "HoverButton.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"
#include "StartupScene.h"
#include "BackpackManager.h"
#include "BagScene.h"
#include "DealScene.h"
#include "StoreScene.h"
#include "CoopScene.h"
#include "EntrustScene.h"

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

  auto listener = EventListenerKeyboard::create();

  listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
      if (keyCode == EventKeyboard::KeyCode::KEY_P)
      {
        // �����ǩ�����ڣ��򴴽�����ʾ��
        if (!_label)
        {
          _label = Label::createWithTTF("Day: 0, Hour: 0, Weather: 1", "fonts/Marker Felt.ttf", 24);
          _label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 481,
            Director::getInstance()->getVisibleSize().height / 2 + 315));
          _label->setColor(Color3B::BLACK);
          this->addChild(_label, 10);

          // ��ʼ��ʱ��ϵͳ�����Ÿ��±�ǩ
          _timeSystem = Time_system::getInstance();
          this->schedule(schedule_selector(InitialScene::updateLabel), 1.0f);

          _item = Sprite::create("../Resources/Item/" + std::to_string(Bag::getInstance()->itemInHand) + ".png");
          _item->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 481,
            Director::getInstance()->getVisibleSize().height / 2 + 285));
          this->addChild(_item);
        }
      }
      else if (keyCode == EventKeyboard::KeyCode::KEY_K)
      {
        // �����ǩ���ڣ����Ƴ���
        if (_label)
        {
          this->unschedule(schedule_selector(InitialScene::updateLabel));
          this->removeChild(_label, true);
          this->removeChild(_item, true);
          _label = nullptr;
        }
      }
    };
  this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
 
  auto clothright = HoverButton::create("../Resources/rightarrow.png",
    "../Resources/rightarrow.png",
    "../Resources/rightarrow.png");

  clothright->setScale(0.2f);

  // ���÷��ذ�ťλ��
  clothright->setPosition(Vec2(screenSize.width / 2 + 32, screenSize.height / 2 - 50));

  // Ϊ���ذ�ť����¼�������
  clothright->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //�����·����߼�
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(clothright);

  auto clothleft = HoverButton::create("../Resources/leftarrow.png",
    "../Resources/leftarrow.png",
    "../Resources/leftarrow.png");

  clothleft->setScale(0.2f);

  // ���÷��ذ�ťλ��
  clothleft->setPosition(Vec2(screenSize.width / 2 - 36, screenSize.height / 2 - 50));

  // Ϊ���ذ�ť����¼�������
  clothleft->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //�����·����߼�
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(clothleft);

  auto hatright = HoverButton::create("../Resources/rightarrow.png",
    "../Resources/rightarrow.png",
    "../Resources/rightarrow.png");

  hatright->setScale(0.2f);

  // ���÷��ذ�ťλ��
  hatright->setPosition(Vec2(screenSize.width / 2 + 32, screenSize.height / 2 - 20));

  // Ϊ���ذ�ť����¼�������
  hatright->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //����ñ�ӵ��߼�
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(hatright);

  auto hatleft = HoverButton::create("../Resources/leftarrow.png",
    "../Resources/leftarrow.png",
    "../Resources/leftarrow.png");

  hatleft->setScale(0.2f);

  // ���÷��ذ�ťλ��
  hatleft->setPosition(Vec2(screenSize.width / 2 - 36, screenSize.height / 2 - 20));

  // Ϊ���ذ�ť����¼�������
  hatleft->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //����ñ�ӵ��߼�
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(hatleft);

  auto okButton = HoverButton::create("../Resources/okDefaultButton.png",
    "../Resources/okPressedButton.png",
    "../Resources/okPressedButton.png");

  okButton->setScale(0.45f);

  // ���÷��ذ�ťλ��
  okButton->setPosition(Vec2(screenSize.width / 2 + 135, screenSize.height / 2 - 140));

  // Ϊ���ذ�ť����¼�������
  okButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //������ʽ��Ϸ���߼�
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(okButton);

  auto randButton = HoverButton::create("../Resources/randButton.png",
    "../Resources/randButton.png",
    "../Resources/randButton.png");

  randButton->setScale(0.28f);

  // ���÷��ذ�ťλ��
  randButton->setPosition(Vec2(screenSize.width / 2 - 54, screenSize.height / 2 + 145));

  // Ϊ���ذ�ť����¼�������
  randButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //������������߼�
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(randButton);

  return true;
}
/*
 // ����������Ϸ��ť
 auto cButton = HoverButton::create("../Resources/BackDefaultButton.png",
   "../Resources/BackPressedButton.png",
   "../Resources/BackDefaultButton.png");

 cButton->setScale(0.46f);

 // ���÷��ذ�ťλ��
 cButton->setPosition(Vec2(screenSize.width / 2 + 465, screenSize.height / 2 - 327));

 // Ϊ���ذ�ť����¼�������
 cButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // ���ص����Ч
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

       Director::getInstance()->pushScene(CoopScene::createScene());
       //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
     }
   });

 // �����ذ�ť��ӵ�������
 this->addChild(cButton);

 auto cB = HoverButton::create("../Resources/BackDefaultButton.png",
   "../Resources/BackPressedButton.png",
   "../Resources/BackDefaultButton.png");

 cB->setScale(0.46f);

 // ���÷��ذ�ťλ��
 cB->setPosition(Vec2(screenSize.width / 2 + 365, screenSize.height / 2 - 327));

 // Ϊ���ذ�ť����¼�������
 cB->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // ���ص����Ч
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

       Director::getInstance()->pushScene(EntrustScene::createScene());
     }
   });

 // �����ذ�ť��ӵ�������
 this->addChild(cB);

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
       Director::getInstance()->pushScene(BagScene::createScene());
     }
   });

 // ��������ť��ӵ�������
 this->addChild(bagButton);

 // �����̵갴ť
 auto storeButton = HoverButton::create("../Resources/store.png",
   "../Resources/store.png",
   "../Resources/store.png");

 // �����̵갴ťλ��
 storeButton->setPosition(Vec2(screenSize.width / 2 + 365, screenSize.height / 2 + 227));

 // Ϊ�̵갴ť����¼�������
 storeButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // ���ص����Ч
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
       Director::getInstance()->pushScene(StoreScene::createScene());
       //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
     }
   });

 // ���̵갴ť��ӵ�������
 this->addChild(storeButton);

 // �����̵갴ť
 auto dealButton = HoverButton::create("../Resources/deal.png",
   "../Resources/deal.png",
   "../Resources/deal.png");

 // �����̵갴ťλ��
 dealButton->setPosition(Vec2(screenSize.width / 2 + 425, screenSize.height / 2 + 227));

 // Ϊ�̵갴ť����¼�������
 dealButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // ���ص����Ч
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
       Director::getInstance()->pushScene(DealScene::createScene());
       //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
     }
   });

 // ���̵갴ť��ӵ�������
 this->addChild(dealButton);
 */