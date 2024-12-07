#pragma once
#include "cocos2d.h"
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
// @ tmxMap   瓦片地图对象
// @ position 需要转换的像素坐标
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction);