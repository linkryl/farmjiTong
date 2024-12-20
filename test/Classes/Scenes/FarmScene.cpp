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

extern Farm_system farm_system;
extern Liverstock_farm_system live_farm_system;
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
    for (int i = 0; i < 5; ++i) {
        for (int j = 4; j >= 0; --j) {
            auto info = farm_system.get_info(16 * (FARM_OFFSET_X + i), 16 * (FARM_OFFSET_Y + j));
            if (info.type == 0) {
                //continue;
            }
            // 编号应该按照作物生长状态动态调取，先演示
            //auto crop = Sprite::create("/crops/" + crop_names[info.type] + "_6");

            auto crop = Sprite::create("/Crops/" + crop_names[1110 + rand() % 2] + "_" + std::to_string(rand() % 6 + 1) + ".png");
            crop->setPosition(16 * (FARM_OFFSET_X + i), 16 * (FARM_OFFSET_Y + j));
            crop->setAnchorPoint(Vec2(0, 0));
            //crop->setScale(GAME_SCALE);
            addChild(crop);
        }
    }

    // 初始化畜栏
    if (0) {
        for (int i = 0; i < 5; ++i) {
            auto info = live_farm_system.get_info(16 * (LIVE_FARM_OFFSET_X + i), 16 * LIVE_FARM_OFFSET_Y);
            if (info.type == 0) {
                //continue;
            }
            // 编号应该按照作物生长状态动态调取，先演示
            //auto crop = Sprite::create("/crops/" + crop_names[info.type] + "_6");

            auto crop = Sprite::create("/Animals/" + crop_names[2110] + "_1.png");
            crop->setPosition((16 * (LIVE_FARM_OFFSET_X + i * 3) - 8), (16 * LIVE_FARM_OFFSET_Y + 8));
            crop->setAnchorPoint(Vec2(0, 0));
            addChild(crop);
        }
    }

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

            //SceneUtil::gotoFarm();
            

            // 获取 Director 的 _notificationNode
            auto notificationNode = Director::getInstance()->getNotificationNode();

            // 如果 _notificationNode 为空，则创建一个新的 Node
            if (!notificationNode) {
                notificationNode = Node::create();
                Director::getInstance()->setNotificationNode(notificationNode);
            }

            // 创建一个独立的 Layer
            auto topLayer = Layer::create();


            auto dialogFrame = DialogFrame::create("text");

            // 创建一个独立的 Layer 用于放置对话框
            auto uiLayer = cocos2d::Layer::create();
            topLayer->addChild(dialogFrame);

            // 将 Layer 添加到 _notificationNode 中
            notificationNode->addChild(topLayer);
            
            /*
            // 创建一个独立的 Camera 用于 uiLayer
            auto uiCamera = cocos2d::Camera::create();
            uiLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
            uiCamera->setCameraFlag(cocos2d::CameraFlag::USER1);
            uiLayer->setScale(1 / GAME_SCALE);
            //uiCamera->setScale(1 / GAME_SCALE);
            //dialogFrame->setPosition(Vec2(-625, -800));
            // 
            // 将 uiLayer 添加到场景中
            this->addChild(uiLayer);

            // 将 Camera 添加到场景中
            this->addChild(uiCamera);
            //Director::getInstance()->pushScene(dialogScene);
            */
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

