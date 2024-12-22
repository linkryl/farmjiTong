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
    this->addChild(backpackBgSprite, 3); // ����������

    // ��ʼ������״̬
    this->maxItems = maxItems;
    this->currentItems = 0;

    // ��ӹرհ�ť
    addCloseButton();

    syncBagContentsToUI();
    return true;
}

void BackpackLayer::addCloseButton()
{
    // �����رհ�ť
    auto closeButton = ui::Button::create("cancelBotton.png", "cancelBotton.png");
    if (!closeButton)
    {
        CCLOG("Failed to load close button image.");
        return;
    }

    // ���ùرհ�ť��λ�ã����Ͻǣ�
    closeButton->setAnchorPoint(Vec2(1, 1)); // ���ϽǶ���
    closeButton->setPosition(Vec2(backpackBgSprite->getContentSize().width + closeButton->getContentSize().width, backpackBgSprite->getContentSize().height + closeButton->getContentSize().height));

    // ��ӵ���¼�
    closeButton->addClickEventListener([this](Ref* sender) {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
        // ���ر���
        BackpackManager::getInstance()->hideBackpack();
        // �޸Ĵ�����flag��Ϣ
        BackpackManager::getInstance()->ifCreated = false;
        });

    // ���رհ�ť��ӵ�����������
    backpackBgSprite->addChild(closeButton, 4); // ȷ���رհ�ť�ڱ�������֮��
}

bool BackpackLayer::addItemUI(const std::string& itemImagePath, int i, int id)
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
    auto commercialSystem = CommercialSystem::getInstance();

    // ������Ʒλ�ã�������Ʒ���������У�
    float base_x = this->getPosition().x;
    float base_y = this->getPosition().y;
    float x = 530 + (currentItems % 12) * 51; // ÿ�� 12 ����Ʒ����� 51
    float y = 502 - (currentItems / 12) * 55; // ÿ�м�� 55
    itemButton->setPosition(Vec2(x, y));

    itemButton->addClickEventListener([this, id, x, y, commercialSystem](Ref* sender)
        {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
            syncBagContentsToUI();
            if(id!=4001)
            {
                Bag::getInstance()->itemInHand = id;

                // ����һ��С����
                auto popupLayer = Sprite::create("../Resources/emptyscene.png");
                popupLayer->setContentSize(Size(200, 400));
                popupLayer->setPosition(Vec2(x, y));

                // �����˳���ť
                auto backButton = ui::Button::create("ExitButton.png", "ExitPressed.png");
                backButton->setScale(0.2f);
                backButton->setPosition(Vec2(190, 380));

                // ��Ӱ�ť����¼�
                backButton->addClickEventListener([this, popupLayer](Ref* sender) {
                    // ���ص����Ч
                    audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                    popupLayer->removeFromParentAndCleanup(true);
                    });

                // ����ť��ӵ�С���� Layer
                popupLayer->addChild(backButton);

                auto useButton = ui::Button::create("UseDefaultButton.png", "UsePressedButton.png");
                useButton->setScale(0.4f);
                useButton->setPosition(Vec2(100, 280));

                // ��Ӱ�ť����¼�
                useButton->addClickEventListener([this, id, popupLayer](Ref* sender)
                    {
                        // ���ص����Ч
                        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                        Bag::getInstance()->itemInHand = id;
                    });
                // ����ť��ӵ�С����
                popupLayer->addChild(useButton);

                auto sellButton = ui::Button::create("SellDefaultButton.png", "SellPressedButton.png");
                sellButton->setScale(0.4f);
                sellButton->setPosition(Vec2(100, 180));

                // ��Ӱ�ť����¼�
                sellButton->addClickEventListener([this, id, popupLayer, commercialSystem](Ref* sender)
                    {
                        // ���ص����Ч
                        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
                        Bag::getInstance()->removeItem(id, 1);
                        auto price = commercialSystem->IDToPrice[id];
                        commercialSystem->supply(id, 1);
                        commercialSystem->update_price();
                        Bag::getInstance()->addItem(4001, price);
                        popupLayer->removeFromParentAndCleanup(true);
                        syncBagContentsToUI();
                    });
                // ����ť��ӵ�С����
                popupLayer->addChild(sellButton);

                // ��С������ӵ�������
                this->addChild(popupLayer, 50);
            }
        });

    // �����Ʒ������
    this->addChild(itemButton, 49);

    auto quantitylabel = Label::createWithSystemFont(std::to_string(i), "Arial", 24);
    quantitylabel->setPosition(Vec2(35, 15));
    quantitylabel->setColor(Color3B::BLACK);
    itemButton->addChild(quantitylabel, 49);
    itemButtons.push_back(itemButton);

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}