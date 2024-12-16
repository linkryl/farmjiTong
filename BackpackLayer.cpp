#include "BackpackLayer.h"
#include "Item.h"
#include "AudioPlayer.h"
#include "HoverButton.h"

USING_NS_CC;

BackpackLayer* BackpackLayer::create(const std::string& backpackBgPath, int maxItems)
{
    auto layer = new (std::nothrow) BackpackLayer();
    if (layer && layer->init(backpackBgPath, maxItems))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool BackpackLayer::init(const std::string& backpackBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }

    // ��ȡ���ڴ�С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��ʼ����������
    backpackBgSprite = Sprite::create(backpackBgPath);

    if (!backpackBgSprite)
    {
        CCLOG("Failed to load backpack background image: %s", backpackBgPath.c_str());
        return false;
    }

    backpackBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    backpackBgSprite->setPosition(visibleSize / 2); 
    this->addChild(backpackBgSprite,3);//����������

    // ��ʼ������״̬
    this->maxItems = maxItems;
    this->currentItems = 0;

    syncBagContentsToUI();
    return true;
}

bool BackpackLayer::addItem(const std::string& itemImagePath,int i)
{
    if (currentItems >= maxItems)
    {
        CCLOG("Backpack is full! Cannot add more items.");
        return false;
    }

    // ������Ʒ����
    auto itemButton = ui::Button::create(itemImagePath);
    if (!itemButton)
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false;
    }

    //��Ʒӳ���������±��룺 
    //1110Ϊ�߲����1100Ϊ�߲����ӣ�1120Ϊ�ջ���߲� 
    //1111Ϊ�������1101Ϊ�������ӣ�1121Ϊ�ջ�Ĺ���
    //2110Ϊ��2100Ϊ���У�2120Ϊ����
    //3110Ϊ����

    /*�˴��ݶ�*/
    // ������Ʒλ�ã�������Ʒ���������У�
    float x = 368 + (currentItems % 12) * 51; // ÿ�� 12 ����Ʒ����� 51
    float y = 412 - (currentItems / 12) * 55; // ÿ�м�� 55
    itemButton->setPosition(Vec2(x, y));
    /*�˴��ݶ�*/
    if (i!=-1)
    {
      auto k = Bag::getInstance()->_items.begin();
      for (int j = 0; j < i; ++j)
        if (j)
          ++k;
      int id = k->first;
    
    itemButton->addClickEventListener([this,id](Ref* sender)
    {
      // ���ص����Ч
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

      Bag::getInstance()->itemInHand = id;
    });
    }
    else
    {
      itemButton->addClickEventListener([this](Ref* sender)
        {
          // ���ص����Ч
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        });
    }
    // �����Ʒ������
    this->addChild(itemButton,3);
    itemButtons.pushBack(itemButton);

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}