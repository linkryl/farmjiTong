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
    // 创建场景
    if ( !Scene::init() )
    {
        return false;
    }

    // 加载音乐
    audioPlayer("../Resources/Music/stardew.mp3", true);//未确定

    // 加载背景
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/startgamescene.png");//未确定
    background->setContentSize(screenSize);
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建开始游戏按钮
    auto startButton = HoverButton::create("../Resources/StartDefaultButton.png",
      "../Resources/StartPressedButton.png",
      "../Resources/StartDefaultButton.png");

    startButton->setScale(0.51f * 1.25);

    // 设置开始游戏按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2 - 185*1.25, screenSize.height / 2 - 311 * 1.25));
    // 为开始游戏按钮添加事件处理器
    startButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        //Director::getInstance()->pushScene(CoopScene::createScene());
        //Director::getInstance()->pushScene(SkillScene::createScene());
        Director::getInstance()->pushScene(InitialScene::createScene());
        //Director::getInstance()->pushScene(EntrustScene::createScene());

      }
    });

    // 将开始游戏按钮添加到场景中
    this->addChild(startButton);

    // 创建载入游戏按钮
    auto loadButton = HoverButton::create("../Resources/LoadDefaultButton.png",
      "../Resources/LoadPressedButton.png",
      "../Resources/LoadDefaultButton.png");

    loadButton->setScale(0.51f * 1.25);

    // 设置载入游戏按钮位置
    loadButton->setPosition(Vec2(screenSize.width / 2 - 61 * 1.25, screenSize.height / 2 - 311 * 1.25));

    // 为载入游戏按钮添加事件处理器
    loadButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
        }
      });

    // 将载入游戏按钮添加到场景中
    this->addChild(loadButton);

    // 创建联机游戏按钮
    auto coopButton = HoverButton::create("../Resources/CoopDefaultButton.png",
      "../Resources/CoopPressedButton.png",
      "../Resources/CoopDefaultButton.png");

    coopButton->setScale(0.51f * 1.25);

    // 设置联机游戏按钮位置
    coopButton->setPosition(Vec2(screenSize.width / 2 + 61 * 1.25, screenSize.height / 2 - 311 * 1.25));

    // 为联机游戏按钮添加事件处理器
    coopButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE));
        }
      });

    // 将联机游戏按钮添加到场景中
    this->addChild(coopButton);

    // 创建退出游戏按钮
    auto exitButton = HoverButton::create("../Resources/ExitDefaultButton.png",
      "../Resources/ExitPressedButton.png",
      "../Resources/ExitDefaultButton.png");

    exitButton->setScale(0.51f * 1.25);

    // 设置退出游戏按钮位置
    exitButton->setPosition(Vec2(screenSize.width / 2 + 184 * 1.25, screenSize.height / 2 - 311 * 1.25));

    // 为退出游戏按钮添加事件处理器
    exitButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          // 退出程序
          Director::getInstance()->end();
        }
      });

    // 将退出游戏按钮添加到场景中
    this->addChild(exitButton);

    // 创建设置按钮
    auto setButton = HoverButton::create("../Resources/SetButtonDefault.png",
      "../Resources/SetButtonPressed.png",
      "../Resources/SetButtonDefault.png");

    setButton->setScale(0.3f * 1.25);

    // 设置设置按钮位置
    setButton->setPosition(Vec2(screenSize.width / 2 - 621 * 1.25, screenSize.height / 2 + 345 * 1.25));

    // 为设置按钮添加事件处理器
    setButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          Director::getInstance()->pushScene(SettingsScene::createScene());
        }
      });

    // 将设置按钮添加到场景中
    this->addChild(setButton);

    return true;
}