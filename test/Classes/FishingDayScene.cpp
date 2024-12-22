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
//// ��Ʒӳ���������±��룺 
//// 
//// 1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
//// 1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ��� 
//// 2110Ϊ��2100Ϊ���У�2120Ϊ���� 
//
//extern Time_system time_system;
//extern PlayerInfo playerInfo;
//
//
//// ��ɫ��Ӧ��ID
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
//    // ��ʼ����ͼ
//    auto map = TMXTiledMap::create("FarmHouse.tmx");
//    auto layer = map->getLayer("Front");
//    layer->setZOrder(80);
//    //auto map_front = TMXTiledMap::create("Farm_Front.tmx");
//    // ���õ�ͼ��λ��
//    map->setPosition(Vec2(0, 0));
//    //map_front->setPosition(Vec2(0, 0));
//    map->setAnchorPoint(Vec2(0, 0));
//    //map_front->setAnchorPoint(Vec2(0, 0));
//    // ����ͼ��ӵ�������
//    this->addChild(map);
//    //this->addChild(map_front, 80);
//    // �����а󶨵�ͼ
//    this->setTiledMap(map);
//
//    this->setAnchorPoint(Vec2(0, 0));
//    this->setPosition(getMiddlePosition(playerPosition));
//    this->setScale(GAME_SCALE);
//
//    // ��ʼ������
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
//    // ���������͵�
//    auto farmTransportPoint = new TeleportPoint(TPMap::FARM, this);
//    farmTransportPoint->setPosition(tileCoordToPixel(FARM_TO_HOUSE_INIT_X, FARM_TO_HOUSE_INIT_Y));
//    this->addChild(farmTransportPoint);
//    getMotionManager()->add_movableObject(farmTransportPoint);
//
//
//    // �����¼�������
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
//        throw "����������";
//    }
//}
//
//
//void FishingDayScene::menuCloseCallback(Ref* pSender)
//{
//    Director::getInstance()->end();
//}
