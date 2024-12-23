#include "SettingsScene.h"
#include "HoverButton.h"
#include "MenuScene.h"
#include "constant.h"
#include "AudioEngine.h"

USING_NS_CC;

// 音频引擎设置
int g_backgroundMusicSign = DEFAULT_MUSIC_SIGN;
int g_soundEffectSign = DEFAULT_MUSIC_SIGN;
float g_backgroundMusicVolumn = DEFAULT_MUSIC_VOLUMN;
float g_soundEffectVolumn = DEFAULT_MUSIC_VOLUMN;

void audioPlayer(const std::string& audioPath, bool isLoop)
{
  if (isLoop)
  {
    if (g_backgroundMusicSign != -1)
    {
      experimental::AudioEngine::stop(g_backgroundMusicSign);
    }
    g_backgroundMusicSign = experimental::AudioEngine::play2d(audioPath, isLoop);
    experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
  }
  else
  {
    g_soundEffectSign = experimental::AudioEngine::play2d(audioPath, isLoop);
    experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
  }
}

Scene* SettingsScene::createScene()
{
  auto scene = Scene::create();
  auto layer = create();
  scene->addChild(layer);
  return scene;
}

bool SettingsScene::init()
{
  // 创建场景
  if (!Scene::init())
  {
    return false;
  }

  // 加载音乐
  audioPlayer("../Resources/Music/stardew.mp3", true);

  // 加载背景
  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/SettingsScene.png");
  background->setScale(1.5f);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background);

  // 创建滑动条
  auto backgroundMusicVolumnSlider = ui::Slider::create();
  backgroundMusicVolumnSlider->loadBarTexture("../Resources/SliderBackground.png");
  backgroundMusicVolumnSlider->loadSlidBallTextures("../Resources/SliderNodeNormal.png",
    "../Resources/SliderNodeDisable.png",
    "../Resources/SliderNodeDisable.png");
  backgroundMusicVolumnSlider->loadProgressBarTexture("../Resources/SliderBar.png");
  backgroundMusicVolumnSlider->setPosition(Vec2(screenSize.width / 2 - 50, screenSize.height / 2 + 86));
  backgroundMusicVolumnSlider->setPercent(g_backgroundMusicVolumn * 100);
  auto effectVolumnslider = ui::Slider::create();
  effectVolumnslider->loadBarTexture("../Resources/SliderBackground.png");
  effectVolumnslider->loadSlidBallTextures("../Resources/SliderNodeNormal.png",
    "../Resources/SliderNodeDisable.png",
    "../Resources/SliderNodeDisable.png");
  effectVolumnslider->loadProgressBarTexture("../Resources/SliderBar.png");
  effectVolumnslider->setPosition(Vec2(screenSize.width / 2 - 50, screenSize.height / 2 - 30));
  effectVolumnslider->setPercent(g_soundEffectVolumn * 100);

  // 为滑动条添加事件处理器
  backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
    if (type == ui::Slider::EventType::ON_SLIDEBALL_DOWN)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
    }
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
      const ui::Slider* backgroundMusicVolumnSlider = dynamic_cast<ui::Slider*>(sender);
      const float percent = backgroundMusicVolumnSlider->getPercent();
      g_backgroundMusicVolumn = percent / 100.0f;
      experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
    }
    });
  effectVolumnslider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
    if(type == ui::Slider::EventType::ON_SLIDEBALL_DOWN)
    {
      // 加载点击音效
      audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);
    }
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
      const ui::Slider* effectVolumnslider = dynamic_cast<ui::Slider*>(sender);
      const float percent = effectVolumnslider->getPercent();
      g_soundEffectVolumn = percent / 100.0f;
      experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
    }
    });

  // 将滑动条添加至场景
  this->addChild(backgroundMusicVolumnSlider);
  this->addChild(effectVolumnslider);

  // 创建返回游戏按钮
  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
    "../Resources/BackPressedButton.png",
    "../Resources/BackDefaultButton.png");

  backButton->setScale(0.46f);

  // 设置返回按钮位置
  backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

  // 为返回按钮添加事件处理器
  backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        Director::getInstance()->popScene();
      }
    });

  // 将返回按钮添加到场景中
  this->addChild(backButton);

  return true;
}