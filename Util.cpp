#include "cocos2d.h"
#include "Util.h"

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

// 判断该位置按该方向是否可移动
// 
// @ tmxMap   瓦片地图对象
// @ position 需要转换的像素坐标
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
        toPos.y += 1;
    }
    else if (direction == DOWN) {
        toPos.y -= 1;
    }
    else if (direction == LEFT) {
        toPos.x -= 1;
    }
    else if (direction == RIGHT) {
        toPos.x += 1;
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
    CCLOG("%d", id);
    return static_cast<bool>(!id);
}