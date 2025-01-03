#pragma once
#include "cocos2d.h"
#include "Item.h"
#include "ui/UIButton.h"

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
  // 物品容器
  std::vector<ui::Button*> itemButtons;

  // 创建背包层，传入背包背景图片路径和物品上限
  static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

  // 初始化方法
  virtual bool init(const std::string& backpackBgPath, int maxItems);

  // 添加物品到背包
  bool addItemUI(const std::string& itemImagePath, int quantity,int id);

  void syncBagContentsToUI()
  {
    // 清空现有的物品显示
    for (auto Button : itemButtons)
    {
      this->removeChild(Button);
    }
    itemButtons.clear();
    currentItems = 0;

    // 根据Bag中的物品数据更新UI
    for (const auto& pair : Bag::getInstance()->_items)
    {
      int itemId = pair.first;
      int quantity = pair.second;
      if (quantity)
      {
        // 获取物品图像路径
        std::string itemImagePath = getItemImagePath(itemId);
        // 添加物品到UI
        addItemUI(itemImagePath, quantity, itemId);
      }
    }
  }

  std::string getItemImagePath(int itemId) const
  {
    return "../Resources/Item/" + std::to_string(itemId) + ".png";
  }
private:
  // 背包背景精灵
  Sprite* backpackBgSprite;
  void addCloseButton();
  // 背包物品上限
  int maxItems;

  // 当前背包中的物品数量
  int currentItems;
};