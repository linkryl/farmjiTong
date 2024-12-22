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
#include "../Time_system.h"
#include "MotionManager.h"
#include "Constant.h"
#include "InteractableObject.h"


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

Scene* WoodsScene::createScene()
{
    return WoodsScene::create();
}

void WoodsScene::update(float delta)
{
    getMotionManager()->update();
}

bool WoodsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("Woods.tmx");
    auto map_front = TMXTiledMap::create("Woods_Front.tmx");

    // 设置地图的位置
    map->setPosition(Vec2(0, 0));
    map_front->setPosition(Vec2(0, 0));
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
    //this->setPosition(Vec2(-GAME_SCALE * (playerInfo.tileX * 8 + 8), -GAME_SCALE * (playerInfo.tileY * 8 + 8)));
    this->setPosition(getMiddlePosition(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8));
    this->setScale(GAME_SCALE);

    // 初始化人物
    auto farmer = Player::getInstance();

    farmer->setTiledMap(map);
    farmer->setAnchorPoint(Vec2(0, 0));

    farmer->setPosition(Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8));

    farmer->regist(getMotionManager(), this, 2);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    this->setPlayer(farmer);

    getMotionManager()->add_movableObject(this);
    //this->go(opposite(playerInfo.faceTo));


    // 建立各传送点
    auto farmTransportPoint = new TeleportPoint(TPMap::FARM, this);
    farmTransportPoint->setPosition(tileCoordToPixel(FARM_TO_WOODS_INIT_X, FARM_TO_WOODS_INIT_Y));
    this->addChild(farmTransportPoint);
    getMotionManager()->add_movableObject(farmTransportPoint);


    //键盘事件监听器
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
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



    return true;
}

void WoodsScene::changeScene(TPMap toMap) {
    if (toMap == TPMap::FARM) {
        SceneUtil::gotoFarm(WOODS_TO_FARM_INIT_X, WOODS_TO_FARM_INIT_Y, LEFT);
    }
    else {
        CCLOG("Wrong scene name! Please check it.");
        throw "场景名错误";
    }
}

void WoodsScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}