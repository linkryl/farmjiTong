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

// 判断该位置按该方向是否可移动
// 
// @ tmxMap    瓦片地图对象
// @ position  需要转换的像素坐标
// @ direction 移动方向
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction);

// 通过方向和距离生成Vec2向量
// 
// @ direction 移动方向
// @ distance 距离
Vec2 generateVec2(Direction direction, int distance);

// 通过方向和距离增量修改Vec2向量
// 
// @ vec 需要修改的向量
// @ direction 移动方向
// @ distance 距离
Vec2 modifyVec2(Vec2 vec, Direction direction, int distance);