#include "Monster.h"
#include <cmath>
#include <string>

Bat* Bat::create(const std::string& filename, int attack, int health, Node* fa)
{
    Bat* bat = new (std::nothrow) Bat(attack, health, fa);
    if (bat && bat->initWithFile(filename))
    {
        bat->autorelease();
        return bat;
    }
    CC_SAFE_DELETE(bat);
    return nullptr;
}

void Bat::go(const Vec2& direction)
{
    float x = direction.x;
    float y = direction.y;
    // 单位化
    float length = sqrt(x * x + y * y);
    x /= length, y /= length;
    // 基准速度
    float base_speed = 100;
    // 一共4帧
    const int upper_limit = 4;
    // 每一帧动画的间隔
    const float frameGap = 0.2;
    // 动作
    auto moveAction = MoveBy::create(upper_limit * frameGap, { x * base_speed, y * base_speed });
    // 动画
    Vector<SpriteFrame*> spriteFrames;
    auto path = "monster/bat/bat_fly.plist";
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
    for (int i = 0; i < upper_limit; i++)
    {
        std::string index = std::to_string(i);
        auto imageName = "bat_fly_" + index + ".png";
        auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
        spriteFrames.pushBack(frame);
    }
    ////////*Something goes wrong here*/
    Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
    Animate* animate = Animate::create(ani);
    ///////////////

    // 动作并行Spawn
    auto moveSpawn = Spawn::createWithTwoActions(moveAction, animate);
    moveSpawn->setTag(1573);
    // 这个if条件保证了动作连贯进行而不是中途被打断
    const auto sign = this->_actionManager->getActionByTag(1573, this);
    if (this->_actionManager->getActionByTag(1573, this) == nullptr)
    {
        this->runAction(moveSpawn);
    }
}

void Bat::regist(MotionManager* motionManager, Node* father)
{
    motionManager->add_movableObject(this);
    father->addChild(this);
}
void Bat::regist(MotionManager* motionManager, Node* father, int Zorder)
{
    motionManager->add_movableObject(this);
    father->addChild(this, Zorder);
}
void Bat::moveUpdate(MotionManager* information)
{
    motionManager = information;
    // 运动部分
    const auto playerPosition = information->playerPosition;
    const auto batPosition = this->getPosition();
    Vec2 direction = { playerPosition.x - batPosition.x, playerPosition.y - batPosition.y };
    this->go(direction);
    const auto light_hit = cocos2d::EventKeyboard::KeyCode::KEY_J;

    // 攻击部分
    const int dis = abs(playerPosition.x - batPosition.x) + abs(playerPosition.y - batPosition.y);
    if (dis < 40 && information->keyMap[light_hit])
        hitted(10);
    if (dis < 20 && information->keyMap[light_hit])
        attack_player();
}

void Bat::hitted(int score)
{
    // 获取当前时间
    float currentTime = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();

    // 检查时间间隔
    if (currentTime - lastHitTime < 0.1f)
    {
        return; // 如果时间间隔小于 0.1 秒，直接返回，不执行击中逻辑
    }

    // 更新上次被击中的时间
    lastHitTime = currentTime;

    // 执行击中逻辑
    health -= score;
    const auto playerPosition = motionManager->playerPosition;
    const auto batPosition = this->getPosition();
    // 逆追踪方向
    Vec2 direction = { batPosition.x - playerPosition.x, batPosition.y - playerPosition.y };
    this->stopAllActions();
    this->go(direction);
    if (health <= 0)
    {
        del();
    }
}
void Bat::attack_player()
{
    // 获取当前时间
    float currentTime = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();
    // 检查时间间隔
    if (currentTime - lastAttackTime < 0.1f)
    {
        return; // 如果时间间隔小于 0.1 秒，直接返回，不执行进攻逻辑
    }
    // 更新上次攻击的时间
    lastAttackTime = currentTime;
    motionManager->deltaPlayerHealth -= attack;
}

void Bat::del()
{
    motionManager->del_object(this);
    father->removeChild(this);
}