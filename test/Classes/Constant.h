#pragma once

// 整体缩放比例
constexpr double GAME_SCALE = 1.89;

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
constexpr int FARM_TO_TOWN_INIT_X = 1;
constexpr int FARM_TO_TOWN_INIT_Y = 1;

// 农场到山脉初始瓦片坐标
constexpr int FARM_TO_MOUNTAIN_INIT_X = 1;
constexpr int FARM_TO_MOUNTAIN_INIT_Y = 1;

// 农场到洞穴初始瓦片坐标
constexpr int FARM_TO_CAVE_INIT_X = 1;
constexpr int FARM_TO_CAVE_INIT_Y = 1;

// 农场到森林初始瓦片坐标
constexpr int FARM_TO_WOODS_INIT_X = 1;
constexpr int FARM_TO_WOODS_INIT_Y = 1;

// 小镇回到农场初始瓦片坐标
constexpr int TOWN_TO_FARM_INIT_X = 1;
constexpr int TOWN_TO_FARM_INIT_Y = 1;

// 山脉回到农场初始瓦片坐标
constexpr int MOUNTAIN_TO_FARM_INIT_X = 1;
constexpr int MOUNTAIN_TO_FARM_INIT_Y = 1;

// 洞穴回到农场初始瓦片坐标
constexpr int CAVE_TO_FARM_INIT_X = 1;
constexpr int CAVE_TO_FARM_INIT_Y = 1;

// 森林回到农场初始瓦片坐标
constexpr int WOODS_TO_FARM_INIT_X = 1;
constexpr int WOODS_TO_FARM_INIT_Y = 1;