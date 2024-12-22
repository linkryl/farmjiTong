#include "StoreScene.h"
#include "AudioPlayer.h"
#include "HoverButton.h"
#include "BackpackManager.h"
#include "BackpackLayer.h"
#include "ui/CocosGUI.h"
#include "CommercialSystem.h"
#include <vector>
#include <cmath>
#include "CommercialSystem.h"

Scene* StoreScene::createScene()
{
    auto scene = Scene::create();
    auto layer = create();
    scene->addChild(layer);
    return scene;
}

bool StoreScene::init()
{
    // ��������
    if (!Scene::init())
    {
        return false;
    }

    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/emptyscene.png");
    background->setContentSize(screenSize);
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background, 2);

    // �������ͷ�����Ͻ�
    auto avatar = Sprite::create("../Resources/Pierre.png"); // ͷ��ͼƬ·��
    avatar->setScale(2.5);
    avatar->setPosition(Vec2(avatar->getContentSize().width * avatar->getScale() / 2 + 30, screenSize.height - avatar->getContentSize().height * avatar->getScale() / 2 - 30)); // ���Ͻ�λ��
    this->addChild(avatar, 5); // ��ӵ������У��㼶Ϊ 5

    BackpackManager::getInstance()->showBackpack(this, 4);
    BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();

    // ������Ʒ��Ϣ
    struct ProductInfo {
        std::string name;
        std::string imagePath;
        int itemId;
        int price;
    };
    auto commercialSysterm = CommercialSystem::getInstance();
    // ʹ�� vector �洢��Ʒ��Ϣ
    std::vector<ProductInfo> products = {
        {"legend fish", "../Resources/Item/3126.png", 3126, 114514},
        {"vegetable seed", "../Resources/Item/1100.png", 1100, 10},
        {"crop seed", "../Resources/Item/1101.png", 1101, 10},
        {"fertilizer", "../Resources/Item/1102.png", 1102, 10},
        {"pig", "../Resources/Item/2100.png", 2100, 10},
        {"wheat", "../Resources/Item/3101.png", 3101, 30}
    };
    // ��Ʒ���ֲ���
    const int productsPerRow = 4; // ÿ����ʾ����Ʒ����
    const float startX = screenSize.width / (productsPerRow + 1); // ��ʼ X ����
    const float startY = screenSize.height - 100; // ��ʼ Y ����
    const float spacingX = startX; // X ����ļ��
    const float spacingY = -200; // Y ����ļ��

    // ������Ʒ��Ϣ������ UI
    for (size_t i = 0; i < products.size(); ++i) {
        const auto& product = products[i];

        // ������Ʒ��λ��
        float x = startX + (i % productsPerRow) * spacingX;
        float y = startY + (i / productsPerRow) * spacingY;

        // ������Ʒ��ť
        auto productButton = HoverButton::create(product.imagePath, product.imagePath, product.imagePath);
        productButton->setPosition(Vec2(x, y));

        // Ϊ��Ʒ��ť����¼�������
        productButton->addClickEventListener([this, product](Ref* sender) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
            Bag::getInstance()->addItem(product.itemId, 1);
            if (Bag::getInstance()->_items[4001] >= product.price)
            {
                Bag::getInstance()->removeItem(4001, product.price);
                auto commercialSystem = CommercialSystem::getInstance();
                commercialSystem->demand(product.itemId, 1);
                commercialSystem->update_price();
            }
            else
                log("money is not enough");
            BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();
            });

        // ����Ʒ��ť��ӵ�������
        this->addChild(productButton, 4);

        // ������Ʒ���Ʊ�ǩ
        auto productLabel = Label::createWithSystemFont(product.name, "Arial", 24);
        productLabel->setPosition(Vec2(x, y - 70));
        productLabel->setColor(Color3B::BLACK);
        this->addChild(productLabel, 4);

        // ������Ʒ�۸��ǩ
        auto productPrice = Label::createWithSystemFont(std::to_string(product.price), "Arial", 24);
        productPrice->setPosition(Vec2(x - 10, y - 100));
        productPrice->setColor(Color3B::BLACK);
        this->addChild(productPrice, 4);

        // �������ͼ��
        const auto coin = Sprite::create("../Resources/coin.png");
        coin->setContentSize(Size(25, 25));
        coin->setPosition(Vec2(x + 20, y - 100));
        this->addChild(coin, 4);
    }

    // ����������Ϸ��ť
    auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
        "../Resources/BackPressedButton.png",
        "../Resources/BackDefaultButton.png");

    backButton->setScale(0.46f);

    // ���÷��ذ�ťλ��
    backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

    // Ϊ���ذ�ť����¼�������
    backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            Director::getInstance()->popScene();
        }
        });

    // �����ذ�ť��ӵ�������
    this->addChild(backButton, 3);

    return true;
}