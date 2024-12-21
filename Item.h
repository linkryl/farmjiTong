#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"

class Bag : public cocos2d::Ref
{
public:
  static Bag* getInstance();

  // 禁用拷贝构造函数和赋值操作符
  Bag(const Bag&) = delete;
  Bag& operator=(const Bag&) = delete;

  // 添加物品到背包
  void addItem(int itemId, int quantity);

  // 移除物品从背包
  bool removeItem(int itemId, int quantity);

  // 获取物品数量
  int getItemQuantity(int itemId) const;

  // 背包内容的容器，可以是std::map或其他适合的数据结构
  std::map<int, int> _items; // 使用物品ID作为键，数量作为值

  int itemInHand;
  //替换手中道具
  void changeHand(int itemId, int quantity);
private:
  Bag(); // 私有构造函数
  ~Bag(); // 私有析构函数

  static Bag* _instance; // 单例指针
};

#endif // _ITEM_H_