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

// �жϸ�λ�ð��÷����Ƿ���ƶ�
// 
// @ tmxMap    ��Ƭ��ͼ����
// @ position  ��Ҫת������������
// @ direction �ƶ�����
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction);

// ͨ������;�������Vec2����
// 
// @ direction �ƶ�����
// @ distance ����
Vec2 generateVec2(Direction direction, int distance);

// ͨ������;��������޸�Vec2����
// 
// @ vec ��Ҫ�޸ĵ�����
// @ direction �ƶ�����
// @ distance ����
Vec2 modifyVec2(Vec2 vec, Direction direction, int distance);