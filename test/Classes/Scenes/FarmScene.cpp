#include <iostream>
#include <map>
#include "SimpleAudioEngine.h"
#include "FarmScene.h"
#include "TownScene.h"
#include "Player.h"
#include "../Utils/MapUtil.h"
#include "../Utils/SceneUtil.h"
#include "../Systems/Farm_system.h"
#include "../Systems/Livestock_farm_system.h"
#include "../Systems/Time_system.h"
#include "MotionManager.h"
#include "Constant.h"

// ��Ʒӳ���������±��룺 
// 
// 1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
// 1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ��� 
// 2110Ϊ��2100Ϊ���У�2120Ϊ���� 

extern int all_var;
extern Farm_system farm_system;
extern Liverstock_farm_system live_farm_system;
extern Time_system time_system;
extern std::map<int, std::string> crop_names;
extern std::map<int, int> crop_image_number;


USING_NS_CC;

Scene* FarmScene::createScene()
{
    return FarmScene::create();
}

// �˶�������
MotionManager motionManager;
enum Character { player, Abigail };
// ��ɫ��Ӧ��ID
std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };
void FarmScene::update(float delta)
{
    motionManager.update();
}

bool FarmScene::init()
{
    srand(time(0));
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��ʼ����ͼ
    auto map = TMXTiledMap::create("Farm.tmx");
    auto map_front = TMXTiledMap::create("Farm_Front.tmx");
    // ���õ�ͼ��λ��
    map->setPosition(Vec2(0, 0));
    map_front->setPosition(Vec2(0, 0));
    // ����ͼ��ӵ�������
    this->addChild(map);
    this->addChild(map_front, 80);

    // ��ʼ��ũ��
    for (int i = 0; i < 5; ++i) {
        for (int j = 4; j >= 0; --j) {
            auto info = farm_system.get_info(16 * (FARM_OFFSET_X + i), 16 * (FARM_OFFSET_Y + j));
            if (info.type == 0) {
                //continue;
            }
            // ���Ӧ�ð�����������״̬��̬��ȡ������ʾ
            //auto crop = Sprite::create("/crops/" + crop_names[info.type] + "_6");

            auto crop = Sprite::create("/Crops/" + crop_names[1110 + rand() % 2] + "_" + std::to_string(rand() % 6 + 1) + ".png");
            crop->setPosition(16 * (FARM_OFFSET_X + i), 16 * (FARM_OFFSET_Y + j));
            crop->setAnchorPoint(Vec2(0, 0));
            addChild(crop);
        }
    }

    // ��ʼ������
    for (int i = 0; i < 5; ++i) {
        auto info = live_farm_system.get_info(16 * (LIVE_FARM_OFFSET_X + i), 16 * LIVE_FARM_OFFSET_Y);
        if (info.type == 0) {
            //continue;
        }
        // ���Ӧ�ð�����������״̬��̬��ȡ������ʾ
        //auto crop = Sprite::create("/crops/" + crop_names[info.type] + "_6");

        auto crop = Sprite::create("/Animals/" + crop_names[2110] + "_1.png");
        crop->setPosition(16 * (LIVE_FARM_OFFSET_X + i * 3) - 8, 16 * LIVE_FARM_OFFSET_Y + 8);
        crop->setAnchorPoint(Vec2(0, 0));
        addChild(crop);
    }


    // ��ʼ������
    auto farmer = Player::create();
    motionManager.add_movableObject(farmer);
    farmer->setTiledMap(map);
    farmer->add_part("/motion/walk_up/body/body_walk_up_0.png", "body");
    farmer->add_part("/motion/walk_up/arm/arm_walk_up_0.png", "arm");

    farmer->setScale(1);
    farmer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));

    for (auto part : farmer->get_parts()) {
        this->addChild(part, 20);
    }

    this->addChild(farmer, 20, characterID[player]);

    farmer->go(DOWN);


    //�����¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("press");
        motionManager.keyMap[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("release");
        motionManager.keyMap[keyCode] = false;
        std::cout << "release" << std::endl;
        if (keyCode == EventKeyboard::KeyCode::KEY_W ||
            keyCode == EventKeyboard::KeyCode::KEY_A ||
            keyCode == EventKeyboard::KeyCode::KEY_S ||
            keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            Player* player = (Player*)this->getChildByTag(characterID[Character::player]);
            player->stand();
            log("stand");
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



    return true;
}


void FarmScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}