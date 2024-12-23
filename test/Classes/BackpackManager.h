#pragma once
#include "cocos2d.h"
#include "BackpackLayer.h"
#include "MotionManager.h"
#include "Item.h"

//���� BackpackManager ������, �������������������ں��߼�
class BackpackManager : public Movable, public Node
{
public:
  // �Ƿ��Ѿ�����
  bool ifCreated;
  // ��ȡ����ʵ��
  static BackpackManager* getInstance();

  // ��ʾ������
  bool showBackpack(Node* parent, int order);

  // ���ر�����
  void hideBackpack();

  // �����Ʒ������
  bool addItem(const std::string& itemImagePath, int quantity, int id);

  // ��鱳���Ƿ�����
  bool isFull() const;
  void regist(MotionManager* motionManager, Node* father);
  void moveUpdate(MotionManager* information);
  BackpackLayer* backpackLayer; // ������
private:
  BackpackManager();  // ���캯��˽�л�
  ~BackpackManager(); // ��������

  // ���׽ڵ�
  Node* father;
  int maxItems;                  // ������Ʒ����
  int currentItems;              // ��ǰ�����е���Ʒ����
};