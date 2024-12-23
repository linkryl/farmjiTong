#include "Player.h"
#include "Utils/MapUtil.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <map>
#include "DialogFrame.h"
#include "MotionManager.h"
#include "Time_system.h"
#include "SocialInfo.h"
#include "Monster.h"

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
extern Time_system time_system;
void HelloWorld::update(float delta)
{
    time_system.update_time();
    auto time = time_system.get_clock_time();
    // 创建对话内容标签
    this->removeChildByTag(69210);
    //////// 时间检测
    /////
    auto contentLabel = Label::createWithTTF(std::to_string(time), "fonts/arial.ttf", 24);
    contentLabel->setTag(69210);
    contentLabel->setColor(Color3B::BLACK);
    contentLabel->setPosition({ 300, 300 });
    this->addChild(contentLabel);

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
    auto testMap = TMXTiledMap::create("town.tmx");
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
    abigail->add_part("characters/model/Abigail/walk_down/00.png", "body");
    abigail->add_shadow("/shadow/shadow.png");
    abigail->setTiledMap(testMap);
    std::vector<std::string> dialogList = { {"Good morning, No_99_Tongji!"}, {"Have you passed CET6?"}, {"Ahh..."} };
    abigail->add_dialogs(dialogList);

    abigail->setLocalZOrder(1);

    abigail->setScale(1.5);
    //farmer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - farmer->getContentSize().height));

    abigail->setPosition(Vec2(615, 835));

    auto Abigail_parts = abigail->get_parts();
    /*for (auto part : Abigail_parts)
        this->addChild(part);*/
    abigail->regist(&motionManager, this);

    // 人物部分
    auto farmer = Player::create();
    farmer->setTiledMap(testMap);

    farmer->add_part("/motion/walk_down/body/body_walk_down_2.png", "body");
    farmer->add_part("/motion/walk_down/arm/arm_walk_down_2.png", "arm");
    farmer->add_tool("/motion/heavy_hit_right/hoe/hoe_heavy_hit_right_5.png", "hoe");
    farmer->add_weapon("/motion/light_hit_right/sword/sword_light_hit_right_5.png", "sword");
    farmer->add_wearing("/wearing/hat", "hat", 3);
    farmer->add_wearing("/wearing/shirt", "shirt", 2);
    farmer->add_shadow("/shadow/shadow.png");

    //farmer->setLocalZOrder(2);

    farmer->setScale(1.5);
    farmer->setPosition(Vec2(600, 500));

    farmer->regist(&motionManager, this, 2);

    // 怪物部分
    Bat* bat1 = (Bat*)Bat::create("monster/bat/bat_fly_0.png", 50, 100, this);
    bat1->setPosition(200, 300);
    bat1->regist(&motionManager, this);

    Bat* bat2 = (Bat*)Bat::create("monster/bat/bat_fly_0.png", 50, 100, this);
    bat2->setPosition(500, 300);
    bat2->regist(&motionManager, this);


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
            Player* player = farmer;
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