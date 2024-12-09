#include "Player.h"
#include "Util.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <map>

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

std::map<EventKeyboard::KeyCode, bool> keyMap;
bool mouse_down = false;
TMXTiledMap* tmxMap;

void HelloWorld::update(float delta)
{
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    auto light_hit = cocos2d::EventKeyboard::KeyCode::KEY_J;
    auto heavy_hit = cocos2d::EventKeyboard::KeyCode::KEY_K;

    int offsetX = 0;
    Direction direction;
    if (keyMap[left])
    {
        offsetX = -4;
        direction = LEFT;
    }
    else if (keyMap[right])
    {
        offsetX = 4;
        direction = RIGHT;
    }
    else if (keyMap[down])
    {
        offsetX = 4;
        direction = DOWN;
    }
    else if (keyMap[up])
    {
        offsetX = 4;
        direction = UP;
    }

    Player* player = (Player*)this->getChildByTag(114514);
    auto pos = player->get_parts().at(0)->getPosition();
    if (player) {
        CCLOG("Position %f %f", pos.x, pos.y);
    }
    if (offsetX != 0)
    {
        if (!can_move(player->getTiledMap(), pos, direction)) return;
        player->go(direction);
    }

    if (keyMap[light_hit])
    {
        player->light_hit();
    }
    else if (keyMap[heavy_hit])
    {
        player->heavy_hit();
    }
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
    auto testMap = TMXTiledMap::create("Cave.tmx");
    testMap->setPosition(Vec2(0, 0));
    if (!testMap) {
        CCLOG("Failed to load Town.tmx");
        return false;
    }
    tmxMap = testMap;
    addChild(testMap, -8);
    auto testLayer = testMap->getLayer("Front");
    //testLayer->setLocalZOrder(11);

    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "Hello World"
    // create and initialize a label
    // Ìí¼ÓËÑË÷Â·¾¶
    FileUtils::getInstance()->addSearchPath("E:\\cocos2d-x-3.17.2\\cocos2d-x-3.17.2\\testCpp2\\proj.win32\\Debug.win32\\content");

    auto farmer = Player::create();
    farmer->setTiledMap(testMap);
    
    farmer->add_part("/motion/walk_up/body/body_walk_up_0.png", "body");
    farmer->add_part("/motion/walk_up/arm/arm_walk_up_0.png", "arm");
    farmer->add_tool("/motion/heavy_hit_right/axe/axe_heavy_hit_right_5.png", "axe");

    farmer->setLocalZOrder(0);

    farmer->setScale(1.5);
    //farmer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - farmer->getContentSize().height));

    farmer->setPosition(Vec2(600, 500));

    auto farmer_parts = farmer->get_parts();
    auto farmer_tools = farmer->get_tools();

    for (auto part : farmer_parts)
        this->addChild(part);
    for (auto tool : farmer_tools)
        this->addChild(tool);

    farmer->go(DOWN);

    this->addChild(farmer, 2, 114514);

    //¼üÅÌÊÂ¼þ¼àÌýÆ÷
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("press");
        keyMap[keyCode] = true;
        };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("release");
        keyMap[keyCode] = false;
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