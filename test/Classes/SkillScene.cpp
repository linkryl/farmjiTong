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
//  // ��������
//  if (!Scene::init())
//  {
//    return false;
//  }
//
//  //����
//  Skill mySkill;
//  
//    // ��������ͼƬ"../Resources/" + std::to_string(itemId) + ".png"
//    const auto collectpng = Sprite::create("../Resources/CollectIcon.png"); // δȷ��
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
//        const auto level = Sprite::create("../Resources/SkillLevel.png"); // δȷ��
//        level->setContentSize(Size(40, 40));
//        level->setPosition(Vec2(250 + h * 40, 650));
//        this->addChild(level, 3);
//      }
//      else
//      {
//        const auto delevel = Sprite::create("../Resources/SkillDelevel.png"); // δȷ��
//        delevel->setContentSize(Size(40, 40));
//        delevel->setPosition(Vec2(250 + h * 40, 650));
//        this->addChild(delevel, 3);
//      }
//    }
//
//    // ��������ͼƬ"../Resources/" + std::to_string(itemId) + ".png"
//    const auto farmpng = Sprite::create("../Resources/FarmIcon.png"); // δȷ��
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
//        const auto level = Sprite::create("../Resources/SkillLevel.png"); // δȷ��
//        level->setContentSize(Size(40, 40));
//        level->setPosition(Vec2(250 + h * 40, 550));
//        this->addChild(level, 3);
//      }
//      else
//      {
//        const auto delevel = Sprite::create("../Resources/SkillDelevel.png"); // δȷ��
//        delevel->setContentSize(Size(40, 40));
//        delevel->setPosition(Vec2(250 + h * 40, 550));
//        this->addChild(delevel, 3);
//      }
//    }
//
//    // ��������ͼƬ"../Resources/" + std::to_string(itemId) + ".png"
//    const auto finshingpng = Sprite::create("../Resources/FishIcon.png"); // δȷ��
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
//        const auto level = Sprite::create("../Resources/SkillLevel.png"); // δȷ��
//        level->setContentSize(Size(40, 40));
//        level->setPosition(Vec2(250 + h * 40, 450));
//        this->addChild(level, 3);
//      }
//      else
//      {
//        const auto delevel = Sprite::create("../Resources/SkillDelevel.png"); // δȷ��
//        delevel->setContentSize(Size(40, 40));
//        delevel->setPosition(Vec2(250 + h * 40, 450));
//        this->addChild(delevel, 3);
//      }
//    }
//
//  // ���ر���
//  const auto screenSize = Director::getInstance()->getVisibleSize();
//  const auto background = Sprite::create("../Resources/emptyscene.png");//δȷ��
//  background->setContentSize(screenSize);
//  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
//  this->addChild(background, 2);
//
//  // ����������Ϸ��ť
//  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
//    "../Resources/BackPressedButton.png",
//    "../Resources/BackDefaultButton.png");
//
//  backButton->setScale(0.46f);
//
//  // ���÷��ذ�ťλ��
//  backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));
//
//  // Ϊ���ذ�ť����¼�������
//  backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
//    {
//      if (type == ui::Widget::TouchEventType::ENDED)
//      {
//        // ���ص����Ч
//        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
//
//        Director::getInstance()->popScene();
//        //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
//      }
//    });
//
//  // �����ذ�ť��ӵ�������
//  this->addChild(backButton, 3);
//
//  return true;
//}