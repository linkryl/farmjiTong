/*#include "ui/CocosGUI.h"
#include "Inventory.h"

void InventoryLayer::createInventoryUI(const Inventory& inventory)
{
  int rows = inventory.getRows();
  int cols = inventory.getCols();

  float gridSize = 70.0f;  // ÿ�����ӵĴ�С

  // ����������������
  auto gridLayout = ui::Layout::create();
  gridLayout->setContentSize(Size(cols * gridSize, rows * gridSize));
  gridLayout->setPosition(Vec2(100, 100));

  // ���������е���Ʒ����䵽������
  for (int i = 0; i < rows * cols; ++i)
  {
    auto item = inventory.getItem(i);
    auto itemLayout = ui::Layout::create();
    itemLayout->setContentSize(Size(gridSize, gridSize));

    if (item.id != 0) {
      // ������Ʒͼ��
      auto icon = Sprite::create(item.icon);
      icon->setPosition(Vec2(gridSize / 2, gridSize / 2));
      itemLayout->addChild(icon);

      // ��ʾ��Ʒ����
      auto label = Label::createWithSystemFont(
        to_string(item.quantity), "Arial", 18);
      label->setPosition(Vec2(gridSize / 2, gridSize / 4));
      itemLayout->addChild(label);
    }

    itemLayout->setTag(i);  // Ϊÿ����������Ψһ��ǩ
    gridLayout->addChild(itemLayout);
  }

  this->addChild(gridLayout);
}*/