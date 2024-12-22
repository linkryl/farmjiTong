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
  backpackLayer->setPosition({ 0, 0 });
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

bool BackpackManager::showBackpack(Node* parent,int order = 2)
{
  if (backpackLayer->getParent() == nullptr)
  {
      backpackLayer->setPosition({ 0, -300 });
    parent->addChild(backpackLayer, order); // 将背包层添加到当前场景
  }

  // id映射到路径
    //3020是碎石
    //3021是木头
    //3022是铁锭
    //3120是海草
    //3121是鲤鱼
    //3122是鲟鱼
    //3123是鲶鱼
    //3124是大海参
    //3125是河豚
    //3126是传说之鱼
  std::string basePath = "content/";
  std::map<int, std::string> idToPath =
  {
      {3120, "fish/Seaweed.png"},
      {3121, "fish/Carp.png"},
      {3122, "fish/Sturgeon.png"},
      {3123, "fish/Catfish.png"},
      {3124, "fish/Super_Cucumber.png"},
      {3125, "fish/Pufferfish.png"},
      {3126, "fish/Legend.png"}
  };

  auto bag = Bag::getInstance();
  const auto& items = bag->_items;
  for (const auto p : items)
  {
      auto id = p.first;
      auto quantity = p.second;
      auto path = basePath + idToPath[id];
      addItem(path, quantity, id);
  }
  return true;
}

void BackpackManager::hideBackpack()
{
  backpackLayer->removeFromParent();
}

bool BackpackManager::addItem(const std::string& itemImagePath, int quantity, int id)
{
  if (isFull())
  {
    CCLOG("Backpack is full! Cannot add more items.");
    return false;
  }

  // 调用背包层的添加物品方法
  dynamic_cast<BackpackLayer*>(backpackLayer)->addItemUI(itemImagePath, quantity, id);

  // 更新当前物品数量
  ++currentItems;
  return true;
}

bool BackpackManager::isFull() const
{
  return currentItems >= maxItems;
}
void BackpackManager::regist(MotionManager* motionManager, Node* father)
{
    this->father = father;
    motionManager->add_movableObject(this);
    father->addChild(this);
}
void BackpackManager::moveUpdate(MotionManager* information)
{
    auto backPackOpen = cocos2d::EventKeyboard::KeyCode::KEY_B;
    if (information->keyMap[backPackOpen] && !ifCreated)
    {
        //this->showBackpack(father, 15);
        backpackLayer->syncBagContentsToUI();
        father->addChild(backpackLayer, 15);
        ifCreated = true;
    }
}

//使用:
//BackpackManager::getInstance()->showBackpack(this);