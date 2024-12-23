/*#include "ui/CocosGUI.h"
#include "Inventory.h"

void InventoryLayer::createInventoryUI(const Inventory& inventory)
{
  int rows = inventory.getRows();
  int cols = inventory.getCols();

  float gridSize = 70.0f;  // 每个格子的大小

  // 创建背包的主容器
  auto gridLayout = ui::Layout::create();
  gridLayout->setContentSize(Size(cols * gridSize, rows * gridSize));
  gridLayout->setPosition(Vec2(100, 100));

  // 遍历背包中的物品，填充到格子中
  for (int i = 0; i < rows * cols; ++i)
  {
    auto item = inventory.getItem(i);
    auto itemLayout = ui::Layout::create();
    itemLayout->setContentSize(Size(gridSize, gridSize));

    if (item.id != 0) {
      // 创建物品图标
      auto icon = Sprite::create(item.icon);
      icon->setPosition(Vec2(gridSize / 2, gridSize / 2));
      itemLayout->addChild(icon);

      // 显示物品数量
      auto label = Label::createWithSystemFont(
        to_string(item.quantity), "Arial", 18);
      label->setPosition(Vec2(gridSize / 2, gridSize / 4));
      itemLayout->addChild(label);
    }

    itemLayout->setTag(i);  // 为每个格子设置唯一标签
    gridLayout->addChild(itemLayout);
  }

  this->addChild(gridLayout);
}*/