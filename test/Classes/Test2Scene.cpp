#include "Test2Scene.h"

#include "Util.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <map>


USING_NS_CC;

Scene* Test2Scene::createScene()
{
    return Test2Scene::create();
}

std::map<EventKeyboard::KeyCode, bool> keyMap;
TMXTiledMap* tmxMap;
bool mouse_down = false;


void Test2Scene::update(float delta)
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

    Player* player = (Player*)this->getChildByName("meow");
    auto pos = player->get_parts().at(0)->getPosition();
    if (player) {
        CCLOG("Position %f %f", pos.x, pos.y);
    }
    if (offsetX != 0)
    {
        if (!can_move(tmxMap, pos, direction)) return;
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

bool Test2Scene::init()
{

    //auto viewport = Viewport::create();
    //this->addChild(viewport);
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("Town.tmx");
    auto map2 = TMXTiledMap::create("Town_Front.tmx");
    if (!map) {
        CCLOG("Failed to load my2.tmx");
        return false;
    }
    tmxMap = map;
    ////Vec2 spritePos = sprite->getPosition();
    //for (int i = 30; i < 40; ++i) {
    //    Vec2 tilePos = convertToTileCoord(map, Vec2(i * 10, 2 * i + 80));
    //    CCLOG(std::to_string(tilePos.x).c_str());
    //    CCLOG(std::to_string(tilePos.y).c_str());
    //}
    //auto layer = map->getLayer("Buildings");
    //for (int i = 0; i < 80; ++i) {
    //    for (int j = 0; j < 65; ++j) {
    //        int id = layer->getTileGIDAt(Vec2(i, j));
    //        //CCLOG(std::to_string(id).c_str());
    //    }
    //}



    // 设置地图的位置
    map->setPosition(Vec2(0, 0));
    map2->setPosition(Vec2(0, 0));

    // 设置地图的缩放比例
    map->setScale(1.0f);

    // 将地图添加到场景中
    this->addChild(map);
    this->addChild(map2, 80);

    auto farmer = Player::create();
    farmer->setTiledMap(map);
    farmer->add_part("/motion/walk_up/body/body_walk_up_0.png", "body");
    farmer->add_part("/motion/walk_up/arm/arm_walk_up_0.png", "arm");

    //farmer->setLocalZOrder(0);

    farmer->setScale(1.5);
    //farmer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - farmer->getContentSize().height));
    farmer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    CCLOG("(%f, %f)", farmer->getPositionX(), farmer->getPositionY());
    auto farmer_parts = farmer->get_parts();
    farmer->go(DOWN);
    PlayerPart* p;
    for (auto part : farmer_parts) {
        this->addChild(part);
        p = part;
    }
    auto pp = farmer->get_parts().at(0);
        
    this->addChild(farmer, 2, "meow");
    CCLOG("(%f, %f)", p->getPositionX(), p->getPositionY());

    //键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("press");
        keyMap[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("release");
        keyMap[keyCode] = false;
        std::cout << "release" << std::endl;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}


void Test2Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}