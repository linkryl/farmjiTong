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

// 全局时间系统
extern Time_system time_system;
// 需维护的玩家信息
extern PlayerInfo playerInfo;
// 运动管理器
static MotionManager motionManager;
enum Character { player, Abigail };
// 角色对应的ID
static std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };

Scene* TownScene::createScene()
{
    return TownScene::create();
}

void TownScene::update(float delta)
{
    motionManager.update();
}

bool TownScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // 初始化地图
    auto map = TMXTiledMap::create("Town.tmx");
    auto map_front = TMXTiledMap::create("Town_Front.tmx");
    // 设置地图的位置
    map->setPosition(Vec2(0, 0));
    map_front->setPosition(Vec2(0, 0));
    map->setAnchorPoint(Vec2(0, 0));
    map_front->setAnchorPoint(Vec2(0, 0));
    // 将地图添加到场景中
    this->addChild(map);
    this->addChild(map_front, 80);
    // 场景中绑定地图
    this->setTiledMap(map);
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(-GAME_SCALE * (playerInfo.tileX * 8 + 8), -GAME_SCALE * (playerInfo.tileY * 8 + 8)));
    this->setScale(GAME_SCALE);


    // 初始化人物
    auto farmer = Player::create();
    motionManager.add_movableObject(farmer);
    farmer->setTiledMap(map);
    farmer->add_part("/motion/walk_up/body/body_walk_up_0.png", "body");
    farmer->add_part("/motion/walk_up/arm/arm_walk_up_0.png", "arm");

    farmer->setPosition(Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8));

    for (auto part : farmer->get_parts()) {
        this->addChild(part, 20);
    }

    this->addChild(farmer, 20, characterID[Character::player]);
    this->setPlayer(farmer);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    motionManager.add_movableObject(this);


    //键盘事件监听器
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
            this->stopAllActions();
            log("stand");
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void TownScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}