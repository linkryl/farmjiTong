#include <iostream>
#include <map>
#include "SimpleAudioEngine.h"
#include "FarmScene.h"
#include "TownScene.h"
#include "FarmHouseScene.h"
#include "WoodsScene.h"
#include "CaveScene.h"
#include "MountainScene.h"
#include "Player.h"
#include "../Utils/MapUtil.h"
#include "../Utils/SceneUtil.h"
#include "../Systems/Farm_system.h"
#include "../Systems/Livestock_farm_system.h"
#include "../Systems/Time_system.h"
#include "MotionManager.h"
#include "Constant.h"

USING_NS_CC;

enum Character { player, Abigail };

// ��Ʒӳ���������±��룺 
// 
// 1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
// 1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ��� 
// 2110Ϊ��2100Ϊ���У�2120Ϊ���� 

extern Farm_system farm_system;
extern Liverstock_farm_system live_farm_system;
extern Time_system time_system;
extern std::map<int, std::string> crop_names;
extern std::map<int, int> crop_image_number;
extern PlayerInfo playerInfo;

// �˶�������
static MotionManager motionManager;
// ��ɫ��Ӧ��ID
static std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };

Scene* FarmHouseScene::createScene()
{
    return FarmHouseScene::create();
}

void FarmHouseScene::update(float delta)
{
    motionManager.update();
}

bool FarmHouseScene::init()
{
    srand(time(0));
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto playerPosition = Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8);
    auto playerPosition = Vec2(400, 400);

    // ��ʼ����ͼ
    auto map = TMXTiledMap::create("FarmHouse2.tmx");
    auto layer = map->getLayer("Front");
    layer->setZOrder(80);
    //auto map_front = TMXTiledMap::create("Farm_Front.tmx");
    // ���õ�ͼ��λ��
    map->setPosition(Vec2(0, 0));
    //map_front->setPosition(Vec2(0, 0));
    map->setAnchorPoint(Vec2(0, 0));
    //map_front->setAnchorPoint(Vec2(0, 0));
    // ����ͼ��ӵ�������
    this->addChild(map);
    //this->addChild(map_front, 80);
    // �����а󶨵�ͼ
    this->setTiledMap(map);

    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(getMiddlePosition(playerPosition));
    this->setScale(GAME_SCALE);

    // ��ʼ������
    auto farmer = Player::create();
    
    farmer->setTiledMap(map);
    farmer->setAnchorPoint(Vec2(0, 0));
    farmer->add_part("/motion/walk_down/body/body_walk_down_2.png", "body");
    farmer->add_part("/motion/walk_down/arm/arm_walk_down_2.png", "arm");
    farmer->add_tool("/motion/heavy_hit_right/hoe/hoe_heavy_hit_right_5.png", "hoe");
    farmer->add_weapon("/motion/light_hit_right/sword/sword_light_hit_right_5.png", "sword");
    farmer->add_wearing("/wearing/hat", "hat", 3);
    farmer->add_wearing("/wearing/shirt", "shirt", 2);
    farmer->add_shadow("/shadow/shadow.png");

    farmer->setPosition(playerPosition);

    farmer->regist(&motionManager, this, 2);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    this->setPlayer(farmer);

    motionManager.add_movableObject(this);


    // �����¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        motionManager.keyMap[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        motionManager.keyMap[keyCode] = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_W ||
            keyCode == EventKeyboard::KeyCode::KEY_A ||
            keyCode == EventKeyboard::KeyCode::KEY_S ||
            keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            Player* player = farmer;
            player->stand();
            this->stopAllActions();
            this->returnMiddlePosition();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void FarmHouseScene::changeScene(std::string sceneName) {
    if (sceneName == "Farm") {
        playerInfo = { HOME_X, HOME_Y, DOWN };
        SceneUtil::changeScene(FarmScene::create());
    }
    else if (sceneName == "Town") {
        playerInfo = { FARM_TO_TOWN_INIT_X, FARM_TO_TOWN_INIT_Y, RIGHT };
        SceneUtil::changeScene(TownScene::create());
    }
    else if (sceneName == "Mountain") {
        playerInfo = { FARM_TO_MOUNTAIN_INIT_X, FARM_TO_MOUNTAIN_INIT_Y, RIGHT };
        SceneUtil::changeScene(MountainScene::create());
    }
    else if (sceneName == "Cave") {
        playerInfo = { FARM_TO_CAVE_INIT_X, FARM_TO_CAVE_INIT_Y, UP };
        SceneUtil::changeScene(CaveScene::create());
    }
    else if (sceneName == "Woods") {
        playerInfo = { FARM_TO_WOODS_INIT_X, FARM_TO_WOODS_INIT_Y, LEFT };
        SceneUtil::changeScene(WoodsScene::create());
    }
    else {
        CCLOG("Wrong scene name! Please check it.");
        throw "����������";
    }
}


void FarmHouseScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

