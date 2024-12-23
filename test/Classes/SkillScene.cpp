//#include "SkillScene.h"
//#include "proj.win32/AudioPlayer.h"
//#include "proj.win32/HoverButton.h"
//#include "ui/CocosGUI.h"
//
//Scene* SkillScene::createScene()
//{
//  auto scene = Scene::create();
//  auto layer = create();
//  scene->addChild(layer);
//  return scene;
//}
//
//bool SkillScene::init()
//{
//  // 创建场景
//  if (!Scene::init())
//  {
//    return false;
//  }
//
//  //测试
//  Skill mySkill;
//  
//    // 加载人物图片"../Resources/" + std::to_string(itemId) + ".png"
//    const auto collectpng = Sprite::create("../Resources/CollectIcon.png"); // 未确定
//    collectpng->setContentSize(Size(100, 100));
//    collectpng->setPosition(Vec2(80, 650));
//    this->addChild(collectpng, 3);
//
//    auto collectLabel = Label::createWithSystemFont("Collect", "Arial", 24);
//    collectLabel->setPosition(Vec2(180, 650));
//    collectLabel->setColor(Color3B::BLACK);
//    this->addChild(collectLabel, 3);
//
//    for (int h = 0; h < 5; ++h)
//    {
//      if (h < mySkill.collect_level)
//      {
//        const auto level = Sprite::create("../Resources/SkillLevel.png"); // 未确定
//        level->setContentSize(Size(40, 40));
//        level->setPosition(Vec2(250 + h * 40, 650));
//        this->addChild(level, 3);
//      }
//      else
//      {
//        const auto delevel = Sprite::create("../Resources/SkillDelevel.png"); // 未确定
//        delevel->setContentSize(Size(40, 40));
//        delevel->setPosition(Vec2(250 + h * 40, 650));
//        this->addChild(delevel, 3);
//      }
//    }
//
//    // 加载人物图片"../Resources/" + std::to_string(itemId) + ".png"
//    const auto farmpng = Sprite::create("../Resources/FarmIcon.png"); // 未确定
//    farmpng->setContentSize(Size(100, 100));
//    farmpng->setPosition(Vec2(80, 550));
//    this->addChild(farmpng, 3);
//
//    auto farmLabel = Label::createWithSystemFont("Farm", "Arial", 24);
//    farmLabel->setPosition(Vec2(180, 550));
//    farmLabel->setColor(Color3B::BLACK);
//    this->addChild(farmLabel, 3);
//
//    for (int h = 0; h < 5; ++h)
//    {
//      if (h < mySkill.farm_level)
//      {
//        const auto level = Sprite::create("../Resources/SkillLevel.png"); // 未确定
//        level->setContentSize(Size(40, 40));
//        level->setPosition(Vec2(250 + h * 40, 550));
//        this->addChild(level, 3);
//      }
//      else
//      {
//        const auto delevel = Sprite::create("../Resources/SkillDelevel.png"); // 未确定
//        delevel->setContentSize(Size(40, 40));
//        delevel->setPosition(Vec2(250 + h * 40, 550));
//        this->addChild(delevel, 3);
//      }
//    }
//
//    // 加载人物图片"../Resources/" + std::to_string(itemId) + ".png"
//    const auto finshingpng = Sprite::create("../Resources/FishIcon.png"); // 未确定
//    finshingpng->setContentSize(Size(100, 100));
//    finshingpng->setPosition(Vec2(80, 450));
//    this->addChild(finshingpng, 3);
//
//    auto fishingLabel = Label::createWithSystemFont("Fishing", "Arial", 24);
//    fishingLabel->setPosition(Vec2(180, 450));
//    fishingLabel->setColor(Color3B::BLACK);
//    this->addChild(fishingLabel, 3);
//
//    for (int h = 0; h < 5; ++h)
//    {
//      if (h < mySkill.fishing_level)
//      {
//        const auto level = Sprite::create("../Resources/SkillLevel.png"); // 未确定
//        level->setContentSize(Size(40, 40));
//        level->setPosition(Vec2(250 + h * 40, 450));
//        this->addChild(level, 3);
//      }
//      else
//      {
//        const auto delevel = Sprite::create("../Resources/SkillDelevel.png"); // 未确定
//        delevel->setContentSize(Size(40, 40));
//        delevel->setPosition(Vec2(250 + h * 40, 450));
//        this->addChild(delevel, 3);
//      }
//    }
//
//  // 加载背景
//  const auto screenSize = Director::getInstance()->getVisibleSize();
//  const auto background = Sprite::create("../Resources/emptyscene.png");//未确定
//  background->setContentSize(screenSize);
//  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
//  this->addChild(background, 2);
//
//  // 创建返回游戏按钮
//  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
//    "../Resources/BackPressedButton.png",
//    "../Resources/BackDefaultButton.png");
//
//  backButton->setScale(0.46f);
//
//  // 设置返回按钮位置
//  backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));
//
//  // 为返回按钮添加事件处理器
//  backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
//    {
//      if (type == ui::Widget::TouchEventType::ENDED)
//      {
//        // 加载点击音效
//        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
//
//        Director::getInstance()->popScene();
//        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
//      }
//    });
//
//  // 将返回按钮添加到场景中
//  this->addChild(backButton, 3);
//
//  return true;
//}