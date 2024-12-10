#include "Player.h"
#include <functional>

void PlayerPart::go(const Direction direction, const Part_catogory catogory)
{
    // 基准速度
    double base_speed = 60;
    // 一共6帧
    const int upper_limit = 6;
    // 每一帧动画的间隔
    const float frameGap = 0.2;
    int originDistance = speed * base_speed, distance = originDistance;
    for (int i = 1; i <= originDistance; ++i) {
        Vec2 pos = modifyVec2(Vec2(getPosition()), direction, i);
        if (!can_move(getPlayer()->getTiledMap(), pos, direction)) {
            distance = i - 1;
            break;
        }
    }
    // 动作
    Vec2 moveVec2 = generateVec2(direction, distance);
    auto moveAction = MoveBy::create(upper_limit * frameGap * distance / originDistance, moveVec2);
    // 数字映射到string
    std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
    if (catogory == HUMAN)
    {
        // 动画
        // 动画帧序列map
        //static std::map<std::string, Vector<SpriteFrame*>> spriteFramesMap;
        Vector<SpriteFrame*> spriteFrames;
        auto direct = numToString[direction];
        auto path = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + ".plist";
        SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
        for (int i = 0; i < upper_limit; i++)
        {
            std::string direct = numToString[direction];
            std::string index = std::to_string(i);
            auto imageName = part_name + "_" + direct + "_" + index + ".png";
            auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
            //auto frame = SpriteFrame::create(path, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
            /*if (spriteFramesMap.find(direct) != spriteFramesMap.end() && spriteFramesMap[direct].empty())
                spriteFramesMap[direct].pushBack(frame);*/
            spriteFrames.pushBack(frame);
        }
        ////////*Something goes wrong here*/
        Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
        Animate* animate = Animate::create(ani);
        ///////////////

        // 动作并行Spawn
        auto moveSpawn = Spawn::createWithTwoActions(moveAction, animate);

        const size_t hash_value = partNameHash[part_name] + direction + hashValue[GO];
        moveSpawn->setTag(hash_value);
        // 这个if条件保证了动作连贯进行而不是中途被打断
        const auto sign = this->_actionManager->getActionByTag(hash_value, this);
        if (this->_actionManager->getActionByTag(hash_value, this) == nullptr)
        {
            // UP是第一个枚举类，LEFT是最后一个
            for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
                // 打断其他方向的动作
                if (i != direction)
                    this->stopActionByTag(i - direction + hash_value);
            this->runAction(moveSpawn);
        }
    }
    else if (catogory == TOOL || catogory == WEAPON)
    {
        const size_t hash_value = partNameHash[part_name] + direction + hashValue[GO];
        moveAction->setTag(hash_value);
        // 这个if条件保证了动作连贯进行而不是中途被打断
        const auto sign = this->_actionManager->getActionByTag(hash_value, this);
        if (this->_actionManager->getActionByTag(hash_value, this) == nullptr)
        {
            // UP是第一个枚举类，LEFT是最后一个
            for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
                // 打断其他方向的动作
                if (i != direction)
                    this->stopActionByTag(i - direction + hash_value);
            this->runAction(moveAction);
        }
    }
}

void PlayerPart::stand(const Direction direction)
{
    // 数字映射到string
    std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
    auto direct = numToString[direction];
    auto imagePath = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + "_5.png";
    this->stopAllActions();
    this->setTexture(imagePath);
}

void PlayerPart::light_hit(const Direction direction)
{
    // 一共6帧
    const int upper_limit = 6;
    // 每一帧动画的间隔
    const float frameGap = 0.05;
    // 数字映射到string
    std::map<int, std::string> numToString = { {UP,"light_hit_up"}, {RIGHT, "light_hit_right"}, {LEFT, "light_hit_left"}, {DOWN, "light_hit_down"} };
    // 动画
    Vector<SpriteFrame*> spriteFrames;
    auto direct = numToString[direction];
    auto path = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + ".plist";
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
    for (int i = 0; i < upper_limit; i++)
    {
        std::string direct = numToString[direction];
        std::string index = std::to_string(i);
        auto imageName = part_name + "_" + direct + "_" + index + ".png";
        auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
        spriteFrames.pushBack(frame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
    Animate* animate = Animate::create(ani);

    const size_t hash_value = hashValue[LIGHT_HIT];
    // const size_t hash_value = hasher(part_name) + direction + hashValue[LIGHT_HIT];
    animate->setTag(partNameHash[part_name] + direction + hash_value);
    // 这个if条件保证了动作连贯进行而不是中途被打断
    const auto sign = this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this);
    if (this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this) == nullptr)
    {
        // UP是第一个枚举类，LEFT是最后一个
        for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
            // 打断其他方向的动作
            for (const auto& item : hashValue)
            {
                int val = item.second;
                if (val != hash_value || i != direction)
                {
                    int partHash = partNameHash[part_name];
                    int temp = i + partNameHash[part_name] + val;
                    //this->stopActionByTag(i - direction + hash_value);
                    this->stopActionByTag(i + partNameHash[part_name] + val);
                }
            }
        this->runAction(animate);
    }
}

void PlayerPart::heavy_hit(const Direction direction)
{
    // 一共6帧
    const int upper_limit = 6;
    // 每一帧动画的间隔
    const float frameGap = 0.10;
    // 数字映射到string
    std::map<int, std::string> numToString = { {UP,"heavy_hit_up"}, {RIGHT, "heavy_hit_right"}, {LEFT, "heavy_hit_left"}, {DOWN, "heavy_hit_down"} };
    // 动画
    Vector<SpriteFrame*> spriteFrames;
    auto direct = numToString[direction];
    auto path = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + ".plist";
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
    for (int i = 0; i < upper_limit; i++)
    {
        std::string direct = numToString[direction];
        std::string index = std::to_string(i);
        auto imageName = part_name + "_" + direct + "_" + index + ".png";
        auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
        spriteFrames.pushBack(frame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
    Animate* animate = Animate::create(ani);

    const size_t hash_value = hashValue[HEAVY_HIT];
    // const size_t hash_value = hasher(part_name) + direction + hashValue[LIGHT_HIT];
    animate->setTag(partNameHash[part_name] + direction + hash_value);
    // 这个if条件保证了动作连贯进行而不是中途被打断
    const auto sign = this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this);
    if (this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this) == nullptr)
    {
        // UP是第一个枚举类，LEFT是最后一个
        for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
            // 打断其他方向的动作
            for (const auto& item : hashValue)
            {
                int val = item.second;
                if (val != hash_value || i != direction)
                {
                    int partHash = partNameHash[part_name];
                    int temp = i + partNameHash[part_name] + val;
                    //this->stopActionByTag(i - direction + hash_value);
                    this->stopActionByTag(i + partNameHash[part_name] + val);
                }
            }
        this->runAction(animate);
    }
}

PlayerPart* PlayerPart::create(const std::string& path, const std::string& part_name)
{
    PlayerPart* playerPart = new PlayerPart(part_name);
    if (playerPart && playerPart->initWithFile(path))
    {
        playerPart->autorelease();
        return playerPart;
    }
    CC_SAFE_DELETE(playerPart);
    return nullptr;
}

void PlayerPart::setPlayer(Player* player)
{
    this->player = player;
}

Player* PlayerPart::getPlayer()
{
    return this->player;
}

void Player::setTiledMap(TMXTiledMap* map)
{
    tmxMap = map;
}

TMXTiledMap* Player::getTiledMap()
{
    return this->tmxMap;
}

void Player::add_part(const std::string& path, const std::string& part_name)
{
    auto part = PlayerPart::create(path, part_name);
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 0));
    parts.pushBack(part);
}

void Player::add_tool(const std::string& path, const std::string& tool_name)
{
    auto part = PlayerPart::create(path, tool_name);
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 1.0 / 3));
    tools.pushBack(part);
    //tools.pushBack(PlayerPart::create(path, tool_name));
}

void Player::add_weapon(const std::string& path, const std::string& weapon_name)
{
    auto part = PlayerPart::create(path, weapon_name);
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 1.0 / 3));
    weapons.pushBack(part);
}

void Player::go(Direction direction)
{
    faceTo = direction;
    PLAYER_TRAVELSAL(part)
    {
        part->go(direction);
    }
    TOOL_TRAVELSAL(tool)
    {
        tool->go(direction, TOOL);
    }
    WEAPON_TRAVELSAL(weapon)
    {
        weapon->go(direction, WEAPON);
    }
}

void Player::heavy_hit()
{
    PLAYER_TRAVELSAL(part)
    {
        part->heavy_hit(faceTo);
    }
    TOOL_TRAVELSAL(tool)
    {
        // 工具向上砍不好做，干脆不要了
        if (faceTo != UP)
            tool->heavy_hit(faceTo);
    }
}

void Player::light_hit()
{
    PLAYER_TRAVELSAL(part)
    {
        part->light_hit(faceTo);
    }
    WEAPON_TRAVELSAL(weapon)
    {
        // 还是一样的，向上砍的动作不好做
        if (faceTo != UP)
            weapon->light_hit(faceTo);
    }
}

void Player::stand()
{
    PLAYER_TRAVELSAL(part)
    {
        part->stand(faceTo);
    }
    TOOL_TRAVELSAL(tool)
    {
        tool->stand(faceTo);
    }
    WEAPON_TRAVELSAL(weapon)
    {
        weapon->stand(faceTo);
    }
}

void Player::setPosition(const Vec2& vec)
{
    Node::setPosition(vec);
    PLAYER_TRAVELSAL(part)
    {
        part->setPosition(vec);
    }
    TOOL_TRAVELSAL(tool)
    {
        tool->setPosition(vec);
    }
    WEAPON_TRAVELSAL(weapon)
    {
        weapon->setPosition(vec);
    }
}

void Player::setScale(const float scale)
{
    PLAYER_TRAVELSAL(part)
    {
        part->setScale(scale);
    }
    TOOL_TRAVELSAL(tool)
    {
        tool->setScale(scale);
    }
    WEAPON_TRAVELSAL(weapon)
    {
        weapon->setScale(scale);
    }
}

Vector<PlayerPart*> Player::get_parts()
{
    return parts;
}

Vector<PlayerPart*> Player::get_tools()
{
    return tools;
}

Vector<PlayerPart*> Player::get_weapons()
{
    return weapons;
}

Player* Player::create()
{
    Player* player = new Player();
    if (player)
    {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}