#include "EntrustScene.h"
#include "AudioPlayer.h"
#include "HoverButton.h"
#include "ui/CocosGUI.h"

Scene* EntrustScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool EntrustScene::init()
{
  // 创建场景
  if (!Scene::init())
  {
    return false;
  }

  //测试
  SocialInfo npcs;
  Entrust en1("Abigail", "I need crops", "FarmIcon");
  Entrust en2("Alex", "I need fish", "FishIcon");
  npcs.add_entrust(en1);
  npcs.add_entrust(en2);
  auto j = npcs.entrusts.begin();
  for (size_t i = 0; i < npcs.entrusts.size(); ++i, ++j)
  {
    // 加载人物图片"../Resources/" + std::to_string(itemId) + ".png"
    const auto npcpng = Sprite::create("../Resources/" + j->master + ".png"); // 未确定
    npcpng->setContentSize(Size(100, 100));
    npcpng->setPosition(Vec2(80, 650 - 100 * i));
    this->addChild(npcpng, 3);

    auto label = Label::createWithSystemFont(j->requirement, "Arial", 24);
    label->setPosition(Vec2(280, 650 - 100 * i));
    label->setColor(Color3B::BLACK);
    this->addChild(label, 3);

    const auto itempng = Sprite::create("../Resources/" + j->item + ".png"); // 未确定
    itempng->setContentSize(Size(100, 100));
    itempng->setPosition(Vec2(540, 650 - 100 * i));
    this->addChild(itempng, 3);
    
    // 创建交付物品按钮
    auto DeEntrust = HoverButton::create("../Resources/DecoopLevel.png",
      "../Resources/CoopLevel.png",
      "../Resources/CoopLevel.png");

    DeEntrust->setContentSize(Size(40, 40));;

    // 设置交付物品按钮位置
    DeEntrust->setPosition(Vec2(700, 650 - 100 * i));

    // 为交付物品按钮添加事件处理器
    DeEntrust->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          //此处应跟背包处做联动,构建一个枚举类使得名称和编号对应
          //Director::getInstance()->popScene();
          //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
        }
      });

    // 将交付物品按钮添加到场景中
    this->addChild(DeEntrust, 3);
  }
  // 加载背景
  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/emptyscene.png");//未确定
  background->setContentSize(screenSize);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background, 2);

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
  this->addChild(backButton, 3);

  return true;
}