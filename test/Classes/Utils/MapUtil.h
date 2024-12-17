#pragma once

#include "cocos2d.h"
#include "PlayerData.h"
#include "Player.h"

USING_NS_CC;

constexpr double eps = 1e-7;

// 像素坐标转瓦片坐标
// 
// @ tmxMap   瓦片地图对象
// @ position 需要转换的像素坐标
Vec2 convertToTileCoord(TMXTiledMap* tmxMap, const Vec2& position);

// 像素坐标转瓦片坐标
// 
// 默认为16x16 size格子.
// 
// @ x     像素x坐标
// @ y     像素y坐标
// @ xSize  瓦片的尺寸
// @ ySize  瓦片的尺寸
std::pair<int, int> convertToTileCoord(const int x, const int y, const int xSize = 16, const int ySize = 16);

// 判断该位置按该方向是否可移动
// 
// @ tmxMap    瓦片地图对象
// @ position  需要转换的像素坐标
// @ direction 移动方向
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction);

// 通过方向和距离生成Vec2向量
// 
// @ direction 移动方向
// @ distance  距离
Vec2 generateVec2(Direction direction, int distance);

// Vec2向量相加，返回新向量
// 
// @ vec1  操作向量1
// @ vec2  操作向量2
Vec2 addVec2(Vec2 vec1, Vec2 vec2);

// 通过方向和距离增量修改Vec2向量
// 
// @ vec       需要修改的向量
// @ direction 移动方向
// @ distance  距离
Vec2 modifyVec2(Vec2 vec, Direction direction, int distance);

