#pragma once

enum Direction { UP, RIGHT, DOWN, LEFT };
enum Motion { GO, LIGHT_HIT, HEAVY_HIT, STAND };
enum Part_catogory { HUMAN, TOOL, WEAPON, WEARING };

constexpr int COLLISION_BOX_SIZE = 8;