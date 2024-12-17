#pragma once

#include "cocos2d.h"
#include "PlayerData.h"
#include "Player.h"

USING_NS_CC;

constexpr double eps = 1e-7;

// ��������ת��Ƭ����
// 
// @ tmxMap   ��Ƭ��ͼ����
// @ position ��Ҫת������������
Vec2 convertToTileCoord(TMXTiledMap* tmxMap, const Vec2& position);

// ��������ת��Ƭ����
// 
// Ĭ��Ϊ16x16 size����.
// 
// @ x     ����x����
// @ y     ����y����
// @ xSize  ��Ƭ�ĳߴ�
// @ ySize  ��Ƭ�ĳߴ�
std::pair<int, int> convertToTileCoord(const int x, const int y, const int xSize = 16, const int ySize = 16);

// �жϸ�λ�ð��÷����Ƿ���ƶ�
// 
// @ tmxMap    ��Ƭ��ͼ����
// @ position  ��Ҫת������������
// @ direction �ƶ�����
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction);

// ͨ������;�������Vec2����
// 
// @ direction �ƶ�����
// @ distance  ����
Vec2 generateVec2(Direction direction, int distance);

// Vec2������ӣ�����������
// 
// @ vec1  ��������1
// @ vec2  ��������2
Vec2 addVec2(Vec2 vec1, Vec2 vec2);

// ͨ������;��������޸�Vec2����
// 
// @ vec       ��Ҫ�޸ĵ�����
// @ direction �ƶ�����
// @ distance  ����
Vec2 modifyVec2(Vec2 vec, Direction direction, int distance);

