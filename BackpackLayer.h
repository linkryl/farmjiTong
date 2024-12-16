#include "cocos2d.h"
#include "Item.h"
#include "ui/UIButton.h"

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
    // ��Ʒ����
    Vector<ui::Button*> itemButtons;

    // ���������㣬���뱳������ͼƬ·������Ʒ����
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    // ��ʼ������
    virtual bool init(const std::string& backpackBgPath, int maxItems);

    // �����Ʒ������
    bool addItem(const std::string& itemImagePath,int i);

private:
    // ������������
    Sprite* backpackBgSprite;

    // ������Ʒ����
    int maxItems;

    // ��ǰ�����е���Ʒ����
    int currentItems;

    void syncBagContentsToUI()
    {
      // ������е���Ʒ��ʾ
      for (auto& Button : itemButtons)
      {
        this->removeChild(Button);
      }
      itemButtons.clear();
      currentItems = 0;

      // ����Bag�е���Ʒ���ݸ���UI
      for (const auto& pair : Bag::getInstance()->_items)
      {
        int itemId = pair.first;
        int quantity = pair.second;

        // ��ȡ��Ʒͼ��·��
        std::string itemImagePath = getItemImagePath(itemId);

        // �����Ʒ��UI
        for (int i = 0; i < quantity; ++i)
        {
          addItem(itemImagePath,i);
        }
      }
    }

    std::string getItemImagePath(int itemId) const
    {
      return "../Resources/Item/" + std::to_string(itemId) + ".png";
    }
};