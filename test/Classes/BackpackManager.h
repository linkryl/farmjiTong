#pragma once
#include "cocos2d.h"
#include "BackpackLayer.h"
#include "MotionManager.h"
#include "Item.h"

//创建 BackpackManager 单例类, 负责管理背包层的生命周期和逻辑
class BackpackManager : public Movable, public Node
{
public:
  // 是否已经创建
  bool ifCreated;
  // 获取单例实例
  static BackpackManager* getInstance();

  // 显示背包层
  bool showBackpack(Node* parent, int order);

  // 隐藏背包层
  void hideBackpack();

  // 添加物品到背包
  bool addItem(const std::string& itemImagePath, int quantity, int id);

  // 检查背包是否已满
  bool isFull() const;
  void regist(MotionManager* motionManager, Node* father);
  void moveUpdate(MotionManager* information);
  BackpackLayer* backpackLayer; // 背包层
private:
  BackpackManager();  // 构造函数私有化
  ~BackpackManager(); // 析构函数

  // 父亲节点
  Node* father;
  int maxItems;                  // 背包物品上限
  int currentItems;              // 当前背包中的物品数量
};