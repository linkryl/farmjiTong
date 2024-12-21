#include "BagScene.h"
#include "proj.win32/AudioPlayer.h"
#include "proj.win32/HoverButton.h"
#include "ui/CocosGUI.h"

Scene* BagScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool BagScene::init()
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
  BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();

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