#include <locale>
#include <codecvt>
#include "InitialScene.h"
#include "HoverButton.h"
#include "Constant.h"
#include "AudioPlayer.h"
#include "StartupScene.h"
#include "BackpackManager.h"

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
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        // 创建返回游戏按钮
        auto backButton = HoverButton::create("../Resources/ExitBack.png",
          "../Resources/ExitPressed.png",
          "../Resources/ExitBack.png");

        backButton->setScale(0.46f);

        const auto screenSize = Director::getInstance()->getVisibleSize();

        // 设置返回按钮位置
        backButton->setPosition(Vec2(screenSize.width / 2 + 165, screenSize.height / 2 + 327));

        // 为返回按钮添加事件处理器
        backButton->addTouchEventListener([this, backButton](Ref* sender, ui::Widget::TouchEventType type)
          {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
              // 加载点击音效
              audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
              
              BackpackManager::getInstance()->hideBackpack();
              this->removeChild(backButton);
            }
          });

        // 将返回按钮添加到场景中
        this->addChild(backButton);
        //BackpackManager::getInstance()->showBackpack(this);
      }
    });

  // 将背包按钮添加到场景中
  this->addChild(bagButton);

  return true;
}