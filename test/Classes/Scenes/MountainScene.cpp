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
#include "InteractableObject.h"

USING_NS_CC;

enum Character { player, Abigail };

// ��Ʒӳ���������±��룺 
// 
// 1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
// 1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ��� 
// 2110Ϊ��2100Ϊ���У�2120Ϊ���� 

extern Time_system time_system;
extern PlayerInfo playerInfo;

// �˶�������
static MotionManager motionManager;
// ��ɫ��Ӧ��ID
static std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };

Scene* MountainScene::createScene()
{
    return MountainScene::create();
}

void MountainScene::update(float delta)
{
    getMotionManager()->update();
}

bool MountainScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto playerPosition = Vec2(playerInfo.tileX * 16 + 8 + 16, playerInfo.tileY * 16 - 8);
    auto playerPosition = Vec2(10, 440);


    // ��ʼ����ͼ
    auto map = TMXTiledMap::create("Mountain.tmx");
    auto map_front = TMXTiledMap::create("Mountain_Front.tmx");
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

    farmer->regist(getMotionManager(), this, 2);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    this->setPlayer(farmer);

    getMotionManager()->add_movableObject(this);

    // ���ư�ť�ı߽��
    auto drawNode = DrawNode::create();
    drawNode->drawRect(farmer->getBoundingBox().origin, farmer->getBoundingBox().origin + farmer->getBoundingBox().size, Color4F::RED);
    Director::getInstance()->getRunningScene()->addChild(drawNode, 100);
    drawNode->setPosition(playerPosition);


    // ���������͵�
    auto farmTransportPoint = new TeleportPoint(TPMap::FARM, this);
    farmTransportPoint->setPosition(tileCoordToPixel(FARM_TO_MOUNTAIN_INIT_X, FARM_TO_MOUNTAIN_INIT_Y));
    this->addChild(farmTransportPoint);
    getMotionManager()->add_movableObject(farmTransportPoint);

    // �����¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        getMotionManager()->keyMap[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        getMotionManager()->keyMap[keyCode] = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_W ||
            keyCode == EventKeyboard::KeyCode::KEY_A ||
            keyCode == EventKeyboard::KeyCode::KEY_S ||
            keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            Player* player = farmer;
            player->stand();
            this->stopAllActions();
            this->returnMiddlePosition();
            CCLOG("%2.f %2.f", PLAYER_POSITION.x, PLAYER_POSITION.y);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



    return true;
}

void MountainScene::changeScene(TPMap toMap) {
    if (toMap == TPMap::FARM) {
        SceneUtil::gotoFarm(MOUNTAIN_TO_FARM_INIT_X, MOUNTAIN_TO_FARM_INIT_Y, UP);
    }
    else {
        CCLOG("Wrong scene name! Please check it.");
        throw "����������";
    }
}

void MountainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}