#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"

class Bag : public cocos2d::Ref
{
public:
  static Bag* getInstance();

  // ���ÿ������캯���͸�ֵ������
  Bag(const Bag&) = delete;
  Bag& operator=(const Bag&) = delete;

  // �����Ʒ������
  void addItem(int itemId, int quantity);

  // �Ƴ���Ʒ�ӱ���
  bool removeItem(int itemId, int quantity);

  // ��ȡ��Ʒ����
  int getItemQuantity(int itemId) const;

  // �������ݵ�������������std::map�������ʺϵ����ݽṹ
  std::map<int, int> _items; // ʹ����ƷID��Ϊ����������Ϊֵ

  int itemInHand;
  //�滻���е���
  void changeHand(int itemId, int quantity);
private:
  Bag(); // ˽�й��캯��
  ~Bag(); // ˽����������

  static Bag* _instance; // ����ָ��
};

#endif // _ITEM_H_