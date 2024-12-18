#pragma once
#define opposite(x) static_cast<Direction>((x + 2) % 4)
#define PLAYER_POSITION getPlayer()->get_parts().at(0)->getPosition()

enum Direction { UP, RIGHT, DOWN, LEFT };
enum Motion { GO, LIGHT_HIT, HEAVY_HIT, STAND };
enum Part_catogory { HUMAN, TOOL, WEAPON, WEARING, SHADOW };

// ��ײ��ߴ磬��λΪ����
constexpr int COLLISION_BOX_SIZE = 8;

// ��������ͼ�л���Ҫά������Ϣ
struct PlayerInfo {
	// ��ҳ�ʼ��ʱ���ڵ���Ƭ����
	int tileX, tileY;
	// ��ҳ�ʼ��ʱ������
	Direction faceTo;
};