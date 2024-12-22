#include <locale>
#include <codecvt>
#include "Time_system.h"
#include "InitialScene.h"
#include "HoverButton.h"
#include "Constant.h"
#include "AudioPlayer.h"
//#include "StartupScene.h"
#include "BackpackManager.h"
#include "Scenes/BagScene.h"
#include "DealScene.h"
#include "StoreScene.h"
#include "CoopScene.h"
#include "EntrustScene.h"
#include "Player.h"
#include "Scenes/FarmScene.h"

// ��������
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = create();
    scene->addChild(layer);
    return scene;
}

    int hat_num = 301;
    int shirt_num = 301;

bool InitialScene::init()
{
    // ��������
    if (!Scene::init())
    {
        return false;
    }


    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/initialscene.png");
    background->setContentSize(screenSize);
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    auto cloth = Sprite::create("../Resources/wearing/shirt/shirt_1/shirt_1.png");
    cloth->setContentSize(Size(50, 50));
    cloth->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 130));
    this->addChild(cloth);
    auto hat = Sprite::create("../Resources/wearing/hat/hat_1/hat_1.png");
    hat->setContentSize(Size(50, 50));
    hat->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 180));
    this->addChild(hat);

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_P)
            {
                // �����ǩ�����ڣ��򴴽�����ʾ��
                if (!_label)
                {
                    _label = Label::createWithTTF("Day: 0, Hour: 0, Weather: 1", "fonts/Marker Felt.ttf", 24);
                    _label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 601.25,
                        Director::getInstance()->getVisibleSize().height / 2 + 393.75));
                    _label->setColor(Color3B::BLACK);
                    this->addChild(_label, 10);

                    // ��ʼ��ʱ��ϵͳ�����Ÿ��±�ǩ
                    _timeSystem = Time_system::getInstance();
                    this->schedule(schedule_selector(InitialScene::updateLabel), 1.0f);

                    _health_label = Label::createWithTTF("Health:"+std::to_string(Player::getInstance()->getHp()), "fonts/Marker Felt.ttf", 24);
                    _health_label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 601.25,
                        Director::getInstance()->getVisibleSize().height / 2 + 333.75));
                    _health_label->setColor(Color3B::BLACK);
                    this->addChild(_health_label, 10);

                    _item = Sprite::create("../Resources/Item/" + std::to_string(Bag::getInstance()->itemInHand) + ".png");
                    _item->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + 601.25,
                        Director::getInstance()->getVisibleSize().height / 2 + 363.75));
                    this->addChild(_item);


                }
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_K)
            {
                // �����ǩ���ڣ����Ƴ���
                if (_label)
                {
                    this->unschedule(schedule_selector(InitialScene::updateLabel));
                    this->removeChild(_label, true);
                    this->removeChild(_item, true);
                    this->removeChild(_health_label, true);
                    _label = nullptr;
                }
            }
        };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ����������Ϸ��ť
    auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
        "../Resources/BackPressedButton.png",
        "../Resources/BackDefaultButton.png");

    backButton->setScale(0.575f);

    // ���÷��ذ�ťλ��
    backButton->setPosition(Vec2(screenSize.width / 2 + 706.25, screenSize.height / 2 - 408.75));

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
    this->addChild(backButton);

    auto clothright = HoverButton::create("../Resources/rightarrow.png",
        "../Resources/rightarrow.png",
        "../Resources/rightarrow.png");

    clothright->setScale(0.25f);

    // ���÷��ذ�ťλ��
    clothright->setPosition(Vec2(screenSize.width / 2 + 40, screenSize.height / 2 - 62.5));

    // Ϊ���ذ�ť����¼�������
    clothright->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
        {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                // ���ص����Ч
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                ++shirt_num;
            }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(clothright);

    auto clothleft = HoverButton::create("../Resources/leftarrow.png",
        "../Resources/leftarrow.png",
        "../Resources/leftarrow.png");

    clothleft->setScale(0.25f);

    // ���÷��ذ�ťλ��
    clothleft->setPosition(Vec2(screenSize.width / 2 - 45, screenSize.height / 2 - 62.5));

    // Ϊ���ذ�ť����¼�������
    clothleft->addTouchEventListener([this, screenSize,&cloth](Ref* sender, ui::Widget::TouchEventType type)
        {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                // ���ص����Ч
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                --shirt_num;
                /*this->removeChild(cloth);
                cloth = Sprite::create("../Resources/wearing/shirt/shirt_" + std::to_string(shirt_num % 2 + 1) + "/shirt_" + std::to_string(shirt_num % 2 + 1) + ".png");
                cloth->setContentSize(Size(50, 50));
                cloth->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 130));
                this->addChild(cloth);*/
            }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(clothleft);

    auto hatright = HoverButton::create("../Resources/hatrightarrow.png",
        "../Resources/hatrightarrow.png",
        "../Resources/hatrightarrow.png");

    hatright->setScale(0.25f);

    // ���÷��ذ�ťλ��
    hatright->setPosition(Vec2(screenSize.width / 2 + 40, screenSize.height / 2 - 25));

    // Ϊ���ذ�ť����¼�������
    hatright->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
        {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                // ���ص����Ч
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                ++hat_num;
            }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(hatright);

    auto hatleft = HoverButton::create("../Resources/hatleftarrow.png",
        "../Resources/hatleftarrow.png",
        "../Resources/hatleftarrow.png");

    hatleft->setScale(0.25f);

    // ���÷��ذ�ťλ��
    hatleft->setPosition(Vec2(screenSize.width / 2 - 45, screenSize.height / 2 - 25));

    // Ϊ���ذ�ť����¼�������
    hatleft->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
        {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                // ���ص����Ч
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                --hat_num;
            }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(hatleft);

    auto okButton = HoverButton::create("../Resources/okDefaultButton.png",
        "../Resources/okPressedButton.png",
        "../Resources/okPressedButton.png");

    okButton->setScale(0.5625f);

    // ���÷��ذ�ťλ��
    okButton->setPosition(Vec2(screenSize.width / 2 + 168.75, screenSize.height / 2 - 175));

    // Ϊ���ذ�ť����¼�������
    okButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
        {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                // ���ص����Ч
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                auto farmer = Player::getInstance();
                //farmer->setTiledMap(map);
                /*farmer->setAnchorPoint(Vec2(0, 0));
                farmer->add_part("/motion/walk_down/body/body_walk_down_2.png", "body");
                farmer->add_part("/motion/walk_down/arm/arm_walk_down_2.png", "arm");
                farmer->add_tool("/motion/heavy_hit_right/axe/axe_heavy_hit_right_5.png", "axe");
                farmer->add_weapon("/motion/light_hit_right/sickle/sickle_light_hit_right_5.png", "sickle");*/
                farmer->add_wearing("/wearing/hat", "hat", hat_num % 3 + 1);
                farmer->add_wearing("/wearing/shirt", "shirt", shirt_num % 2 + 1);
                farmer->add_shadow("/shadow/shadow.png");
                Director::getInstance()->pushScene(FarmScene::createScene());
            }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(okButton);

    auto randButton = HoverButton::create("../Resources/randButton.png",
        "../Resources/randButton.png",
        "../Resources/randButton.png");

    randButton->setScale(0.35f);

    // ���÷��ذ�ťλ��
    randButton->setPosition(Vec2(screenSize.width / 2 - 67.5, screenSize.height / 2 + 181.25));

    // Ϊ���ذ�ť����¼�������
    randButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
        {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                // ���ص����Ч
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                hat_num = rand() % 3 + 300;
                shirt_num = rand() % 2 + 300;
            }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(randButton);

    return true;
}