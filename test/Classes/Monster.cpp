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
    // ��λ��
    float length = sqrt(x * x + y * y);
    x /= length, y /= length;
    // ��׼�ٶ�
    float base_speed = 100;
    // һ��4֡
    const int upper_limit = 4;
    // ÿһ֡�����ļ��
    const float frameGap = 0.2;
    // ����
    auto moveAction = MoveBy::create(upper_limit * frameGap, { x * base_speed, y * base_speed });
    // ����
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

    // ��������Spawn
    auto moveSpawn = Spawn::createWithTwoActions(moveAction, animate);
    moveSpawn->setTag(1573);
    // ���if������֤�˶���������ж�������;�����
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
    // �˶�����
    const auto playerPosition = information->playerPosition;
    const auto batPosition = this->getPosition();
    Vec2 direction = { playerPosition.x - batPosition.x, playerPosition.y - batPosition.y };
    this->go(direction);
    const auto light_hit = cocos2d::EventKeyboard::KeyCode::KEY_J;

    // ��������
    const int dis = abs(playerPosition.x - batPosition.x) + abs(playerPosition.y - batPosition.y);
    if (dis < 40 && information->keyMap[light_hit])
        hitted(10);
    if (dis < 20 && information->keyMap[light_hit])
        attack_player();
}

void Bat::hitted(int score)
{
    // ��ȡ��ǰʱ��
    float currentTime = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();

    // ���ʱ����
    if (currentTime - lastHitTime < 0.1f)
    {
        return; // ���ʱ����С�� 0.1 �룬ֱ�ӷ��أ���ִ�л����߼�
    }

    // �����ϴα����е�ʱ��
    lastHitTime = currentTime;

    // ִ�л����߼�
    health -= score;
    const auto playerPosition = motionManager->playerPosition;
    const auto batPosition = this->getPosition();
    // ��׷�ٷ���
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
    // ��ȡ��ǰʱ��
    float currentTime = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();
    // ���ʱ����
    if (currentTime - lastAttackTime < 0.1f)
    {
        return; // ���ʱ����С�� 0.1 �룬ֱ�ӷ��أ���ִ�н����߼�
    }
    // �����ϴι�����ʱ��
    lastAttackTime = currentTime;
    motionManager->deltaPlayerHealth -= attack;
}

void Bat::del()
{
    motionManager->del_object(this);
    father->removeChild(this);
}