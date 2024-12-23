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
  // ��������
  if (!Scene::init())
  {
    return false;
  }

  //����
  SocialInfo npcs;
  Entrust en1("Abigail", "I need crops", "FarmIcon");
  Entrust en2("Alex", "I need fish", "FishIcon");
  npcs.add_entrust(en1);
  npcs.add_entrust(en2);
  auto j = npcs.entrusts.begin();
  for (size_t i = 0; i < npcs.entrusts.size(); ++i, ++j)
  {
    // ��������ͼƬ"../Resources/" + std::to_string(itemId) + ".png"
    const auto npcpng = Sprite::create("../Resources/" + j->master + ".png"); // δȷ��
    npcpng->setContentSize(Size(100, 100));
    npcpng->setPosition(Vec2(80, 650 - 100 * i));
    this->addChild(npcpng, 3);

    auto label = Label::createWithSystemFont(j->requirement, "Arial", 24);
    label->setPosition(Vec2(280, 650 - 100 * i));
    label->setColor(Color3B::BLACK);
    this->addChild(label, 3);

    const auto itempng = Sprite::create("../Resources/" + j->item + ".png"); // δȷ��
    itempng->setContentSize(Size(100, 100));
    itempng->setPosition(Vec2(540, 650 - 100 * i));
    this->addChild(itempng, 3);
    
    // ����������Ʒ��ť
    auto DeEntrust = HoverButton::create("../Resources/DecoopLevel.png",
      "../Resources/CoopLevel.png",
      "../Resources/CoopLevel.png");

    DeEntrust->setContentSize(Size(40, 40));;

    // ���ý�����Ʒ��ťλ��
    DeEntrust->setPosition(Vec2(700, 650 - 100 * i));

    // Ϊ������Ʒ��ť����¼�������
    DeEntrust->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
      {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
          // ���ص����Ч
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

          //�˴�Ӧ��������������,����һ��ö����ʹ�����ƺͱ�Ŷ�Ӧ
          //Director::getInstance()->popScene();
          //Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, StartupScene::createScene(), Color3B::WHITE));
        }
      });

    // ��������Ʒ��ť��ӵ�������
    this->addChild(DeEntrust, 3);
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
  this->addChild(backButton, 3);

  return true;
}