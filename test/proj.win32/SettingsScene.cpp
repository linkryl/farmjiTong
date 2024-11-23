#include "SettingsScene.h"
#include "HoverButton.h"
#include "MenuScene.h"
#include "AudioEngine.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

// “Ù∆µ“˝«Ê…Ë÷√
int g_backgroundMusicSign = -1;
int g_soundEffectSign = -1;
float g_backgroundMusicVolumn = 0.5;
float g_soundEffectVolumn = 0.5;

void audioPlayer(const std::string& audioPath, bool isLoop)
{
  if (isLoop) {
    if (g_backgroundMusicSign != -1) {
      experimental::AudioEngine::stop(g_backgroundMusicSign);
    }
    g_backgroundMusicSign = experimental::AudioEngine::play2d(audioPath, isLoop);
    experimental::AudioEngine::setVolume(g_backgroundMusicSign, g_backgroundMusicVolumn);
  }
  else {
    g_soundEffectSign = experimental::AudioEngine::play2d(audioPath, isLoop);
    experimental::AudioEngine::setVolume(g_soundEffectSign, g_soundEffectVolumn);
  }
}