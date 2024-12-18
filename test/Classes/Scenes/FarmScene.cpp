#include <iostream>
#include <map>
#include "SimpleAudioEngine.h"
#include "FarmScene.h"
#include "TownScene.h"
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

Scene* FarmScene::createScene()
{
    return FarmScene::create();
}

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
    map->setAnchorPoint(Vec2(0, 0));
    map_front->setAnchorPoint(Vec2(0, 0));
    // ����ͼ��ӵ�������
    this->addChild(map);
    this->addChild(map_front, 80);
    // �����а󶨵�ͼ
    this->setTiledMap(map);

    this->setAnchorPoint(Vec2(0, 0));
    //this->setPosition(Vec2(-GAME_SCALE * (playerInfo.tileX * 8 + 8), -GAME_SCALE * (playerInfo.tileY * 8 + 8)));
    this->setPosition(getMiddlePosition(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8));
    this->setScale(GAME_SCALE);

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
            //crop->setScale(GAME_SCALE);
            addChild(crop);
        }
    }

    // ��ʼ������
    if (0) {
        for (int i = 0; i < 5; ++i) {
            auto info = live_farm_system.get_info(16 * (LIVE_FARM_OFFSET_X + i), 16 * LIVE_FARM_OFFSET_Y);
            if (info.type == 0) {
                //continue;
            }
            // ���Ӧ�ð�����������״̬��̬��ȡ������ʾ
            //auto crop = Sprite::create("/crops/" + crop_names[info.type] + "_6");

            auto crop = Sprite::create("/Animals/" + crop_names[2110] + "_1.png");
            crop->setPosition(GAME_SCALE * (16 * (LIVE_FARM_OFFSET_X + i * 3) - 8), GAME_SCALE * (16 * LIVE_FARM_OFFSET_Y + 8));
            crop->setAnchorPoint(Vec2(0, 0));
            //crop->setScale(GAME_SCALE);
            addChild(crop);
        }
    }

    // ���Ե�
    Size mapSize = map->getMapSize();
    Size tileSize = map->getTileSize();
    double sceneFixedWidth = visibleSize.width / 2.0 / GAME_SCALE;
    double sceneFixedHeight = visibleSize.height / 2.0 / GAME_SCALE;
    double mapWidth = 1.0 * mapSize.width * tileSize.width;
    double mapHeight = 1.0 * mapSize.height * tileSize.height;
    auto crop = Sprite::create("/Crops/" + crop_names[1110 + rand() % 2] + "_" + std::to_string(rand() % 6 + 1) + ".png");
    crop->setPosition(sceneFixedWidth, sceneFixedHeight);
    crop->setAnchorPoint(Vec2(0, 0));
    addChild(crop);
    auto crop2 = Sprite::create("/Crops/" + crop_names[1110] + "_6.png");
    crop2->setPosition(mapWidth - sceneFixedWidth, sceneFixedHeight);
    crop2->setAnchorPoint(Vec2(0, 0));
    addChild(crop2);
    auto crop3 = Sprite::create("/Crops/" + crop_names[1110] + "_6.png");
    crop3->setPosition(sceneFixedWidth, mapHeight - sceneFixedHeight);
    crop3->setAnchorPoint(Vec2(0, 0));
    addChild(crop3);
    auto crop4 = Sprite::create("/Crops/" + crop_names[1110] + "_6.png");
    crop4->setPosition(mapWidth - sceneFixedWidth, mapHeight - sceneFixedHeight);
    crop4->setAnchorPoint(Vec2(0, 0));
    addChild(crop4);

    // ��ʼ������
    auto farmer = Player::create();
    //motionManager.add_movableObject(farmer);
    
    farmer->setTiledMap(map);
    farmer->setAnchorPoint(Vec2(0, 0));
    farmer->add_part("/motion/walk_up/body/body_walk_up_0.png", "body");
    farmer->add_part("/motion/walk_up/arm/arm_walk_up_0.png", "arm");

    farmer->setPosition(Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8));
    /*
    for (auto part : farmer->get_parts()) {
        this->addChild(part, 20);
    }

    this->addChild(farmer, 20, characterID[Character::player]);
    this->setPlayer(farmer);
    */
    farmer->regist(&motionManager, this, 2);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    //motionManager.add_movableObject(this);
    this->go(opposite(playerInfo.faceTo));


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
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void changeScene(std::string sceneName) {
    if (sceneName == "Farm") {
        playerInfo = { HOME_X, HOME_Y, DOWN };
        changeScene(FarmScene::create());
    }
    else if (sceneName == "Town") {
        playerInfo = { FARM_TO_TOWN_INIT_X, FARM_TO_TOWN_INIT_Y, RIGHT };
        changeScene(TownScene::create());
    }
    else if (sceneName == "Mountain") {
        playerInfo = { FARM_TO_MOUNTAIN_INIT_X, FARM_TO_MOUNTAIN_INIT_Y, RIGHT };
        changeScene(MountainScene::create());
    }
    else if (sceneName == "Cave") {
        playerInfo = { FARM_TO_CAVE_INIT_X, FARM_TO_CAVE_INIT_Y, UP };
        changeScene(CaveScene::create());
    }
    else if (sceneName == "Woods") {
        playerInfo = { FARM_TO_WOODS_INIT_X, FARM_TO_WOODS_INIT_Y, LEFT };
        changeScene(WoodsScene::create());
    }
    else {
        CCLOG("Wrong scene name! Please check it.");
        throw "����������";
    }
}


void FarmScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

