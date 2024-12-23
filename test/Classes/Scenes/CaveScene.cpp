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
#include "Monster.h"
#include "Drop.h"

USING_NS_CC;

// 全局时间系统
extern Time_system time_system;
// 需维护的玩家信息
extern PlayerInfo playerInfo;
enum Character { player, Abigail };
// 角色对应的ID
static std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };

Scene* CaveScene::createScene()
{
    return CaveScene::create();
}

void CaveScene::update(float delta)
{
    getMotionManager()->update();
}

bool CaveScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("Cave.tmx");
    auto map_front = TMXTiledMap::create("Cave_Front.tmx");

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
    farmer->add_tool("/motion/heavy_hit_right/pickaxe/pickaxe_heavy_hit_right_5.png", "pickaxe");
    farmer->add_weapon("/motion/light_hit_right/sword/sword_light_hit_right_5.png", "sword");

    farmer->setPosition(Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8));

    farmer->regist(getMotionManager(), this, 2);

    farmer->go(playerInfo.faceTo);
    farmer->stand();
    // 蝙蝠
    Bat* bat1 = Bat::create("monster/bat/bat_fly_0.png", 5, 50);
    bat1->setPosition(Vec2({ 500, 500 }));
    bat1->regist(this->getMotionManager(), this, 20);

    Bat* bat2 = Bat::create("monster/bat/bat_fly_0.png", 5, 50);
    bat2->setPosition(Vec2({ 700, 590 }));
    bat2->regist(this->getMotionManager(), this, 20);

    // 石头
    int num = 20;
    
    for (int i = 1; i <= 20; i++)
    {
        const auto mapSize = getTiledMap()->getMapSize();
        auto buildingsLayer = getTiledMap()->getLayer("Buildings");
        int x = -1;
        int y = -1;
        while (1) {
            x = rand() % (int)mapSize.width;
            y = rand() % (int)mapSize.height;
            int id = buildingsLayer->getTileGIDAt(Vec2(x, y));
            if (id == 0) {
                break;
            }
        }
        Stone* new_stone = Stone::create("mineral/Mystic_Stone.png");
        new_stone->setScale(0.3);
        new_stone->setPosition(tileCoordToPixel(x, y));
        new_stone->regist(getMotionManager(), this);
    }

    this->setPlayer(farmer);

    getMotionManager()->add_movableObject(this);

    // 建立各传送点
    auto farmTransportPoint = new TeleportPoint(TPMap::FARM, this);
    farmTransportPoint->setPosition(tileCoordToPixel(FARM_TO_CAVE_INIT_X, FARM_TO_CAVE_INIT_Y));
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

void CaveScene::changeScene(TPMap toMap) {
    if (toMap == TPMap::FARM) {
        SceneUtil::gotoFarm(CAVE_TO_FARM_INIT_X, CAVE_TO_FARM_INIT_Y, DOWN);
    }
    else {
        CCLOG("Wrong scene name! Please check it.");
        throw "场景名错误";
    }
}

void CaveScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}