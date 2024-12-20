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

// 物品映射遵照如下编码： 
// 
// 1110为蔬菜作物，1100为蔬菜种子，1120为收获的蔬菜 
// 1111为谷物作物，1101为谷物种子，1121为收获的谷物 
// 2110为猪，2100为猪仔，2120为猪肉 

extern Time_system time_system;
extern PlayerInfo playerInfo;

// 运动管理器
static MotionManager motionManager;
// 角色对应的ID
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


    // 初始化地图
    auto map = TMXTiledMap::create("Mountain.tmx");
    auto map_front = TMXTiledMap::create("Mountain_Front.tmx");
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
    this->setPosition(getMiddlePosition(playerPosition));
    this->setScale(GAME_SCALE);

    // 初始化人物
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

    // 绘制按钮的边界框
    auto drawNode = DrawNode::create();
    drawNode->drawRect(farmer->getBoundingBox().origin, farmer->getBoundingBox().origin + farmer->getBoundingBox().size, Color4F::RED);
    Director::getInstance()->getRunningScene()->addChild(drawNode, 100);
    drawNode->setPosition(playerPosition);


    // 建立各传送点
    auto farmTransportPoint = new TeleportPoint(TPMap::FARM, this);
    farmTransportPoint->setPosition(tileCoordToPixel(FARM_TO_MOUNTAIN_INIT_X, FARM_TO_MOUNTAIN_INIT_Y));
    this->addChild(farmTransportPoint);
    getMotionManager()->add_movableObject(farmTransportPoint);

    // 键盘事件监听器
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
        throw "场景名错误";
    }
}

void MountainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}