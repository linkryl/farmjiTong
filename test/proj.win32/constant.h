#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                               // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                               // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                         // 应用程序帧率
const std::string APPLICATION_TITLE = u8"星露谷物语 Stardew Valley";// 应用程序标题

// 颜色设置
constexpr int DARK_BLUE_R = 0;                                              // 深蓝色 R 通道
constexpr int DARK_BLUE_G = 32;                                             // 深蓝色 G 通道
constexpr int DARK_BLUE_B = 96;                                             // 深蓝色 B 通道
constexpr int GOLDEN_R = 223;                                               // 金黄色 R 通道
constexpr int GOLDEN_G = 176;                                               // 金黄色 G 通道
constexpr int GOLDEN_B = 11;                                                // 金黄色 B 通道

// 启动场景设置
constexpr int STARTUP_SCENE_FONT_SIZE = 20;                                 // 启动场景字体大小
constexpr int STARTUP_SCENE_LOADINGBAR_OFFSET_Y = -241;                     // 启动场景加载进度条位置 Y 偏移量
constexpr int STARTUP_SCENE_LOADING_LABEL_OFFSET_X = -30;                   // 启动场景加载进度条标签位置 X 偏移量
constexpr float STARTUP_SCENE_DURATION = 2.0f;                              // 启动场景加载时间
constexpr float SCENE_TRANSITION_DURATION = 0.3f;

#endif // !_CONSTANT_H_