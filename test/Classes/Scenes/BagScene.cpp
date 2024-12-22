#include "BagScene.h"
#include "AudioPlayer.h"
#include "HoverButton.h"
#include "ui/CocosGUI.h"
#include "BackpackManager.h"

Scene* BagScene::createScene()
{
    auto scene = Scene::create();
    auto layer = create();
    scene->addChild(layer);
    return scene;
}

bool BagScene::init()
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

    // 显示背包
    BackpackManager::getInstance()->showBackpack(this, 4);
    BackpackManager::getInstance()->backpackLayer->syncBagContentsToUI();

    // 创建返回按钮
    auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
        "../Resources/BackPressedButton.png",
        "../Resources/BackDefaultButton.png");

    backButton->setScale(0.46f);
    backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

    backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
            Director::getInstance()->popScene();
        }
        });

    this->addChild(backButton, 3);

    // 添加技能 UI
    Skill* mySkill = Skill::getInstance();

    // 收集技能
    const auto collectpng = Sprite::create("../Resources/CollectIcon.png");
    collectpng->setContentSize(Size(100, 100));
    collectpng->setPosition(Vec2(80, 650));
    this->addChild(collectpng, 3);

    auto collectLabel = Label::createWithSystemFont("Collect", "Arial", 24);
    collectLabel->setPosition(Vec2(180, 650));
    collectLabel->setColor(Color3B::BLACK);
    this->addChild(collectLabel, 3);

    for (int h = 0; h < 5; ++h) {
        if (h < mySkill->collect_level) {
            const auto level = Sprite::create("../Resources/SkillLevel.png");
            level->setContentSize(Size(40, 40));
            level->setPosition(Vec2(250 + h * 40, 650));
            this->addChild(level, 3);
        }
        else {
            const auto delevel = Sprite::create("../Resources/SkillDelevel.png");
            delevel->setContentSize(Size(40, 40));
            delevel->setPosition(Vec2(250 + h * 40, 650));
            this->addChild(delevel, 3);
        }
    }

    // 农场技能
    const auto farmpng = Sprite::create("../Resources/FarmIcon.png");
    farmpng->setContentSize(Size(100, 100));
    farmpng->setPosition(Vec2(80, 550));
    this->addChild(farmpng, 3);

    auto farmLabel = Label::createWithSystemFont("Farm", "Arial", 24);
    farmLabel->setPosition(Vec2(180, 550));
    farmLabel->setColor(Color3B::BLACK);
    this->addChild(farmLabel, 3);

    for (int h = 0; h < 5; ++h) {
        if (h < mySkill->farm_level) {
            const auto level = Sprite::create("../Resources/SkillLevel.png");
            level->setContentSize(Size(40, 40));
            level->setPosition(Vec2(250 + h * 40, 550));
            this->addChild(level, 3);
        }
        else {
            const auto delevel = Sprite::create("../Resources/SkillDelevel.png");
            delevel->setContentSize(Size(40, 40));
            delevel->setPosition(Vec2(250 + h * 40, 550));
            this->addChild(delevel, 3);
        }
    }

    // 钓鱼技能
    const auto fishingpng = Sprite::create("../Resources/FishIcon.png");
    fishingpng->setContentSize(Size(100, 100));
    fishingpng->setPosition(Vec2(80, 450));
    this->addChild(fishingpng, 3);

    auto fishingLabel = Label::createWithSystemFont("Fishing", "Arial", 24);
    fishingLabel->setPosition(Vec2(180, 450));
    fishingLabel->setColor(Color3B::BLACK);
    this->addChild(fishingLabel, 3);

    for (int h = 0; h < 5; ++h) {
        if (h < mySkill->fishing_level) {
            const auto level = Sprite::create("../Resources/SkillLevel.png");
            level->setContentSize(Size(40, 40));
            level->setPosition(Vec2(250 + h * 40, 450));
            this->addChild(level, 3);
        }
        else {
            const auto delevel = Sprite::create("../Resources/SkillDelevel.png");
            delevel->setContentSize(Size(40, 40));
            delevel->setPosition(Vec2(250 + h * 40, 450));
            this->addChild(delevel, 3);
        }
    }

    return true;
}