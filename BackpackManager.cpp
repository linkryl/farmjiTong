#include "BackpackManager.h"

USING_NS_CC;

BackpackManager* BackpackManager::getInstance()
{
    static BackpackManager instance; // 静态实例，确保全局唯一
    return &instance;
}

/*此处暂定*/
BackpackManager::BackpackManager()
{
    // 初始化背包层
    backpackLayer = BackpackLayer::create("backitem.png", 36); // 背包背景图片为 "backpack.png"，上限为 36 个物品
    backpackLayer->retain(); // 保留背包层，防止被释放

    // 初始化背包状态
    maxItems = 36;
    currentItems = 0;
}
/*此处暂定*/

BackpackManager::~BackpackManager()
{
    backpackLayer->release(); // 释放背包层
}

bool BackpackManager::showBackpack(Node* parent)
{
    if (backpackLayer->getParent() == nullptr)
    {
        parent->addChild(backpackLayer, 2); // 将背包层添加到当前场景
        backpackLayer->setLocalZOrder(1);
    }
    return true;
}

void BackpackManager::hideBackpack()
{
    backpackLayer->removeFromParent();
}

bool BackpackManager::addItem(const std::string& itemImagePath)
{
    if (isFull())
    {
        CCLOG("Backpack is full! Cannot add more items.");
        return false;
    }

    // 调用背包层的添加物品方法
    dynamic_cast<BackpackLayer*>(backpackLayer)->addItem(itemImagePath, -1);

    // 更新当前物品数量
    ++currentItems;
    return true;
}

bool BackpackManager::isFull() const
{
    return currentItems >= maxItems;
}

//使用:
//BackpackManager::getInstance()->showBackpack(this);