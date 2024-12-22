#include <iostream>
#include <map>
#include "SimpleAudioEngine.h"
#include "FarmScene.h"
#include "TownScene.h"
#include "WoodsScene.h"
#include "CaveScene.h"
#include "MountainScene.h"
#include "FarmHouseScene.h"
#include "BackpackManager.h"
#include "Player.h"
#include "../Utils/MapUtil.h"
#include "../Utils/SceneUtil.h"
#include "../Systems/Farm_system.h"
#include "../Systems/Livestock_farm_system.h"
#include "../Systems/Time_system.h"
#include "MotionManager.h"
#include "Constant.h"
#include "DialogFrame.h"
#include "InteractableObject.h"

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

// 运动管理器
static MotionManager motionManager;
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
        CCLOG("Farm scene init!");
        Farm_system::getInstance()->drawFarm();
    }

    // 初始化畜栏
    if (1) {
        Liverstock_farm_system::getInstance()->drawFarm();
    }

    // 初始化人物
    auto farmer = Player::create();
    
    farmer->setTiledMap(map);
    farmer->setAnchorPoint(Vec2(0.5, 0));
    farmer->add_part("/motion/walk_down/body/body_walk_down_2.png", "body");
    farmer->add_part("/motion/walk_down/arm/arm_walk_down_2.png", "arm");
    farmer->add_tool("/motion/heavy_hit_right/hoe/hoe_heavy_hit_right_5.png", "hoe");
    farmer->add_weapon("/motion/light_hit_right/sword/sword_light_hit_right_5.png", "sword");
    farmer->add_wearing("/wearing/hat", "hat", 3);
    farmer->add_wearing("/wearing/shirt", "shirt", 2);
    farmer->add_shadow("/shadow/shadow.png");

    farmer->setPosition(playerPosition);

    farmer->regist(getMotionManager(), this, 20);

    farmer->go(playerInfo.faceTo);
    farmer->stand();

    this->setPlayer(farmer);

    getMotionManager()->add_movableObject(this);

    // NPC部分
    auto abigail = new NPC();
    abigail->add_part("characters/model/Abigail/walk_down/00.png", "body");
    abigail->add_shadow("/shadow/shadow.png");
    abigail->setTiledMap(map);
    std::vector<std::string> dialogList = { {"Good morning, No_99_Tongji!"}, {"Have you passed CET6?"}, {"Ahh..."} };
    abigail->add_dialogs(dialogList);

    abigail->setLocalZOrder(1);

    abigail->setPosition(Vec2(615, 835));

    auto Abigail_parts = abigail->get_parts();
    /*for (auto part : Abigail_parts)
        this->addChild(part);*/
    abigail->regist(getMotionManager(), this);

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
            //crop->setColor(Color3B::RED);
            
            Bag::getInstance()->itemInHand = FOOD;
            
            int x = PLAYER_POSITION.x;
            int y = PLAYER_POSITION.y;
            int idx, idy;
            Farm_system::getInstance()->get_closest_land(x, y, idx, idy);
            CCLOG("farm %d %d", idx, idy);
            Liverstock_farm_system::getInstance()->get_closest_corral(x, y, idx);
            CCLOG("animal %d", idx);

            Farm_system::getInstance()->plant_seed(WHEAT_SEED, x, y);

            for (int i = 0; i < 5; ++i) {
                int cnt[5] = { 0 };
                for (int j = 0; j < 5; ++j) {
                    auto info = Farm_system::getInstance()->farm_land[i][j].get_info();
                    cnt[j] = info.type != 0;
                }
                CCLOG("%d %d %d %d %d", cnt[0], cnt[1], cnt[2], cnt[3], cnt[4]);
            }

            Farm_system::getInstance()->drawFarm();

            Liverstock_farm_system::getInstance()->plant_seed(PIG_SEED, x, y);

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

