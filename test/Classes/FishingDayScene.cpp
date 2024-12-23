//#include "FishingDayScene.h"
//#include "Scenes/TownScene.h"
//#include "Player.h"
//#include "Utils/MapUtil.h"
//#include "Utils/SceneUtil.h"
//#include "Time_system.h"
//#include "MotionManager.h"
//#include "Constant.h"
//#include "InteractableObject.h"
//
//USING_NS_CC;
//
//enum Character { player, Abigail };
//
//// 物品映射遵照如下编码： 
//// 
//// 1110为蔬菜作物，1100为蔬菜种子，1120为收获的蔬菜 
//// 1111为谷物作物，1101为谷物种子，1121为收获的谷物 
//// 2110为猪，2100为猪仔，2120为猪肉 
//
//extern Time_system time_system;
//extern PlayerInfo playerInfo;
//
//
//// 角色对应的ID
//static std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };
//
//Scene* FishingDayScene::createScene()
//{
//    return FishingDayScene::create();
//}
//
//void FishingDayScene::update(float delta)
//{
//    getMotionManager()->update();
//}
//
//bool FishingDayScene::init()
//{
//    srand(time(0));
//    if (!Scene::init())
//    {
//        return false;
//    }
//    this->scheduleUpdate();
//
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    auto playerPosition = Vec2(playerInfo.tileX * 16 + 8, playerInfo.tileY * 16 - 8);
//
//    // 初始化地图
//    auto map = TMXTiledMap::create("FarmHouse.tmx");
//    auto layer = map->getLayer("Front");
//    layer->setZOrder(80);
//    //auto map_front = TMXTiledMap::create("Farm_Front.tmx");
//    // 设置地图的位置
//    map->setPosition(Vec2(0, 0));
//    //map_front->setPosition(Vec2(0, 0));
//    map->setAnchorPoint(Vec2(0, 0));
//    //map_front->setAnchorPoint(Vec2(0, 0));
//    // 将地图添加到场景中
//    this->addChild(map);
//    //this->addChild(map_front, 80);
//    // 场景中绑定地图
//    this->setTiledMap(map);
//
//    this->setAnchorPoint(Vec2(0, 0));
//    this->setPosition(getMiddlePosition(playerPosition));
//    this->setScale(GAME_SCALE);
//
//    // 初始化人物
//    auto farmer = Player::getInstance();
//
//    farmer->setTiledMap(map);
//
//    farmer->setPosition(playerPosition);
//
//    farmer->regist(getMotionManager(), this, 2);
//
//    farmer->go(playerInfo.faceTo);
//    farmer->stand();
//
//    this->setPlayer(farmer);
//
//    getMotionManager()->add_movableObject(this);
//
//    // 建立各传送点
//    auto farmTransportPoint = new TeleportPoint(TPMap::FARM, this);
//    farmTransportPoint->setPosition(tileCoordToPixel(FARM_TO_HOUSE_INIT_X, FARM_TO_HOUSE_INIT_Y));
//    this->addChild(farmTransportPoint);
//    getMotionManager()->add_movableObject(farmTransportPoint);
//
//
//    // 键盘事件监听器
//    auto listener = EventListenerKeyboard::create();
//    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
//        getMotionManager()->keyMap[keyCode] = true;
//    };
//    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
//        getMotionManager()->keyMap[keyCode] = false;
//        if (keyCode == EventKeyboard::KeyCode::KEY_W ||
//            keyCode == EventKeyboard::KeyCode::KEY_A ||
//            keyCode == EventKeyboard::KeyCode::KEY_S ||
//            keyCode == EventKeyboard::KeyCode::KEY_D)
//        {
//            Player* player = farmer;
//            player->stand();
//            this->stopAllActions();
//            this->returnMiddlePosition();
//        }
//    };
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//
//
//    return true;
//}
//
//void FishingDayScene::changeScene(TPMap toMap) {
//    if (toMap == TPMap::TOWN) {
//        SceneUtil::gotoTown();
//    }
//    else {
//        CCLOG("Wrong scene name! Please check it.");
//        throw "场景名错误";
//    }
//}
//
//
//void FishingDayScene::menuCloseCallback(Ref* pSender)
//{
//    Director::getInstance()->end();
//}
