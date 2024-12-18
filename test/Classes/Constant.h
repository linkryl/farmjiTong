#pragma once

// �������ű���
constexpr double GAME_SCALE = 1.89;

// ��һ����ƶ�����
constexpr int BASE_MOVE_DISTANCE = 60 * 3;

// ���½ǿ�ʼ������ũ������½���Ƭ����
constexpr int FARM_OFFSET_X = 18;
constexpr int FARM_OFFSET_Y = (65 - 26);

// ��������Ƭ����
constexpr int LIVE_FARM_OFFSET_X = 12;
constexpr int LIVE_FARM_OFFSET_Y = (65 - 43);

// �ҵ���Ƭ����(ũ����ʼ��Ƭ����)
constexpr int HOME_X = 52;
constexpr int HOME_Y = (65 - 27);

// ũ����С���ʼ��Ƭ����
constexpr int FARM_TO_TOWN_INIT_X = 1;
constexpr int FARM_TO_TOWN_INIT_Y = 1;

// ũ����ɽ����ʼ��Ƭ����
constexpr int FARM_TO_MOUNTAIN_INIT_X = 1;
constexpr int FARM_TO_MOUNTAIN_INIT_Y = 1;

// ũ������Ѩ��ʼ��Ƭ����
constexpr int FARM_TO_CAVE_INIT_X = 1;
constexpr int FARM_TO_CAVE_INIT_Y = 1;

// ũ����ɭ�ֳ�ʼ��Ƭ����
constexpr int FARM_TO_WOODS_INIT_X = 1;
constexpr int FARM_TO_WOODS_INIT_Y = 1;

// С��ص�ũ����ʼ��Ƭ����
constexpr int TOWN_TO_FARM_INIT_X = 1;
constexpr int TOWN_TO_FARM_INIT_Y = 1;

// ɽ���ص�ũ����ʼ��Ƭ����
constexpr int MOUNTAIN_TO_FARM_INIT_X = 1;
constexpr int MOUNTAIN_TO_FARM_INIT_Y = 1;

// ��Ѩ�ص�ũ����ʼ��Ƭ����
constexpr int CAVE_TO_FARM_INIT_X = 1;
constexpr int CAVE_TO_FARM_INIT_Y = 1;

// ɭ�ֻص�ũ����ʼ��Ƭ����
constexpr int WOODS_TO_FARM_INIT_X = 1;
constexpr int WOODS_TO_FARM_INIT_Y = 1;