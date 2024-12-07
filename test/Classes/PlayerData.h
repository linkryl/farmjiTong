#pragma once

enum Direction { UP, RIGHT, DOWN, LEFT };
enum Motion { GO, LIGHT_HIT, HEAVY_HIT, STAND };

constexpr int COLLISION_BOX_SIZE = 8;