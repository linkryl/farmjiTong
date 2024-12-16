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

bool BackpackManager::showBackpack(Node* parent)
{
    if (backpackLayer->getParent() == nullptr)
    {
        parent->addChild(backpackLayer, 2); // ����������ӵ���ǰ����
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

    // ���ñ�����������Ʒ����
    dynamic_cast<BackpackLayer*>(backpackLayer)->addItem(itemImagePath, -1);

    // ���µ�ǰ��Ʒ����
    ++currentItems;
    return true;
}

bool BackpackManager::isFull() const
{
    return currentItems >= maxItems;
}

//ʹ��:
//BackpackManager::getInstance()->showBackpack(this);