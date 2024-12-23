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
const std::string APPLICATION_TITLE = "星露谷物语 Stardew Valley";// 应用程序标题
constexpr int DEFAULT_MUSIC_SIGN = -1;                                      // 缺省音乐标识
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                // 缺省音量大小

// 整体缩放比例
constexpr double GAME_SCALE = 2;

// 玩家基础移动距离
constexpr int BASE_MOVE_DISTANCE = 60 * 3;

// 左下角开始计数，农田的左下角瓦片坐标
constexpr int FARM_OFFSET_X = 18;
constexpr int FARM_OFFSET_Y = (65 - 26);

// 牧场的瓦片坐标
constexpr int LIVE_FARM_OFFSET_X = 12;
constexpr int LIVE_FARM_OFFSET_Y = (65 - 43);

// 家的瓦片坐标(农场初始瓦片坐标)
constexpr int HOME_X = 52;
constexpr int HOME_Y = (65 - 27);

// 农场到小镇初始瓦片坐标
constexpr int FARM_TO_TOWN_INIT_X = 0;
constexpr int FARM_TO_TOWN_INIT_Y = (65 - 9);

// 农场到山脉初始瓦片坐标
constexpr int FARM_TO_MOUNTAIN_INIT_X = 0;
constexpr int FARM_TO_MOUNTAIN_INIT_Y = (41 - 13);

// 农场到洞穴初始瓦片坐标
constexpr int FARM_TO_CAVE_INIT_X = 44;
constexpr int FARM_TO_CAVE_INIT_Y = (65 - 52);

// 农场到森林初始瓦片坐标
constexpr int FARM_TO_WOODS_INIT_X = 67;
constexpr int FARM_TO_WOODS_INIT_Y = (65 - 29);

// 农场到小屋内初始瓦片坐标
constexpr int FARM_TO_HOUSE_INIT_X = 34;
constexpr int FARM_TO_HOUSE_INIT_Y = (60 - 34);

// 小镇回到农场初始瓦片坐标
constexpr int TOWN_TO_FARM_INIT_X = 79;
constexpr int TOWN_TO_FARM_INIT_Y = (65 - 17);

// 山脉回到农场初始瓦片坐标
constexpr int MOUNTAIN_TO_FARM_INIT_X = 41;
constexpr int MOUNTAIN_TO_FARM_INIT_Y = (65 - 1);

// 洞穴回到农场初始瓦片坐标
constexpr int CAVE_TO_FARM_INIT_X = 22;
constexpr int CAVE_TO_FARM_INIT_Y = (65 - 7);

// 森林回到农场初始瓦片坐标
constexpr int WOODS_TO_FARM_INIT_X = 40;
constexpr int WOODS_TO_FARM_INIT_Y = (65 - 64);

// 森林回到农场初始瓦片坐标
constexpr int HOUSE_TO_DEAL_INIT_X = 28;
constexpr int HOUSE_TO_DEAL_INIT_Y = (60 - 29);

// 物品对应ID
// 收获的防风草
constexpr int PARSNIP_ITEM = 1120;
// 防风草作物
constexpr int PARSNIP_PLANT = 1110;
// 防风草种子
constexpr int PARSNIP_SEED = 1100;
// 收获的小麦
constexpr int WHEAT_ITEM = 1121;
// 小麦作物
constexpr int WHEAT_PLANT = 1111;
// 小麦种子
constexpr int WHEAT_SEED = 1101;
// 猪肉
constexpr int PIG_ITEM = 2120;
// 猪生物
constexpr int PIG_PLANT = 2110;
// 猪仔
constexpr int PIG_SEED = 2100;
constexpr int FOOD = 1102;

#endif // !_CONSTANT_H_