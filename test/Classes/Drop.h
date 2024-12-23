#pragma once
#include "cocos2d.h"
#include "MotionManager.h"
#include "Item.h"
#include "skill.h"

class Drop : public cocos2d::Sprite, public Movable
{
protected:
    MotionManager* motionManager;
    cocos2d::Node* father;
    virtual void drop() = 0;

    void moveUpdate(MotionManager* information)
    {
        auto hit = cocos2d::EventKeyboard::KeyCode::KEY_K;
        auto playerPosition = information->playerPosition;
        auto playerX = playerPosition.x, playerY = playerPosition.y;
        auto thisPosition = getPosition();

        float scaleX = this->getScaleX();
        float scaleY = this->getScaleY();

        // 获取精灵的原始大小
        Size contentSize = this->getContentSize();
        float scaledHeight = contentSize.height * scaleY;
        auto thisX = thisPosition.x, thisY = thisPosition.y - scaledHeight / 2;
        if (abs(thisX - playerX) + abs(thisY - playerY) <= 30 && information->keyMap[hit])
        {
            CCLOG("Drop condition met, scheduling delayedDrop.");
            scheduleOnce(CC_SCHEDULE_SELECTOR(Drop::delayedDrop), 0.40f);
        }
    }

    void delayedDrop(float dt)
    {
        CCLOG("delayedDrop called.");
        drop();
    }

    void del()
    {
        motionManager->del_object(this);
        father->removeChild(this);
    }

public:
    void regist(MotionManager* information, cocos2d::Node* father)
    {
        this->father = father;
        motionManager = information;
        information->add_movableObject(this);
        father->addChild(this, 20);
    }
};

class Stone : public Drop
{
public:
    static Stone* create(const std::string& path)
    {
        Stone* stone = new Stone();
        if (stone && stone->initWithFile(path))
        {
            stone->autorelease();
            return stone;
        }
        CC_SAFE_DELETE(stone);
        return nullptr;
    }

protected:
    void drop()
    {
        auto bag = Bag::getInstance();
        // 掉落概率
        srand(time(0));
        std::map<int, float> probabilities = { {3021, 1}, {3022, 0.30}, {3023, 0.40}, {3024, 0.20}, {3025,0.05}, {3026,0.01}, {3027,0.001} };
        for (int i = 3021; i <= 3027; i++)
        {
            float probability = probabilities[i];
            while (probability >= 1)
            {
                probability -= 1;
                bag->addItem(i, 1);
            }
            int a = rand() % (int)(1 / probability);
            if (a == 0)
                bag->addItem(i, 1);
        }
        auto skill = Skill::getInstance();
        skill->add_collect_exp(1);
        del();
    }
};

class Tree : public Drop
{
public:
    static Tree* create(const std::string& path)
    {
        Tree* tree = new Tree();
        if (tree && tree->initWithFile(path))
        {
            tree->autorelease();
            return tree;
        }
        CC_SAFE_DELETE(tree);
        return nullptr;
    }

protected:
    void drop()
    {
        auto bag = Bag::getInstance();
        bag->addItem(3020, 4);
        auto skill = Skill::getInstance();
        skill->add_collect_exp(1);
        del();
    }
};