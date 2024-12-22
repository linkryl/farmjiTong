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

// 创建场景
Scene* InitialScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool InitialScene::init()
{
  // 创建场景
  if (!Scene::init())
  {
    return false;
  }
  
  // 加载背景
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
        // 如果标签不存在，则创建并显示它
        if (!_label)
        {
          _label = Label::createWithTTF("Day: 0, Hour: 0, Weather: 1", "fonts/Marker Felt.ttf", 24);
          _label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 481,
            Director::getInstance()->getVisibleSize().height / 2 + 315));
          _label->setColor(Color3B::BLACK);
          this->addChild(_label, 10);

          // 初始化时间系统并安排更新标签
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
        // 如果标签存在，则移除它
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

  // 创建返回游戏按钮
  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
    "../Resources/BackPressedButton.png",
    "../Resources/BackDefaultButton.png");

  backButton->setScale(0.46f);

  // 设置返回按钮位置
  backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

  // 为返回按钮添加事件处理器
  backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        Director::getInstance()->popScene();
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(backButton);
 
  auto clothright = HoverButton::create("../Resources/rightarrow.png",
    "../Resources/rightarrow.png",
    "../Resources/rightarrow.png");

  clothright->setScale(0.2f);

  // 设置返回按钮位置
  clothright->setPosition(Vec2(screenSize.width / 2 + 32, screenSize.height / 2 - 50));

  // 为返回按钮添加事件处理器
  clothright->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //更换衣服的逻辑
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(clothright);

  auto clothleft = HoverButton::create("../Resources/leftarrow.png",
    "../Resources/leftarrow.png",
    "../Resources/leftarrow.png");

  clothleft->setScale(0.2f);

  // 设置返回按钮位置
  clothleft->setPosition(Vec2(screenSize.width / 2 - 36, screenSize.height / 2 - 50));

  // 为返回按钮添加事件处理器
  clothleft->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //更换衣服的逻辑
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(clothleft);

  auto hatright = HoverButton::create("../Resources/rightarrow.png",
    "../Resources/rightarrow.png",
    "../Resources/rightarrow.png");

  hatright->setScale(0.2f);

  // 设置返回按钮位置
  hatright->setPosition(Vec2(screenSize.width / 2 + 32, screenSize.height / 2 - 20));

  // 为返回按钮添加事件处理器
  hatright->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //更换帽子的逻辑
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(hatright);

  auto hatleft = HoverButton::create("../Resources/leftarrow.png",
    "../Resources/leftarrow.png",
    "../Resources/leftarrow.png");

  hatleft->setScale(0.2f);

  // 设置返回按钮位置
  hatleft->setPosition(Vec2(screenSize.width / 2 - 36, screenSize.height / 2 - 20));

  // 为返回按钮添加事件处理器
  hatleft->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //更换帽子的逻辑
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(hatleft);

  auto okButton = HoverButton::create("../Resources/okDefaultButton.png",
    "../Resources/okPressedButton.png",
    "../Resources/okPressedButton.png");

  okButton->setScale(0.45f);

  // 设置返回按钮位置
  okButton->setPosition(Vec2(screenSize.width / 2 + 135, screenSize.height / 2 - 140));

  // 为返回按钮添加事件处理器
  okButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //进入正式游戏的逻辑
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(okButton);

  auto randButton = HoverButton::create("../Resources/randButton.png",
    "../Resources/randButton.png",
    "../Resources/randButton.png");

  randButton->setScale(0.28f);

  // 设置返回按钮位置
  randButton->setPosition(Vec2(screenSize.width / 2 - 54, screenSize.height / 2 + 145));

  // 为返回按钮添加事件处理器
  randButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        //随机获得衣物的逻辑
        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(randButton);

  return true;
}
/*
 // 创建返回游戏按钮
 auto cButton = HoverButton::create("../Resources/BackDefaultButton.png",
   "../Resources/BackPressedButton.png",
   "../Resources/BackDefaultButton.png");

 cButton->setScale(0.46f);

 // 设置返回按钮位置
 cButton->setPosition(Vec2(screenSize.width / 2 + 465, screenSize.height / 2 - 327));

 // 为返回按钮添加事件处理器
 cButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // 加载点击音效
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

       Director::getInstance()->pushScene(CoopScene::createScene());
       //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
     }
   });

 // 将返回按钮添加到场景中
 this->addChild(cButton);

 auto cB = HoverButton::create("../Resources/BackDefaultButton.png",
   "../Resources/BackPressedButton.png",
   "../Resources/BackDefaultButton.png");

 cB->setScale(0.46f);

 // 设置返回按钮位置
 cB->setPosition(Vec2(screenSize.width / 2 + 365, screenSize.height / 2 - 327));

 // 为返回按钮添加事件处理器
 cB->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // 加载点击音效
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

       Director::getInstance()->pushScene(EntrustScene::createScene());
     }
   });

 // 将返回按钮添加到场景中
 this->addChild(cB);

 // 创建背包按钮
 auto bagButton = HoverButton::create("../Resources/BackHold.png",
   "../Resources/BackHold.png",
   "../Resources/BackHold.png");

 bagButton->setScale(0.46f);

 // 设置背包按钮位置
 bagButton->setPosition(Vec2(screenSize.width / 2 + 365, screenSize.height / 2 + 127));

 // 为背包按钮添加事件处理器
 bagButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       Director::getInstance()->pushScene(BagScene::createScene());
     }
   });

 // 将背包按钮添加到场景中
 this->addChild(bagButton);

 // 创建商店按钮
 auto storeButton = HoverButton::create("../Resources/store.png",
   "../Resources/store.png",
   "../Resources/store.png");

 // 设置商店按钮位置
 storeButton->setPosition(Vec2(screenSize.width / 2 + 365, screenSize.height / 2 + 227));

 // 为商店按钮添加事件处理器
 storeButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // 加载点击音效
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
       Director::getInstance()->pushScene(StoreScene::createScene());
       //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
     }
   });

 // 将商店按钮添加到场景中
 this->addChild(storeButton);

 // 创建商店按钮
 auto dealButton = HoverButton::create("../Resources/deal.png",
   "../Resources/deal.png",
   "../Resources/deal.png");

 // 设置商店按钮位置
 dealButton->setPosition(Vec2(screenSize.width / 2 + 425, screenSize.height / 2 + 227));

 // 为商店按钮添加事件处理器
 dealButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
   {
     if (type == ui::Widget::TouchEventType::ENDED)
     {
       // 加载点击音效
       audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
       Director::getInstance()->pushScene(DealScene::createScene());
       //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
     }
   });

 // 将商店按钮添加到场景中
 this->addChild(dealButton);
 */