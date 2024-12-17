#include "TownScene.h"
#include "FarmScene.h"
#include "Utils/MapUtil.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "Utils/SceneUtil.h"
#include <iostream>
#include <map>

extern int all_var;

USING_NS_CC;

Scene* TownScene::createScene()
{
    return TownScene::create();
}

static std::map<EventKeyboard::KeyCode, bool> keyMap;
static bool mouse_down = false;

void TownScene::test() {

    Player* player = (Player*)this->getChildByName("meow");
    auto position = player->get_parts().at(0)->getPosition();
    auto tmxMap = player->getTiledMap();
    auto tileCoord = convertToTileCoord(tmxMap, position);
    auto layer = tmxMap->getLayer("Front");
    layer->removeTileAt(tileCoord);
    //layer->setTileGID(82, convertToTileCoord(tmxMap, position));
    //CCLOG("%f %f : %d", tileCoord.x, tileCoord.y, layer->getTileGIDAt(tileCoord));
    //CCLOG("%d", all_var);
    
}

void TownScene::update(float delta)
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
        //CCLOG("Position %f %f", pos.x, pos.y);
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
    auto layer = player->getTiledMap()->getLayer("Front");
    //layer->setTileGID(82, convertToTileCoord(player->getTiledMap(), player->getPosition()));
    test();
    //CCLOG("%f %f : %d", player->getPosition().x, player->getPosition().y, layer->getTileGIDAt(convertToTileCoord(player->getTiledMap(), player->getPosition())));

}

bool TownScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("Town.tmx");
    auto map_front = TMXTiledMap::create("Town_Front.tmx");


    // 设置地图的位置
    map->setPosition(Vec2(0, 0));
    map_front->setPosition(Vec2(0, 0));

    // 将地图添加到场景中
    this->addChild(map);
    this->addChild(map_front, 80);

    auto farmer = Player::create();
    farmer->setTiledMap(map);
    farmer->add_part("/motion/walk_up/body/body_walk_up_0.png", "body");
    farmer->add_part("/motion/walk_up/arm/arm_walk_up_0.png", "arm");

    farmer->setScale(1.5);
    farmer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    CCLOG("(%f, %f)", farmer->getPositionX(), farmer->getPositionY());
    auto farmer_parts = farmer->get_parts();

    for (auto part : farmer_parts) {
        this->addChild(part);
    }

    this->addChild(farmer, 2, "meow");
    CCLOG("(%f, %f)", farmer->getPositionX(), farmer->getPositionY());

    // 键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("press");
        keyMap[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("release");
        keyMap[keyCode] = false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



    return true;
}


void TownScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}