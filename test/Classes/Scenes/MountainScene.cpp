#include "MountainScene.h"
#include "Util.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "SceneUtil.h"
#include <iostream>
#include <map>

extern int all_var;

USING_NS_CC;

Scene* MountainScene::createScene()
{
    return MountainScene::create();
}

static std::map<EventKeyboard::KeyCode, bool> keyMap;
static bool mouse_down = false;


void MountainScene::update(float delta)
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
    //CCLOG("%f %f : %d", player->getPosition().x, player->getPosition().y, layer->getTileGIDAt(convertToTileCoord(player->getTiledMap(), player->getPosition())));

}

bool MountainScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("Mountain.tmx");
    auto map_front = TMXTiledMap::create("Mountain_Front.tmx");
    if (!map) {
        CCLOG("no Farm.tmx");
    }
    else {
        CCLOG("have Farm.tmx");
    }
    if (!map_front) {
        CCLOG("no Farm_Front.tmx");
    }
    else {
        CCLOG("have Farm_Front.tmx");
    }

    // ���õ�ͼ��λ��
    map->setPosition(Vec2(0, 0));
    map_front->setPosition(Vec2(0, 0));

    // ����ͼ���ӵ�������
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

    // �����¼�������
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


void MountainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}