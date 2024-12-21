#include "StoreScene.h"
#include "proj.win32/AudioPlayer.h"
#include "proj.win32/HoverButton.h"
#include "BackpackManager.h"
#include "BackpackLayer.h"
#include "ui/CocosGUI.h"

Scene* StoreScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool StoreScene::init()
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
  // 创建蔬菜种子按钮
  auto vegetableSeed = HoverButton::create("../Resources/Item/1100.png",
    "../Resources/Item/1100.png",
    "../Resources/Item/1100.png");

  // 设置蔬菜种子按钮位置
  vegetableSeed->setPosition(Vec2(160, 650));

  // 为蔬菜种子按钮添加事件处理器
  vegetableSeed->addClickEventListener([this](Ref* sender)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

      auto popupLayer = Sprite::create("../Resources/emptyscene.png");
      popupLayer->setContentSize(Size(200, 200));
      popupLayer->setPosition(Vec2(160, 450));

      // 创建退出按钮
      auto backButton = ui::Button::create("ExitButton.png", "ExitPressed.png");
      backButton->setScale(0.2f);
      backButton->setPosition(Vec2(190, 380));

      // 添加按钮点击事件
      backButton->addClickEventListener([this, popupLayer](Ref* sender) {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        popupLayer->removeFromParentAndCleanup(true);
        });

      // 将按钮添加到小窗口 Layer
      popupLayer->addChild(backButton);

      auto buyButton = ui::Button::create("BuyDefaultButton.png", "BuyPressedButton.png");
      buyButton->setScale(0.4f);
      buyButton->setPosition(Vec2(100, 280));

      // 添加按钮点击事件
      buyButton->addClickEventListener([this, popupLayer](Ref* sender)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
          Bag::getInstance()->addItem(1100, 1);
          if (Bag::getInstance()->_items[4001] >= 10)
            Bag::getInstance()->removeItem(4001,10);
          else
            log("money is not enough");
          BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();
        //BackpackManager::getInstance()->addItem()
        });
      // 将按钮添加到小窗口
      popupLayer->addChild(buyButton);

      this->addChild(popupLayer, 4);
    });
  // 将蔬菜种子按钮添加到场景中
  this->addChild(vegetableSeed, 4);

  auto vegetablelabel = Label::createWithSystemFont("vegetable seed", "Arial", 24);
  vegetablelabel->setPosition(Vec2(160, 580));
  vegetablelabel->setColor(Color3B::BLACK);
  this->addChild(vegetablelabel, 4);

  auto vegetableprice = Label::createWithSystemFont("10", "Arial", 24);
  vegetableprice->setPosition(Vec2(150, 550));
  vegetableprice->setColor(Color3B::BLACK);
  this->addChild(vegetableprice, 4);

  const auto coin1 = Sprite::create("../Resources/coin.png");//未确定
  coin1->setContentSize(Size(25, 25));
  coin1->setPosition(Vec2(180, 550));
  this->addChild(coin1, 4);
  //
// 创建谷物种子按钮
  auto cropSeed = HoverButton::create("../Resources/Item/1101.png",
    "../Resources/Item/1101.png",
    "../Resources/Item/1101.png");

  // 设置谷物种子按钮位置
  cropSeed->setPosition(Vec2(360, 650));

  // 为谷物种子按钮添加事件处理器
  cropSeed->addClickEventListener([this](Ref* sender)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
      Bag::getInstance()->addItem(1101, 1);
      if (Bag::getInstance()->_items[4001] >= 10)
        Bag::getInstance()->removeItem(4001, 10);
      else
        log("money is not enough");
      BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();
    });
  // 将蔬菜种子按钮添加到场景中
  this->addChild(cropSeed, 4);

  auto croplabel = Label::createWithSystemFont("crop seed", "Arial", 24);
  croplabel->setPosition(Vec2(360, 580));
  croplabel->setColor(Color3B::BLACK);
  this->addChild(croplabel, 4);

  auto cropprice = Label::createWithSystemFont("10", "Arial", 24);
  cropprice->setPosition(Vec2(350, 550));
  cropprice->setColor(Color3B::BLACK);
  this->addChild(cropprice, 4);

  const auto coin2 = Sprite::create("../Resources/coin.png");//未确定
  coin2->setContentSize(Size(25, 25));
  coin2->setPosition(Vec2(380, 550));
  this->addChild(coin2, 4);
  //
// 创建肥料按钮
  auto fertilizer = HoverButton::create("../Resources/Item/1102.png",
    "../Resources/Item/1102.png",
    "../Resources/Item/1102.png");

  // 设置肥料按钮位置
  fertilizer->setPosition(Vec2(560, 650));

  // 为肥料按钮添加事件处理器
  fertilizer->addClickEventListener([this](Ref* sender)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
      Bag::getInstance()->addItem(1102, 1);
      if (Bag::getInstance()->_items[4001] >= 10)
        Bag::getInstance()->removeItem(4001, 10);
      else
        log("money is not enough");
      BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();
    });
  // 将蔬菜种子按钮添加到场景中
  this->addChild(fertilizer, 4);

  auto fertilizerlabel = Label::createWithSystemFont("fertilizer", "Arial", 24);
  fertilizerlabel->setPosition(Vec2(560, 580));
  fertilizerlabel->setColor(Color3B::BLACK);
  this->addChild(fertilizerlabel, 4);

  auto fertilizerprice = Label::createWithSystemFont("10", "Arial", 24);
  fertilizerprice->setPosition(Vec2(550, 550));
  fertilizerprice->setColor(Color3B::BLACK);
  this->addChild(fertilizerprice, 4);

  const auto coin3 = Sprite::create("../Resources/coin.png");//未确定
  coin3->setContentSize(Size(25, 25));
  coin3->setPosition(Vec2(580, 550));
  this->addChild(coin3, 4);
  //
// 创建猪按钮
  auto pig = HoverButton::create("../Resources/Item/1103.png",
    "../Resources/Item/1103.png",
    "../Resources/Item/1103.png");

  // 设置猪按钮位置
  pig->setPosition(Vec2(760, 650));

  // 为猪按钮添加事件处理器
  pig->addClickEventListener([this](Ref* sender)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
      Bag::getInstance()->addItem(1103, 1);
      if (Bag::getInstance()->_items[4001] >= 10)
        Bag::getInstance()->removeItem(4001, 10);
      else
        log("money is not enough");
      BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();
    });
  // 将猪按钮添加到场景中
  this->addChild(pig, 4);

  auto piglabel = Label::createWithSystemFont("pig", "Arial", 24);
  piglabel->setPosition(Vec2(760, 580));
  piglabel->setColor(Color3B::BLACK);
  this->addChild(piglabel, 4);

  auto pigprice = Label::createWithSystemFont("10", "Arial", 24);
  pigprice->setPosition(Vec2(750, 550));
  pigprice->setColor(Color3B::BLACK);
  this->addChild(pigprice, 4);

  const auto coin4 = Sprite::create("../Resources/coin.png");//未确定
  coin4->setContentSize(Size(25, 25));
  coin4->setPosition(Vec2(780, 550));
  this->addChild(coin4, 4);

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