#include "DealScene.h"
#include "proj.win32/AudioPlayer.h"
#include "proj.win32/HoverButton.h"
#include "BackpackManager.h"
#include "BackpackLayer.h"
#include "ui/CocosGUI.h"

Scene* DealScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool DealScene::init()
{
  // 创建场景
  if (!Scene::init())
  {
    return false;
  }

  // 加载背景

  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/emptyscene.png");//未确定
  background->setContentSize(screenSize);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background, 2);

  BackpackManager::getInstance()->showBackpack(this, 4);
  //测试
  //
// 创建面包按钮
  auto bread = HoverButton::create("../Resources/Item/4101.png",
    "../Resources/Item/4101.png",
    "../Resources/Item/4101.png");

  // 设置面包按钮位置
  bread->setPosition(Vec2(760, 650));

  // 为面包按钮添加事件处理器
  bread->addClickEventListener([this](Ref* sender)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
      if (Bag::getInstance()->_items[3101]>=2)
      {
        Bag::getInstance()->addItem(4101, 1);
        Bag::getInstance()->removeItem(3101, 2);
      }

    });
  // 将面包按钮添加到场景中
  this->addChild(bread, 4);

  auto breadlabel = Label::createWithSystemFont("bread", "Arial", 24);
  breadlabel->setPosition(Vec2(760, 580));
  breadlabel->setColor(Color3B::BLACK);
  this->addChild(breadlabel, 4);

  auto breadprice = Label::createWithSystemFont("2", "Arial", 24);
  breadprice->setPosition(Vec2(750, 550));
  breadprice->setColor(Color3B::BLACK);
  this->addChild(breadprice, 4);

  const auto resource = Sprite::create("../Resources/Item/3101.png");//未确定
  resource->setContentSize(Size(25, 25));
  resource->setPosition(Vec2(780, 550));
  this->addChild(resource, 4);

  // 创建返回游戏按钮
  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
    "../Resources/BackPressedButton.png",
    "../Resources/BackDefaultButton.png");

  backButton->setScale(0.46f);

  // 设置返回按钮位置
  //screenSize.width / 2 + 565, screenSize.height / 2 - 327
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
  this->addChild(backButton, 3);

  return true;
}