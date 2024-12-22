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
  int id;            // ��ƷID
  string name;  // ��Ʒ����
  int quantity;      // ��Ʒ����
  string icon;  // ��Ʒͼ��·��
  bool stackable;    // �Ƿ���Զѵ�
};

class Inventory
{
private:
  std::vector<Item> items;  // �洢��Ʒ������
  int rows;                 // ��������
  int cols;                 // ��������
  int maxCapacity;          // ����������� * �У�

public:
  Inventory(int rows, int cols);
  bool addItem(const Item& item);  // �����Ʒ
  bool removeItem(int index, int quantity); // ɾ����Ʒ
  const Item& getItem(int index) const; // ��ȡ��Ʒ
  void clear();  // ��ձ���
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
    // �ҵ��ո����ͬ��Ʒ�����Զѵ�
    if (items[i].id == 0 || (items[i].id == item.id && items[i].stackable))
    {
      items[i] = item;  // ����Ʒ����ø�
      return true;
    }
  }
  return false;  // ��������
}

bool Inventory::removeItem(int index, int quantity)
{
  if (index >= 0 && index < items.size() && items[index].quantity >= quantity)
  {
    items[index].quantity -= quantity;
    if (items[index].quantity <= 0)
    {
      items[index].id = 0;  // �����Ʒ����
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