#pragma once
#include "MotionManager.h"
class Monster : public Movable, public Sprite
{
protected:
	// 血量
	int health;
	// 速度
	int speed;
	// 攻击力
	int attack; 
	// 父节点
	Node* father;
	MotionManager* motionManager;
	void add_father(Node* father_)
	{
		father = father_;
	}
};
class Bat : public Monster
{
public:
	Bat(int attack_, int health_, Node* fa = nullptr)
	{
		attack = attack_, health = health_, father = fa;
	}
	static Bat* create(const std::string& filename, int attack, int health, Node* fa = nullptr);
	virtual void go(const Vec2& direction);
	virtual void moveUpdate(MotionManager* information);
	/*virtual void attack_player(Player* playerPtr);*/
	virtual void hitted(int score);
	virtual void attack_player();
	void del();
	void regist(MotionManager* motionManager, Node* father);
	void regist(MotionManager* motionManager, Node* father, int Zorder);
private:
	float lastHitTime = 0.0f; // 上次被击中的时间
	float lastAttackTime = 0.0f; // 上次进攻的时间
};