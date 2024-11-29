/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Player.h"
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

void HelloWorld::update(float delta)
{
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;

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

    if (offsetX == 0) return;

    Player* sprite = (Player*)this->getChildByTag(114514);
    /*auto moveTo = MoveTo::create(0.2, Vec2(sprite->getPositionX() + offsetX, sprite->getPositionY()));
    sprite->runAction(moveTo);*/
    sprite->go(direction);
    /*// int-动作映射map
    int speed = 1;
    static std::map<int, Vec2> intToMove = { {UP, Vec2(0, speed * 1)}, {RIGHT, Vec2(speed * 1, 0)},
    { DOWN, Vec2(0, -speed * 1) }, {LEFT, Vec2(-speed * 1, 0)} };
    // 动作
    auto move = MoveBy::create(2, intToMove[direction]);
    this->runAction(move);
    // 数字映射到string
    std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
    // 动画
    Vector<SpriteFrame*> spriteFrames;
    auto direct = numToString[direction];
    auto path = "/motion/" + direct + "/" + direct + ".plist";
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
    // DOWN动画要多两帧
    const int upper_limit = direction == DOWN ? 7 : 5;
    for (int i = 0; i <= upper_limit; i++)
    {
        std::string direct = numToString[direction];
        std::string index = std::to_string(i);
        auto imageName = direct + "-" + index + ".png";
        auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
        //std::string path = "\\motion\\" + direct + "\\" + direct + "-" + index + ".png";
        //auto frame = SpriteFrame::create(path, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrames.pushBack(frame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrames, 0.5);
    Animate* animate = Animate::create(ani);
    // 动作并行Spawn
    auto moveSpawn = Spawn::createWithTwoActions(move, animate);
    sprite->runAction(moveSpawn);*/
}
/*void HelloWorld::update()
{
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;

    Player* sprite = (Player*)this->getChildByTag(114514);
    if (keyMap[left])
    {
        sprite->go(LEFT);
    }
    if (keyMap[right])
    {
        sprite->go(RIGHT);
    }
    if (keyMap[up])
    {
        sprite->go(UP);
    }
    if (keyMap[down])
    {
        sprite->go(DOWN);
    }
}*/

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
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "Hello World"
    // create and initialize a label
    // 添加搜索路径
    FileUtils::getInstance()->addSearchPath("E:\\cocos2d-x-3.17.2\\cocos2d-x-3.17.2\\testCpp2\\proj.win32\\Debug.win32\\content");
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    // 加载图集
    // load the Sprite Sheet

    auto farmer = Player::create("\\motion\\walk_up\\walk_up-0.png");
    farmer->setScale(1.5);
    farmer->setPosition(Vec2(50, 50));
    this->addChild(farmer, 1, 114514);
    farmer->go(UP);

    //键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("press");
        keyMap[keyCode] = true;
        /*if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S)
        {
            farmer->go(DOWN);
        }
        else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D)
        {
            farmer->go(RIGHT);
        }
        else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W)
        {
            farmer->go(UP);
        }*/
        
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("release");
        keyMap[keyCode] = false;
        std::cout << "release" << std::endl;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
