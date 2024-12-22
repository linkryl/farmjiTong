#include "BackpackManager.h"

USING_NS_CC;

BackpackManager* BackpackManager::getInstance()
{
  static BackpackManager instance; // ��̬ʵ����ȷ��ȫ��Ψһ
  return &instance;
}

/*�˴��ݶ�*/
BackpackManager::BackpackManager()
{
  // ��ʼ��������
  backpackLayer = BackpackLayer::create("backitem.png", 36); // ��������ͼƬΪ "backpack.png"������Ϊ 36 ����Ʒ
  backpackLayer->setPosition({ 0, 0 });
  backpackLayer->retain(); // ���������㣬��ֹ���ͷ�

  // ��ʼ������״̬
  maxItems = 36;
  currentItems = 0;
}
/*�˴��ݶ�*/

BackpackManager::~BackpackManager()
{
  backpackLayer->release(); // �ͷű�����
}

bool BackpackManager::showBackpack(Node* parent,int order = 2)
{
  if (backpackLayer->getParent() == nullptr)
  {
      backpackLayer->setPosition({ 0, -300 });
    parent->addChild(backpackLayer, order); // ����������ӵ���ǰ����
  }

  // idӳ�䵽·��
    //3020����ʯ
    //3021��ľͷ
    //3022������
    //3120�Ǻ���
    //3121������
    //3122������
    //3123������
    //3124�Ǵ󺣲�
    //3125�Ǻ���
    //3126�Ǵ�˵֮��
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

  // ���ñ�����������Ʒ����
  dynamic_cast<BackpackLayer*>(backpackLayer)->addItemUI(itemImagePath, quantity, id);

  // ���µ�ǰ��Ʒ����
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

//ʹ��:
//BackpackManager::getInstance()->showBackpack(this);