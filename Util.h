#pragma once
#include "cocos2d.h"
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
// @ tmxMap   ��Ƭ��ͼ����
// @ position ��Ҫת������������
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction);