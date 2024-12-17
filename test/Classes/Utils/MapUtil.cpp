#include "cocos2d.h"
#include "MapUtil.h"

// 像素坐标转瓦片坐标
// 
// @ tmxMap   瓦片地图对象
// @ position 需要转换的像素坐标
Vec2 convertToTileCoord(TMXTiledMap* tmxMap, const Vec2& position) {

    // 获取地图的尺寸和瓦片尺寸
    Size mapSize = tmxMap->getMapSize();
    Size tileSize = tmxMap->getTileSize();

    // 计算瓦片坐标
    float x = static_cast<int>(position.x / tileSize.width);
    float y = static_cast<int>((tmxMap->getContentSize().height - position.y) / tileSize.height);

    // 返回瓦片坐标
    return Vec2(x, y);
}

// 像素坐标转瓦片坐标
// 
// 默认为16x16 size格子.
// 
// @ x     像素x坐标
// @ y     像素y坐标
// @ xSize  瓦片的尺寸
// @ ySize  瓦片的尺寸
std::pair<int, int> convertToTileCoord(const int x, const int y, const int xSize, const int ySize) {
    auto height = Director::getInstance()->getVisibleSize().height;
    return std::pair<int, int>(x / xSize, (height - y) / ySize);
}

// 判断该位置按该方向是否可移动
// 
// @ tmxMap    瓦片地图对象
// @ position  需要转换的像素坐标
// @ direction 移动方向
bool can_move(TMXTiledMap* tmxMap, const Vec2 position, Direction direction) {
    if (!static_cast<bool>(tmxMap)) {
        CCLOG("null map");
        return false;
    }
    // 获取地图的尺寸和瓦片尺寸
    Size mapSize = tmxMap->getMapSize();
    Size tileSize = tmxMap->getTileSize();

    int width = static_cast<int>(mapSize.width);
    int height = static_cast<int>(mapSize.height);

    // 计算下一刻要到达的位置的坐标
    Vec2 toPos = position;
    if (direction == UP) {
        toPos.y += 1 + COLLISION_BOX_SIZE;
    }
    else if (direction == DOWN) {
        toPos.y -= 1 + COLLISION_BOX_SIZE;
    }
    else if (direction == LEFT) {
        toPos.x -= 1 + COLLISION_BOX_SIZE;
    }
    else if (direction == RIGHT) {
        toPos.x += 1 + COLLISION_BOX_SIZE;
    }
    // 若超出地图边界，直接返回
    if (toPos.x + eps <= 0 || toPos.y + eps <= 0
        || toPos.x - eps >= mapSize.width * tileSize.width
        || toPos.y - eps >= mapSize.height * tileSize.width)
    {
        CCLOG("out of border");
        return false;
    }

    // 获取下一步要到达的位置对应的瓦片坐标
    Vec2 tilePos = convertToTileCoord(tmxMap, toPos);

    // 获取地图Buildings层
    auto layer = tmxMap->getLayer("Buildings");
    if (nullptr == layer) {
        CCLOG("Buildings layer not found");
        return false;
    }
    int id = layer->getTileGIDAt(tilePos);
    
    // id为0则代表为可移动，否则不可移动
    //CCLOG("%d", id);
    return static_cast<bool>(!id);
}

// 通过方向和距离生成Vec2向量
// 
// @ direction 移动方向
// @ distance 距离
Vec2 generateVec2(Direction direction, int distance) {
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

// Vec2向量相加，返回新向量
// 
// @ vec1  操作向量1
// @ vec2  操作向量2
Vec2 addVec2(Vec2 vec1, Vec2 vec2) {
    return Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
}

// 通过方向和距离增量修改Vec2向量
// 
// @ vec 需要修改的向量
// @ direction 移动方向
// @ distance 距离
Vec2 modifyVec2(Vec2 vec, Direction direction, int distance) {
    return addVec2(vec, generateVec2(direction, distance));
}