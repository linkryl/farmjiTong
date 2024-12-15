#include "Player.h"
#include "Util.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <map>
#include "DialogFrame.h"
#include "MotionManager.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 运动管理器
MotionManager motionManager;
enum Character { player, Abigail };
// 角色对应的ID
std::map<Character, int> characterID = { {player, 114514}, {Abigail, 114} };
void HelloWorld::update(float delta)
{
    motionManager.update();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto testMap = TMXTiledMap::create("Farm.tmx");
    testMap->setPosition(Vec2(0, 0));
    if (!testMap) {
        CCLOG("Failed to load Town.tmx");
        return false;
    }
    motionManager.tmxMap = testMap;
    addChild(testMap, -8);
    auto testLayer = testMap->getLayer("Front");
    testLayer->setLocalZOrder(5);

    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "Hello World"
    // create and initialize a label
    // 添加搜索路径
    FileUtils::getInstance()->addSearchPath("E:\\cocos2d-x-3.17.2\\cocos2d-x-3.17.2\\testCpp2\\proj.win32\\Debug.win32\\content");

    // NPC部分
    auto abigail = new NPC();
    motionManager.add_movableObject(abigail);
    abigail->add_part("chracters/model/Abigail/walk_down/00.png", "body");
    abigail->setTiledMap(testMap);
    std::vector<std::string> dialogList = { {"Good morning, No_99_Tongji!"}, {"Have you passed CET6?"}, {"Ahh..."}};
    abigail->add_dialogs(dialogList);

    abigail->setLocalZOrder(1);

    abigail->setScale(1.5);
    //farmer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - farmer->getContentSize().height));

    abigail->setPosition(Vec2(615, 835));

    auto Abigail_parts = abigail->get_parts();
    for (auto part : Abigail_parts)
        this->addChild(part);


    this->addChild(abigail, 1, characterID[Abigail]);

    // 人物部分
    auto farmer = Player::create();
    motionManager.add_movableObject(farmer);
    farmer->setTiledMap(testMap);
    
    farmer->add_part("/motion/walk_down/body/body_walk_down_2.png", "body");
    farmer->add_part("/motion/walk_down/arm/arm_walk_down_2.png", "arm");
    farmer->add_tool("/motion/heavy_hit_right/hoe/hoe_heavy_hit_right_5.png", "hoe");
    farmer->add_weapon("/motion/light_hit_right/sickle/sickle_light_hit_right_5.png", "sickle");
    farmer->add_wearing("/wearing/hat", "hat", 3);
    farmer->add_wearing("/wearing/shirt", "shirt", 2);

    farmer->setLocalZOrder(2);

    farmer->setScale(1.5);
    //farmer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - farmer->getContentSize().height));

    farmer->setPosition(Vec2(600, 500));

    auto farmer_parts = farmer->get_parts();
    auto farmer_tools = farmer->get_tools();
    auto farmer_weapons = farmer->get_weapons();
    auto farmer_wearings = farmer->get_wearings();
    for (auto wearing : farmer_wearings)
        this->addChild(wearing, 5);
    for (auto part : farmer_parts)
        this->addChild(part);
    for (auto tool : farmer_tools)
        this->addChild(tool, 6);
    for (auto weapon : farmer_weapons)
        this->addChild(weapon, 7);

    //farmer->go(DOWN);

    this->addChild(farmer, 2, characterID[player]);



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
            Player* player = (Player*)this->getChildByTag(114514);
            player->stand();
            log("stand");
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game s    cene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}