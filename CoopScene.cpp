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
  // ��������
  if (!Scene::init())
  {
    return false;
  }

  //����
  SocialInfo npcs;
  npcs.add_NPC("Abigail");
  npcs.add_NPC("Alex");
  npcs.increase_favorability("Abigail");
  std::vector<std::string> ::iterator j = npcs.NPC_names.begin();
  auto l = npcs.favorabilities.begin();
  for (size_t i = 0; i < npcs.favorabilities.size(); ++i,++j ,++l)
  {
    // ��������ͼƬ"../Resources/" + std::to_string(itemId) + ".png"
    const auto npcpng = Sprite::create("../Resources/" + *j + ".png"); // δȷ��
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
        const auto level = Sprite::create("../Resources/CoopLevel.png"); // δȷ��
        level->setContentSize(Size(40, 40));
        level->setPosition(Vec2(250 + h * 40, 650 - 100 * i));
        this->addChild(level, 3);
      }
      else
      {
        const auto delevel = Sprite::create("../Resources/DecoopLevel.png"); // δȷ��
        delevel->setContentSize(Size(40, 40));
        delevel->setPosition(Vec2(250 + h * 40, 650 - 100 * i));
        this->addChild(delevel, 3);
      }
    }

  }
  // ���ر���
  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/emptyscene.png");//δȷ��
  background->setContentSize(screenSize);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background, 2);

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
  this->addChild(backButton,3);
  
  return true;
}