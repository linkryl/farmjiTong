#pragma once
#include "MotionManager.h"
class Monster : public Movable, public Sprite
{
protected:
	// Ѫ��
	int health;
	// �ٶ�
	int speed;
	// ������
	int attack; 
	// ���ڵ�
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
	float lastHitTime = 0.0f; // �ϴα����е�ʱ��
	float lastAttackTime = 0.0f; // �ϴν�����ʱ��
};