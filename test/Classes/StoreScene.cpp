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
    // 创建场景
    if (!Scene::init())
    {
        return false;
    }

    // 加载背景
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/emptyscene.png");
    background->setContentSize(screenSize);
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background, 2);

    // 添加人物头像到左上角
    auto avatar = Sprite::create("../Resources/Pierre.png"); // 头像图片路径
    avatar->setScale(2.5);
    avatar->setPosition(Vec2(avatar->getContentSize().width * avatar->getScale() / 2 + 30, screenSize.height - avatar->getContentSize().height * avatar->getScale() / 2 - 30)); // 左上角位置
    this->addChild(avatar, 5); // 添加到场景中，层级为 5

    BackpackManager::getInstance()->showBackpack(this, 4);
    BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();

    // 定义商品信息
    struct ProductInfo {
        std::string name;
        std::string imagePath;
        int itemId;
        int price;
    };
    auto commercialSysterm = CommercialSystem::getInstance();
    // 使用 vector 存储商品信息
    std::vector<ProductInfo> products = {
        {"legend fish", "../Resources/Item/3126.png", 3126, 114514},
        {"vegetable seed", "../Resources/Item/1100.png", 1100, 10},
        {"crop seed", "../Resources/Item/1101.png", 1101, 10},
        {"fertilizer", "../Resources/Item/1102.png", 1102, 10},
        {"pig", "../Resources/Item/2100.png", 2100, 10},
        {"wheat", "../Resources/Item/3101.png", 3101, 30}
    };
    // 商品布局参数
    const int productsPerRow = 4; // 每行显示的商品数量
    const float startX = screenSize.width / (productsPerRow + 1); // 起始 X 坐标
    const float startY = screenSize.height - 100; // 起始 Y 坐标
    const float spacingX = startX; // X 方向的间距
    const float spacingY = -200; // Y 方向的间距

    // 遍历商品信息并创建 UI
    for (size_t i = 0; i < products.size(); ++i) {
        const auto& product = products[i];

        // 计算商品的位置
        float x = startX + (i % productsPerRow) * spacingX;
        float y = startY + (i / productsPerRow) * spacingY;

        // 创建商品按钮
        auto productButton = HoverButton::create(product.imagePath, product.imagePath, product.imagePath);
        productButton->setPosition(Vec2(x, y));

        // 为商品按钮添加事件处理器
        productButton->addClickEventListener([this, product](Ref* sender) {
            // 加载点击音效
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

        // 将商品按钮添加到场景中
        this->addChild(productButton, 4);

        // 创建商品名称标签
        auto productLabel = Label::createWithSystemFont(product.name, "Arial", 24);
        productLabel->setPosition(Vec2(x, y - 70));
        productLabel->setColor(Color3B::BLACK);
        this->addChild(productLabel, 4);

        // 创建商品价格标签
        auto productPrice = Label::createWithSystemFont(std::to_string(product.price), "Arial", 24);
        productPrice->setPosition(Vec2(x - 10, y - 100));
        productPrice->setColor(Color3B::BLACK);
        this->addChild(productPrice, 4);

        // 创建金币图标
        const auto coin = Sprite::create("../Resources/coin.png");
        coin->setContentSize(Size(25, 25));
        coin->setPosition(Vec2(x + 20, y - 100));
        this->addChild(coin, 4);
    }

    // 创建返回游戏按钮
    auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
        "../Resources/BackPressedButton.png",
        "../Resources/BackDefaultButton.png");

    backButton->setScale(0.46f);

    // 设置返回按钮位置
    backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

    // 为返回按钮添加事件处理器
    backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            Director::getInstance()->popScene();
        }
        });

    // 将返回按钮添加到场景中
    this->addChild(backButton, 3);

    return true;
}