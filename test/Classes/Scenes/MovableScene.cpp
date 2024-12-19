#include "MovableScene.h"
#include "MotionManager.h"
#include "Constant.h"


void MovableScene::go(Direction direction) {

    // һ��6֡
    const int upper_limit = 6;
    // ÿһ֡�����ļ��
    const float frameGap = 0.2;

    int originDistance = getPlayer()->getSpeed() * BASE_MOVE_DISTANCE, distance = originDistance;

    for (int i = 1; i <= originDistance; ++i) {
        
        Vec2 pos = modifyVec2(Vec2(PLAYER_POSITION), direction, i);
        if (!canMove(getTiledMap(), pos, direction, true, i)) {
            distance = i - 1;
            break;
        }
    }

    Vec2 moveVec2 = generateVec2(opposite(direction), distance * GAME_SCALE);
    auto moveAction = MoveBy::create(upper_limit * frameGap * distance / originDistance, moveVec2);

    const size_t hash_value = direction;
    moveAction->setTag(hash_value);
    // ���if������֤�˶���������ж�������;�����
    if (this->_actionManager->getActionByTag(hash_value, this) == nullptr)
    {
        // UP�ǵ�һ��ö���࣬LEFT�����һ��
        for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
            // �����������Ķ���
            if (i != direction)
                this->stopActionByTag(i - direction + hash_value);
        this->runAction(moveAction);
    }
}

void MovableScene::moveUpdate(MotionManager* information) {

    auto left = EventKeyboard::KeyCode::KEY_A;
    auto right = EventKeyboard::KeyCode::KEY_D;
    auto up = EventKeyboard::KeyCode::KEY_W;
    auto down = EventKeyboard::KeyCode::KEY_S;

    auto& keyMap = information->keyMap;
    bool flag = keyMap[left] || keyMap[right] || keyMap[down] || keyMap[up];

    Direction direction;
    if (information->keyMap[left]) {
        direction = LEFT;
    }
    else if (information->keyMap[right]) {
        direction = RIGHT;
    }
    else if (information->keyMap[down]) {
        direction = DOWN;
    }
    else if (information->keyMap[up]) {
        direction = UP;
    }

    if (flag) {
        // ����̽�Ƿ���ƶ�
        if (!canMove(this->getTiledMap(), PLAYER_POSITION, direction, true)) return;
        this->go(direction);
    }
}

// ������(x, y)Ϊ���ĵ�ĳ�����������
// x, y Ϊ��������
Vec2 MovableScene::getMiddlePosition(double x, double y) {

    Size mapSize = getTiledMap()->getMapSize();
    Size tileSize = getTiledMap()->getTileSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    double halfWindowWidth = visibleSize.width / 2.0;
    double halfWindowHeight = visibleSize.height / 2.0;

    double sceneFixedWidth = visibleSize.width / 2.0 / GAME_SCALE;
    double sceneFixedHeight = visibleSize.height / 2.0 / GAME_SCALE;

    double mapWidth = 1.0 * mapSize.width * tileSize.width;
    double mapHeight = 1.0 * mapSize.height * tileSize.height;

    double posX = x * GAME_SCALE - halfWindowWidth;
    double posY = y * GAME_SCALE - halfWindowHeight;

    CCLOG("posX: %2.f, posY: %2.f", posX, posY);

    // �ڱ�Եλ����������
    return getCorrectionPosition(Vec2(-posX, -posY));
}

Vec2 MovableScene::getMiddlePosition(Vec2 position) {
    return getMiddlePosition(position.x, position.y);
}

Vec2 MovableScene::getCorrectionPosition(Vec2 position) {
    Size mapSize = getTiledMap()->getMapSize();
    Size tileSize = getTiledMap()->getTileSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    double mapWidth = 1.0 * mapSize.width * tileSize.width;
    double mapHeight = 1.0 * mapSize.height * tileSize.height;
    double posX = position.x;
    double posY = position.y;

    // �ڱ�Եλ����������
    if (posX + eps <= visibleSize.width - mapWidth * GAME_SCALE) {

        posX = visibleSize.width - mapWidth * GAME_SCALE;
    }
    else if (posX - eps >= 0) {

        posX = 0;
    }
    if (posY + eps <= visibleSize.height - mapHeight * GAME_SCALE) {

        posY = visibleSize.height - mapHeight * GAME_SCALE;
    }
    else if (posY - eps >= 0) {

        posY = 0;
    }
    return Vec2(posX, posY);
}

void MovableScene::returnMiddlePosition() {
    setPosition(getCorrectionPosition(getPosition()));
}