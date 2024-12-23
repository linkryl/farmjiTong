#include "SettingsScene.h"
#include "HoverButton.h"
#include "MenuScene.h"
#include "constant.h"
#include "AudioEngine.h"

USING_NS_CC;

// ��Ƶ��������
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
  // ��������
  if (!Scene::init())
  {
    return false;
  }

  // ��������
  audioPlayer("../Resources/Music/stardew.mp3", true);

  // ���ر���
  const auto screenSize = Director::getInstance()->getVisibleSize();
  const auto background = Sprite::create("../Resources/SettingsScene.png");
  background->setScale(1.5f);
  background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
  this->addChild(background);

  // ����������
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

  // Ϊ����������¼�������
  backgroundMusicVolumnSlider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
    if (type == ui::Slider::EventType::ON_SLIDEBALL_DOWN)
    {
      // ���ص����Ч
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
      // ���ص����Ч
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

  // �����������������
  this->addChild(backgroundMusicVolumnSlider);
  this->addChild(effectVolumnslider);

  // ����������Ϸ��ť
  auto backButton = HoverButton::create("../Resources/BackDefaultButton.png",
    "../Resources/BackPressedButton.png",
    "../Resources/BackDefaultButton.png");

  backButton->setScale(0.46f);

  // ���÷��ذ�ťλ��
  backButton->setPosition(Vec2(screenSize.width / 2 + 565, screenSize.height / 2 - 327));

  // Ϊ���ذ�ť����¼�������
  backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
    {
      if (type == ui::Widget::TouchEventType::ENDED)
      {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        Director::getInstance()->popScene();
      }
    });

  // �����ذ�ť��ӵ�������
  this->addChild(backButton);

  return true;
}