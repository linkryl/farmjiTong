#include <iostream>
#include <map>
#include "SimpleAudioEngine.h"
#include "FarmScene.h"
#include "TownScene.h"
#include "WoodsScene.h"
#include "CaveScene.h"
#include "MountainScene.h"
#include "FarmHouseScene.h"
#include "Player.h"
#include "../Utils/MapUtil.h"
#include "../Utils/SceneUtil.h"
#include "../Systems/Farm_system.h"
#include "../Systems/Livestock_farm_system.h"
#include "../Time_system.h"
#include "MotionManager.h"
#include "Constant.h"
#include "DialogFrame.h"
#include "InteractableObject.h"
#include "Drop.h"

USING_NS_CC;

enum Character { player, Abigail };

// 物品映射遵照如下编码： 
// 
// 1110为蔬菜作物，1100为蔬菜种子，1120为收获的蔬菜 
// 1111为谷物作物，1101为谷物种子，1121为收获的谷物 
// 2110为猪，2100为猪仔，2120为猪肉 

extern Time_system time_system;
extern std::map<int, std::string> crop_names;
extern std::map<int, int> crop_image_number;
extern PlayerInfo playerInfo;

// 角色对应的ID
static std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };

Scene* FarmScene::createScene()
{
    return FarmScene::create();
}

void FarmScene::update(float delta)
{
    getMotionManager()->update();
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

    auto playerPosition = Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8);
    //auto playerPosition = Vec2(100, 400);

    // 初始化地图
    auto map = TMXTiledMap::create("Farm.tmx");
    auto map_front = TMXTiledMap::create("Farm_Front.tmx");
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
    this->setPosition(getMiddlePosition(playerPosition));
    this->setScale(GAME_SCALE);

    // 初始化农田
    if (1) {
        Farm_system::getInstance()->drawFarm();
    }

    // 初始化畜栏
    if (1) {
        Liverstock_farm_system::getInstance()->drawFarm();
    }

    // 初始化人物
    auto farmer = Player::getInstance();
    
    farmer->setTiledMap(map);
    farmer->setAnchorPoint(Vec2(0, 0));
    farmer->add_part("/motion/walk_down/body/body_walk_down_2.png", "body");
    farmer->add_part("/motion/walk_down/arm/arm_walk_down_2.png", "arm");
    farmer->add_tool("/motion/heavy_hit_right/axe/axe_heavy_hit_right_5.png", "axe");
    farmer->add_weapon("/motion/light_hit_right/sickle/sickle_light_hit_right_5.png", "sickle");
    /*farmer->add_wearing("/wearing/hat", "hat", 3);
    farmer->add_wearing("/wearing/shirt", "shirt", 2);*/
    farmer->add_shadow("/shadow/shadow.png");

    farmer->setPosition(playerPosition);

    farmer->regist(getMotionManager(), this, 100);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    this->setPlayer(farmer);

    getMotionManager()->add_movableObject(this);

    // 初始化树木
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
            if (id != 0) {
                continue;
            }
            if (x >= FARM_OFFSET_X && x <= FARM_OFFSET_X + 8 && y >= FARM_OFFSET_Y && y <= FARM_OFFSET_Y + 8) {
                continue;
            }
            if (x >= LIVE_FARM_OFFSET_X - 2 && x <= LIVE_FARM_OFFSET_X + 10 && y >= LIVE_FARM_OFFSET_Y - 6 && y <= LIVE_FARM_OFFSET_Y + 6) {
                continue;
            }
            if (x >= 45 && x <= 56 && y >= 65 - 27 && y <= 65 - 16) {
                continue;
            }
            if (x >= 32 && x <= 48 && y >= 0 && y <= 65 - 47) {
                continue;
            }
            if (x >= 68 && x <= 80 && y >= 65 - 35 && y <= 65 - 14) {
                continue;
            }
            if (x >= 10 && x <= 45 && y >= 65 - 11 && y <= 65) {
                continue;
            }
            if (x >= 0 && x <= 6 && y >= 65 - 65 && y <= 65 - 2) {
                continue;
            }
            break;
        }
        Tree* new_tree = Tree::create("tree/tree_"+std::to_string(i%3)+".png");
        new_tree->setScale(0.5);
        new_tree->setPosition(tileCoordToPixel(x, y));
        new_tree->regist(getMotionManager(), this);
    }


    // 建立各传送点
    auto townTransportPoint = new TeleportPoint(TPMap::TOWN, this);
    townTransportPoint->setPosition(tileCoordToPixel(TOWN_TO_FARM_INIT_X, TOWN_TO_FARM_INIT_Y));
    auto caveTransportPoint = new TeleportPoint(TPMap::CAVE, this);
    caveTransportPoint->setPosition(tileCoordToPixel(CAVE_TO_FARM_INIT_X, CAVE_TO_FARM_INIT_Y));
    auto woodsTransportPoint = new TeleportPoint(TPMap::WOODS, this);
    woodsTransportPoint->setPosition(tileCoordToPixel(WOODS_TO_FARM_INIT_X, WOODS_TO_FARM_INIT_Y));
    auto mountainTransportPoint = new TeleportPoint(TPMap::MOUNTAIN, this);
    mountainTransportPoint->setPosition(tileCoordToPixel(MOUNTAIN_TO_FARM_INIT_X, MOUNTAIN_TO_FARM_INIT_Y));
    auto houseTransportPoint = new TeleportPoint(TPMap::FARM_HOUSE, this);
    houseTransportPoint->setPosition(tileCoordToPixel(HOME_X, HOME_Y));
    this->addChild(townTransportPoint);
    this->addChild(caveTransportPoint);
    this->addChild(woodsTransportPoint);
    this->addChild(mountainTransportPoint);
    this->addChild(houseTransportPoint);
    getMotionManager()->add_movableObject(townTransportPoint);
    getMotionManager()->add_movableObject(caveTransportPoint);
    getMotionManager()->add_movableObject(woodsTransportPoint);
    getMotionManager()->add_movableObject(mountainTransportPoint);
    getMotionManager()->add_movableObject(houseTransportPoint);

    // 键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        getMotionManager()->keyMap[keyCode] = true;
        if (keyCode == EventKeyboard::KeyCode::KEY_O) {

            Farm_system::getInstance()->drawFarm();
            Liverstock_farm_system::getInstance()->drawFarm();
        }
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

    // 处理点击事件
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        // 获取点击的屏幕坐标
        Vec2 touchLocation = touch->getLocation();

        CCLOG("%2.f %2.f", touchLocation.x, touchLocation.y);

        // 没有点击按钮
        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

    return true;
}

void FarmScene::changeScene(TPMap toMap) {
    if (toMap == TPMap::FARM) {
        SceneUtil::gotoFarm();
    }
    else if (toMap == TPMap::TOWN) {
        SceneUtil::gotoTown();
    }
    else if (toMap == TPMap::MOUNTAIN) {
        SceneUtil::gotoMountain();
    }
    else if (toMap == TPMap::CAVE) {
        SceneUtil::gotoCave();
    }
    else if (toMap == TPMap::WOODS) {
        SceneUtil::gotoWoods();
    }
    else if (toMap == TPMap::FARM_HOUSE) {
        SceneUtil::gotoHouse();
    }
    else {
        CCLOG("Wrong scene name! Please check it.");
        throw "场景名错误";
    }
}


void FarmScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

