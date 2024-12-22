#include "BackpackLayer.h"
#include "Item.h"
#include "AudioPlayer.h"
#include "HoverButton.h"
#include "BackpackManager.h"
#include "CommercialSystem.h"

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
    this->addChild(backpackBgSprite, 3); // 层数需重设

    // 初始化背包状态
    this->maxItems = maxItems;
    this->currentItems = 0;

    // 添加关闭按钮
    addCloseButton();

    syncBagContentsToUI();
    return true;
}

void BackpackLayer::addCloseButton()
{
    // 创建关闭按钮
    auto closeButton = ui::Button::create("cancelBotton.png", "cancelBotton.png");
    if (!closeButton)
    {
        CCLOG("Failed to load close button image.");
        return;
    }

    // 设置关闭按钮的位置（右上角）
    closeButton->setAnchorPoint(Vec2(1, 1)); // 右上角对齐
    closeButton->setPosition(Vec2(backpackBgSprite->getContentSize().width + closeButton->getContentSize().width, backpackBgSprite->getContentSize().height + closeButton->getContentSize().height));

    // 添加点击事件
    closeButton->addClickEventListener([this](Ref* sender) {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        // 隐藏背包
        BackpackManager::getInstance()->hideBackpack();
        // 修改创建的flag信息
        BackpackManager::getInstance()->ifCreated = false;
        });

    // 将关闭按钮添加到背包背景上
    backpackBgSprite->addChild(closeButton, 4); // 确保关闭按钮在背包背景之上
}

bool BackpackLayer::addItemUI(const std::string& itemImagePath, int i, int id)
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
    auto commercialSystem = CommercialSystem::getInstance();

    // 设置物品位置（假设物品从左到右排列）
    float base_x = this->getPosition().x;
    float base_y = this->getPosition().y;
    float x = 530 + (currentItems % 12) * 51; // 每行 12 个物品，间隔 51
    float y = 502 - (currentItems / 12) * 55; // 每列间隔 55
    itemButton->setPosition(Vec2(x, y));

    itemButton->addClickEventListener([this, id, x, y, commercialSystem](Ref* sender)
        {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
            syncBagContentsToUI();
            if(id!=4001)
            {
                Bag::getInstance()->itemInHand = id;

                // 创建一个小窗口
                auto popupLayer = Sprite::create("../Resources/emptyscene.png");
                popupLayer->setContentSize(Size(200, 400));
                popupLayer->setPosition(Vec2(x, y));

                // 创建退出按钮
                auto backButton = ui::Button::create("ExitButton.png", "ExitPressed.png");
                backButton->setScale(0.2f);
                backButton->setPosition(Vec2(190, 380));

                // 添加按钮点击事件
                backButton->addClickEventListener([this, popupLayer](Ref* sender) {
                    // 加载点击音效
                    audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                    popupLayer->removeFromParentAndCleanup(true);
                    });

                // 将按钮添加到小窗口 Layer
                popupLayer->addChild(backButton);

                auto useButton = ui::Button::create("UseDefaultButton.png", "UsePressedButton.png");
                useButton->setScale(0.4f);
                useButton->setPosition(Vec2(100, 280));

                // 添加按钮点击事件
                useButton->addClickEventListener([this, id, popupLayer](Ref* sender)
                    {
                        // 加载点击音效
                        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                        Bag::getInstance()->itemInHand = id;
                    });
                // 将按钮添加到小窗口
                popupLayer->addChild(useButton);

                auto sellButton = ui::Button::create("SellDefaultButton.png", "SellPressedButton.png");
                sellButton->setScale(0.4f);
                sellButton->setPosition(Vec2(100, 180));

                // 添加按钮点击事件
                sellButton->addClickEventListener([this, id, popupLayer, commercialSystem](Ref* sender)
                    {
                        // 加载点击音效
                        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                        Bag::getInstance()->removeItem(id, 1);
                        auto price = commercialSystem->IDToPrice[id];
                        commercialSystem->supply(id, 1);
                        commercialSystem->update_price();
                        Bag::getInstance()->addItem(4001, price);
                        popupLayer->removeFromParentAndCleanup(true);
                        syncBagContentsToUI();
                    });
                // 将按钮添加到小窗口
                popupLayer->addChild(sellButton);

                // 将小窗口添加到场景中
                this->addChild(popupLayer, 50);
            }
        });

    // 添加物品到背包
    this->addChild(itemButton, 49);

    auto quantitylabel = Label::createWithSystemFont(std::to_string(i), "Arial", 24);
    quantitylabel->setPosition(Vec2(35, 15));
    quantitylabel->setColor(Color3B::BLACK);
    itemButton->addChild(quantitylabel, 49);
    itemButtons.push_back(itemButton);

    // 更新当前物品数量
    currentItems++;
    return true;
}