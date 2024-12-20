#include "cocos2d.h"
#include "MapUtil.h"
#include "Constant.h"

// ��������ת��Ƭ����
// 
// @ tmxMap   ��Ƭ��ͼ����
// @ position ��Ҫת������������
Vec2 convertToTileCoord(TMXTiledMap* tmxMap, const Vec2& position) {

    // ��ȡ��ͼ�ĳߴ����Ƭ�ߴ�
    Size mapSize = tmxMap->getMapSize();
    Size tileSize = tmxMap->getTileSize();

    // ������Ƭ����
    float x = static_cast<int>(position.x / tileSize.width);
    float y = static_cast<int>((tmxMap->getContentSize().height - position.y) / tileSize.height);

    // ������Ƭ����
    return Vec2(x, y);
}

// ��������ת��Ƭ����
// 
// Ĭ��Ϊ16x16 size����.
// 
// @ x     ����x����
// @ y     ����y����
// @ xSize  ��Ƭ�ĳߴ�
// @ ySize  ��Ƭ�ĳߴ�
std::pair<int, int> convertToTileCoord(const int x, const int y, const int xSize, const int ySize) {
    auto height = Director::getInstance()->getVisibleSize().height;
    return std::pair<int, int>(x / xSize, (height - y) / ySize);
}

// ��������ת��Ƭ����
// 
// @ x     ��Ƭx����
// @ y     ��Ƭy����
Vec2 tileCoordToPixel(int x, int y) {
    return Vec2(x * 16 + 8, y * 16 - 8);
}

// �жϸ�λ�ð��÷����Ƿ���ƶ�
// 
// @ tmxMap    ��Ƭ��ͼ����
// @ position  ��Ҫת������������
// @ direction �ƶ�����
// @ isScene   �����Ƿ�ΪMovableScene�������
bool canMove(TMXTiledMap* tmxMap, const Vec2 position, Direction direction, bool isScene, int moveDistance) {
    if (!static_cast<bool>(tmxMap)) {
        CCLOG("oh no null map");
        return false;
    }

    static int cnt = 0;

    // ��ȡ��ͼ�ĳߴ����Ƭ�ߴ�
    Size mapSize = tmxMap->getMapSize();
    Size tileSize = tmxMap->getTileSize();

    if (isScene) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        double sceneFixedWidth = visibleSize.width / 2.0 / GAME_SCALE + COLLISION_BOX_SIZE * 0;
        double sceneFixedHeight = visibleSize.height / 2.0 / GAME_SCALE + COLLISION_BOX_SIZE * 0;

        double mapWidth = 1.0 * mapSize.width * tileSize.width;
        double mapHeight = 1.0 * mapSize.height * tileSize.height;

        Vec2 toPos = modifyVec2(position, direction, 1);
        if ((direction == LEFT || direction == RIGHT) && (toPos.x + eps <= sceneFixedWidth || toPos.x - eps >= mapWidth - sceneFixedWidth)) {
            return false;
        }
        if ((direction == UP || direction == DOWN) && (toPos.y + eps <= sceneFixedHeight || toPos.y - eps >= mapHeight - sceneFixedHeight)) {
            return false;
        }
    }
    // ������һ��Ҫ�����λ�õ�����
    Vec2 toPos = modifyVec2(position, direction, 1 + COLLISION_BOX_SIZE);

    // ��������ͼ�߽磬ֱ�ӷ���
    if (toPos.x + eps <= 0 || toPos.y + eps <= 0
        || toPos.x - eps >= mapSize.width * tileSize.width
        || toPos.y - eps >= mapSize.height * tileSize.width)
    {
        //CCLOG("out of border");
        return false;
    }

    // ��ȡ��һ��Ҫ�����λ�ö�Ӧ����Ƭ����
    Vec2 tilePos = convertToTileCoord(tmxMap, toPos);
    if (tilePos.x <= -1 || tilePos.x >= mapSize.width || tilePos.y <= -1 || tilePos.y >= mapSize.height) {
        return false;
    }

    // ��ȡ��ͼBuildings��
    auto layer = tmxMap->getLayer("Buildings");
    if (nullptr == layer) {
        //CCLOG("Buildings layer not found");
        return false;
    }
    int id = layer->getTileGIDAt(tilePos);
    
    // idΪ0�����Ϊ���ƶ������򲻿��ƶ�
    return static_cast<bool>(!id);
}

// ͨ������;�������Vec2����
// 
// @ direction �ƶ�����
// @ distance ����
Vec2 generateVec2(Direction direction, double distance) {
    Vec2 pos;
    if (direction == UP) {
        pos.y = distance;
    }
    else if (direction == DOWN) {
        pos.y = -distance;
    }
    else if (direction == LEFT) {
        pos.x = -distance;
    }
    else if (direction == RIGHT) {
        pos.x = distance;
    }
    return pos;
}

// Vec2������ӣ�����������
// 
// @ vec1  ��������1
// @ vec2  ��������2
Vec2 addVec2(Vec2 vec1, Vec2 vec2) {
    return Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
}

// ͨ������;��������޸�Vec2����
// 
// @ vec ��Ҫ�޸ĵ�����
// @ direction �ƶ�����
// @ distance ����
Vec2 modifyVec2(Vec2 vec, Direction direction, double distance) {
    return addVec2(vec, generateVec2(direction, distance));
}