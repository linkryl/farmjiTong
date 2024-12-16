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

    // 获取窗口大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初始化背包背景
    backpackBgSprite = Sprite::create(backpackBgPath);

    if (!backpackBgSprite)
    {
        CCLOG("Failed to load backpack background image: %s", backpackBgPath.c_str());
        return false;
    }

    backpackBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    backpackBgSprite->setPosition(visibleSize / 2); 
    this->addChild(backpackBgSprite,3);//层数需重设

    // 初始化背包状态
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

    // 创建物品精灵
    auto itemButton = ui::Button::create(itemImagePath);
    if (!itemButton)
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false;
    }

    //物品映射遵照如下编码： 
    //1110为蔬菜作物，1100为蔬菜种子，1120为收获的蔬菜 
    //1111为谷物作物，1101为谷物种子，1121为收获的谷物
    //2110为猪，2100为猪仔，2120为猪肉
    //3110为镐子

    /*此处暂定*/
    // 设置物品位置（假设物品从左到右排列）
    float x = 368 + (currentItems % 12) * 51; // 每行 12 个物品，间隔 51
    float y = 412 - (currentItems / 12) * 55; // 每列间隔 55
    itemButton->setPosition(Vec2(x, y));
    /*此处暂定*/
    if (i!=-1)
    {
      auto k = Bag::getInstance()->_items.begin();
      for (int j = 0; j < i; ++j)
        if (j)
          ++k;
      int id = k->first;
    
    itemButton->addClickEventListener([this,id](Ref* sender)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

      Bag::getInstance()->itemInHand = id;
    });
    }
    else
    {
      itemButton->addClickEventListener([this](Ref* sender)
        {
          // 加载点击音效
          audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        });
    }
    // 添加物品到背包
    this->addChild(itemButton,3);
    itemButtons.pushBack(itemButton);

    // 更新当前物品数量
    currentItems++;
    return true;
}