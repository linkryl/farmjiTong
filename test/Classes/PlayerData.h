#pragma once
#define opposite(x) static_cast<Direction>((x + 2) % 4)
#define PLAYER_POSITION getPlayer()->get_parts().at(0)->getPosition()

enum Direction { UP, RIGHT, DOWN, LEFT };
enum Motion { GO, LIGHT_HIT, HEAVY_HIT, STAND };
enum Part_catogory { HUMAN, TOOL, WEAPON, WEARING, SHADOW };

// 碰撞箱尺寸，单位为像素
constexpr int COLLISION_BOX_SIZE = 8;

// 保存跟随地图切换需要维护的信息
struct PlayerInfo {
	// 玩家初始化时所在的瓦片坐标
	int tileX, tileY;
	// 玩家初始化时面向方向
	Direction faceTo;
};