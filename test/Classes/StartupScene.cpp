#include "StartupScene.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"
#include "proj.win32/InitialScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* StartupScene::createScene()
{
  auto scene = Scene::create();
  auto layer = StartupScene::create();
  scene->addChild(layer);
  return scene;
}

// on "init" you need to initialize your instance
bool StartupScene::init()
{
    // 创建场景
    if ( !Scene::init() )
    {
        return false;
    }

    // 加载音乐
    audioPlayer("../Resources/mp.mp3", true);//未确定
/*
    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/HelloWorld.png");//未确定
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);
    
    // 创建进度条
    auto progressBar = ui::LoadingBar::create("../Resources/HelloWorld.png");//未确定
    progressBar->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + STARTUP_SCENE_LOADINGBAR_OFFSET_Y));
    progressBar->setPercent(0);
    this->addChild(progressBar);

    // 创建标签以显示进度
    auto progressLabel = Label::createWithTTF("0%", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", STARTUP_SCENE_FONT_SIZE);//未确定
    progressLabel->setPosition(Vec2(progressBar->getPosition().x - progressBar->getContentSize().width / 2 + STARTUP_SCENE_LOADING_LABEL_OFFSET_X, progressBar->getPosition().y));
    progressLabel->setVisible(false);
    this->addChild(progressLabel);

    // 更新进度条和标签
    constexpr float interval = STARTUP_SCENE_DURATION / 100.0f; // 每 1% 所需时间
    for (int i = 0; i <= 100; i++) {
      this->scheduleOnce([progressBar, progressLabel, i](float dt) {
        progressLabel->setVisible(i >= 10);
        progressBar->setPercent(i);
        progressLabel->setString(std::to_string(i) + "%");
        float percentage = progressBar->getPercent() / 100.0f;
        float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + STARTUP_SCENE_LOADING_LABEL_OFFSET_X;
        progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
        }, interval * i, "UpdateStartupLoadingBar" + std::to_string(i));
    }
    
    // 设置计时器
    this->scheduleOnce([](float dt) {
      auto transition = TransitionFade::create(SCENE_TRANSITION_DURATION, InitialScene::createScene(), Color3B::WHITE);
      Director::getInstance()->replaceScene(transition);
      }, STARTUP_SCENE_DURATION + SCENE_TRANSITION_DURATION, "StartupSceneToInitialScene");
*/
    return true;
}