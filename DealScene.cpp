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
  // ��������
  if (!Scene::init())
  {
    return false;
  }

  // ���ر���

  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/emptyscene.png");//δȷ��
  background->setContentSize(screenSize);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background, 2);

  BackpackManager::getInstance()->showBackpack(this, 4);
  //����
  //
// ���������ť
  auto bread = HoverButton::create("../Resources/Item/4101.png",
    "../Resources/Item/4101.png",
    "../Resources/Item/4101.png");

  // ���������ťλ��
  bread->setPosition(Vec2(760, 650));

  // Ϊ�����ť����¼�������
  bread->addClickEventListener([this](Ref* sender)
    {
      // ���ص����Ч
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
      if (Bag::getInstance()->_items[3101]>=2)
      {
        Bag::getInstance()->addItem(4101, 1);
        Bag::getInstance()->removeItem(3101, 2);
      }

    });
  // �������ť��ӵ�������
  this->addChild(bread, 4);

  auto breadlabel = Label::createWithSystemFont("bread", "Arial", 24);
  breadlabel->setPosition(Vec2(760, 580));
  breadlabel->setColor(Color3B::BLACK);
  this->addChild(breadlabel, 4);

  auto breadprice = Label::createWithSystemFont("2", "Arial", 24);
  breadprice->setPosition(Vec2(750, 550));
  breadprice->setColor(Color3B::BLACK);
  this->addChild(breadprice, 4);

  const auto resource = Sprite::create("../Resources/Item/3101.png");//δȷ��
  resource->setContentSize(Size(25, 25));
  resource->setPosition(Vec2(780, 550));
  this->addChild(resource, 4);

  // ����������Ϸ��ť
  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
    "../Resources/BackPressedButton.png",
    "../Resources/BackDefaultButton.png");

  backButton->setScale(0.46f);

  // ���÷��ذ�ťλ��
  //screenSize.width / 2 + 565, screenSize.height / 2 - 327
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