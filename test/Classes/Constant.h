#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <map>
#include <string>

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                               // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                               // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                         // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = "��¶������ Stardew Valley";// Ӧ�ó������
constexpr int DEFAULT_MUSIC_SIGN = -1;                                      // ȱʡ���ֱ�ʶ
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                // ȱʡ������С

// �������ű���
constexpr double GAME_SCALE = 2;

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
constexpr int FARM_TO_TOWN_INIT_X = 0;
constexpr int FARM_TO_TOWN_INIT_Y = (65 - 9);

// ũ����ɽ����ʼ��Ƭ����
constexpr int FARM_TO_MOUNTAIN_INIT_X = 0;
constexpr int FARM_TO_MOUNTAIN_INIT_Y = (41 - 13);

// ũ������Ѩ��ʼ��Ƭ����
constexpr int FARM_TO_CAVE_INIT_X = 44;
constexpr int FARM_TO_CAVE_INIT_Y = (65 - 52);

// ũ����ɭ�ֳ�ʼ��Ƭ����
constexpr int FARM_TO_WOODS_INIT_X = 67;
constexpr int FARM_TO_WOODS_INIT_Y = (65 - 29);

// ũ����С���ڳ�ʼ��Ƭ����
constexpr int FARM_TO_HOUSE_INIT_X = 34;
constexpr int FARM_TO_HOUSE_INIT_Y = (60 - 34);

// С��ص�ũ����ʼ��Ƭ����
constexpr int TOWN_TO_FARM_INIT_X = 79;
constexpr int TOWN_TO_FARM_INIT_Y = (65 - 17);

// ɽ���ص�ũ����ʼ��Ƭ����
constexpr int MOUNTAIN_TO_FARM_INIT_X = 41;
constexpr int MOUNTAIN_TO_FARM_INIT_Y = (65 - 1);

// ��Ѩ�ص�ũ����ʼ��Ƭ����
constexpr int CAVE_TO_FARM_INIT_X = 22;
constexpr int CAVE_TO_FARM_INIT_Y = (65 - 7);

// ɭ�ֻص�ũ����ʼ��Ƭ����
constexpr int WOODS_TO_FARM_INIT_X = 40;
constexpr int WOODS_TO_FARM_INIT_Y = (65 - 64);

// ɭ�ֻص�ũ����ʼ��Ƭ����
constexpr int HOUSE_TO_DEAL_INIT_X = 28;
constexpr int HOUSE_TO_DEAL_INIT_Y = (60 - 29);

// ��Ʒ��ӦID
// �ջ�ķ����
constexpr int PARSNIP_ITEM = 1120;
// ���������
constexpr int PARSNIP_PLANT = 1110;
// ���������
constexpr int PARSNIP_SEED = 1100;
// �ջ��С��
constexpr int WHEAT_ITEM = 1121;
// С������
constexpr int WHEAT_PLANT = 1111;
// С������
constexpr int WHEAT_SEED = 1101;
// ����
constexpr int PIG_ITEM = 2120;
// ������
constexpr int PIG_PLANT = 2110;
// ����
constexpr int PIG_SEED = 2100;
constexpr int FOOD = 1102;

#endif // !_CONSTANT_H_