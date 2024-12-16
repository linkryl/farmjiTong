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
const std::string APPLICATION_TITLE = u8"��¶������ Stardew Valley";// Ӧ�ó������
constexpr int DEFAULT_MUSIC_SIGN = -1;                                      // ȱʡ���ֱ�ʶ
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                // ȱʡ������С

#endif // !_CONSTANT_H_