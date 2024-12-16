/*#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "cocos2d.h"
#include <vector>
#include <string>

using namespace std;
USING_NS_CC;

struct Item
{
  int id;            // 物品ID
  string name;  // 物品名称
  int quantity;      // 物品数量
  string icon;  // 物品图标路径
  bool stackable;    // 是否可以堆叠
};

class Inventory
{
private:
  std::vector<Item> items;  // 存储物品的容器
  int rows;                 // 背包行数
  int cols;                 // 背包列数
  int maxCapacity;          // 最大容量（行 * 列）

public:
  Inventory(int rows, int cols);
  bool addItem(const Item& item);  // 添加物品
  bool removeItem(int index, int quantity); // 删除物品
  const Item& getItem(int index) const; // 获取物品
  void clear();  // 清空背包
};

Inventory::Inventory(int rows, int cols) : rows(rows), cols(cols)
{
  maxCapacity = rows * cols;
  items.resize(maxCapacity);
}

bool Inventory::addItem(const Item& item)
{
  for (int i = 0; i < items.size(); ++i)
  {
    // 找到空格或相同物品，可以堆叠
    if (items[i].id == 0 || (items[i].id == item.id && items[i].stackable))
    {
      items[i] = item;  // 将物品加入该格
      return true;
    }
  }
  return false;  // 背包已满
}

bool Inventory::removeItem(int index, int quantity)
{
  if (index >= 0 && index < items.size() && items[index].quantity >= quantity)
  {
    items[index].quantity -= quantity;
    if (items[index].quantity <= 0)
    {
      items[index].id = 0;  // 清空物品格子
      items[index].quantity = 0;
    }
    return true;
  }
  return false;
}

const Item& Inventory::getItem(int index) const
{
  return items[index];
}

void Inventory::clear()
{
  for (auto& item : items)
  {
    item.id = 0;
    item.quantity = 0;
  }
}
#endif // !_INVENTORY_H_#pragma once*/