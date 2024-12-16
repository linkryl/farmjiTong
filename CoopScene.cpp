#include "CoopScene.h"
#include "proj.win32/AudioPlayer.h"
#include "proj.win32/HoverButton.h"
#include "ui/CocosGUI.h"

Scene* CoopScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool CoopScene::init()
{
  // 创建场景
  if (!Scene::init())
  {
    return false;
  }

  //测试
  SocialInfo npcs;
  npcs.add_NPC("Abigail");
  npcs.add_NPC("Alex");
  npcs.increase_favorability("Abigail");
  std::vector<std::string> ::iterator j = npcs.NPC_names.begin();
  auto l = npcs.favorabilities.begin();
  for (size_t i = 0; i < npcs.favorabilities.size(); ++i,++j ,++l)
  {
    // 加载人物图片"../Resources/" + std::to_string(itemId) + ".png"
    const auto npcpng = Sprite::create("../Resources/" + *j + ".png"); // 未确定
    npcpng->setContentSize(Size(100, 100));
    npcpng->setPosition(Vec2(80,650-100*i));
    this->addChild(npcpng, 3);

    auto label = Label::createWithSystemFont(*j, "Arial", 24);
    label->setPosition(Vec2(180, 650 - 100 * i));
    label->setColor(Color3B::BLACK);
    this->addChild(label, 3);

    for (int h=0;h < 10;++h)
    {
      if (h<l->second)
      {
        const auto level = Sprite::create("../Resources/CoopLevel.png"); // 未确定
        level->setContentSize(Size(40, 40));
        level->setPosition(Vec2(250 + h * 40, 650 - 100 * i));
        this->addChild(level, 3);
      }
      else
      {
        const auto delevel = Sprite::create("../Resources/DecoopLevel.png"); // 未确定
        delevel->setContentSize(Size(40, 40));
        delevel->setPosition(Vec2(250 + h * 40, 650 - 100 * i));
        this->addChild(delevel, 3);
      }
    }

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
  this->addChild(backButton,3);
  
  return true;
}