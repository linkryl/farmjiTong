#include "Player.h"
#include "DialogFrame.h"
#include <functional>

void PlayerPart::go(const Direction direction, const Part_catogory catogory, const int id)
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
    else if (catogory == WEARING)
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
        // 更换方向
        std::string direct = numToString[direction];
        std::string path = "/wearing/" + part_name + "/" + part_name + "_" + std::to_string(id)
            + "/" + part_name + "_" + std::to_string(id) + "_" + direct + ".png";
        this->setTexture(path);
    }
}

void PlayerPart::stand(const Direction direction, const Part_catogory catogory)
{
    if (catogory != WEARING)
    {
        // 数字映射到string
        std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
        auto direct = numToString[direction];
        auto imagePath = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + "_5.png";
        this->stopAllActions();
        this->setTexture(imagePath);
    }
    else
    {
        this->stopAllActions();
    }
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

void Player::add_wearing(const std::string& path, const std::string& wearing_name, const int id)
{
    // 更改对应衣服的编号
    wearingId[wearing_name] = id;
    std::string real_path = path + "/" + wearing_name + "_" + std::to_string(id) + "/" +
        wearing_name + "_" + std::to_string(id) + "_walk_down.png";
    auto part = PlayerPart::create(real_path, wearing_name);
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 1.0 / 3));
    wearings.pushBack(part);
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
    WEARING_TRAVELSAL(wearing)
    {
        wearing->go(direction, WEARING, wearingId[wearing->part_name]);
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

void Player::fishing()
{
    std::map<int, std::string> numToString = { {UP,"up"}, {RIGHT, "right"}, {LEFT, "left"}, {DOWN, "down"} };
    if (faceTo != UP)
    {
        PLAYER_TRAVELSAL(part)
        {
            if (part->part_name == "arm")
            {
                part->setTexture("motion/fishing_" + numToString[faceTo] + "/arm_fishing_" + numToString[faceTo] + ".png");
            }
        }
    }
}

void Player::stand()
{
    PLAYER_TRAVELSAL(part)
    {
        part->stand(faceTo, HUMAN);
    }
    TOOL_TRAVELSAL(tool)
    {
        tool->stand(faceTo, TOOL);
    }
    WEAPON_TRAVELSAL(weapon)
    {
        weapon->stand(faceTo, WEAPON);
    }
    WEARING_TRAVELSAL(wearing)
    {
        wearing->stand(faceTo, WEARING);
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
    WEARING_TRAVELSAL(wearing)
    {
        wearing->setPosition(vec);
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
    WEARING_TRAVELSAL(wearing)
    {
        wearing->setScale(scale);
    }
}

void Player::moveUpdate(MotionManager* information)
{
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    auto light_hit = cocos2d::EventKeyboard::KeyCode::KEY_J;
    auto heavy_hit = cocos2d::EventKeyboard::KeyCode::KEY_K;
    auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_C;
    auto fishing = cocos2d::EventKeyboard::KeyCode::KEY_F;

    int offsetX = 0;
    Direction direction;
    if (information->keyMap[left])
    {
        offsetX = -4;
        direction = LEFT;
    }
    else if (information->keyMap[right])
    {
        offsetX = 4;
        direction = RIGHT;
    }
    else if (information->keyMap[down])
    {
        offsetX = 4;
        direction = DOWN;
    }
    else if (information->keyMap[up])
    {
        offsetX = 4;
        direction = UP;
    }

    // 获取对象
    // Player* farmer = (Player*)this->getChildByTag(characterID[player]);
    // Player* abigail = (Player*)this->getChildByTag(characterID[Abigail]);
    auto pos = this->get_parts().at(0)->getPosition();
    if (this) {
        CCLOG("Position %f %f", pos.x, pos.y);
    }
    if (offsetX != 0)
    {
        if (!can_move(this->getTiledMap(), pos, direction)) return;
        this->go(direction);
    }

    // 轻重击 
    if (information->keyMap[light_hit])
    {
        this->light_hit();
    }
    else if (information->keyMap[heavy_hit])
    {
        this->heavy_hit();
    }
    // 钓鱼
    else if (information->keyMap[fishing])
        this->fishing();
    information->playerPosition = this->parts.at(0)->getPosition();
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
Vector<PlayerPart*> Player::get_wearings()
{
    return wearings;
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

void NPC::add_dialogs(const std::vector<std::string>& dialogs_)
{
    dialogs = dialogs_;
}

void NPC::communicate()
{
    // 对话框部分
    auto dialogFrame = DialogFrame::create(dialogs.at(0));
    dialogFrame->setPosition(Vec2(-625, -800));
    this->addChild(dialogFrame);

    // 设置关闭按钮的回调函数
    dialogFrame->setCloseCallback([]() {
        CCLOG("Dialog closed!");
        });
    // 设置对话框头像
    dialogFrame->setAvatar("chracters/portraits/Abigail/Abigail_common.png");
    dialogFrame->setDialogList(dialogs);

}

void NPC::communicate(const std::string& text, const std::string& emotion)
{
    auto dialogFrame = DialogFrame::create(text);
    dialogFrame->setPosition(Vec2(-625, -800));
    this->addChild(dialogFrame);

    // 设置关闭按钮的回调函数
    dialogFrame->setCloseCallback([]() {
        CCLOG("Dialog closed!");
        });
    // 设置对话框头像
    dialogFrame->setAvatar("chracters/portraits/Abigail/Abigail_"+ emotion +".png");
}

void NPC::moveUpdate(MotionManager * information)
{
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    auto light_hit = cocos2d::EventKeyboard::KeyCode::KEY_J;
    auto heavy_hit = cocos2d::EventKeyboard::KeyCode::KEY_K;
    auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_C;
    auto gift = cocos2d::EventKeyboard::KeyCode::KEY_G;
    if (information->keyMap[communicate])
    {
        // 距离多少能交互？
        const int dis_limit = 30;
        float dis = abs(information->playerPosition.x - this->getPosition().x) +
            abs(information->playerPosition.y - this->getPosition().y);
        if (dis < dis_limit)
        {
            this->communicate();
        }
    }
    else if (information->keyMap[gift])
    {
        // 距离多少能交互？
        const int dis_limit = 30;
        float dis = abs(information->playerPosition.x - this->getPosition().x) +
            abs(information->playerPosition.y - this->getPosition().y);
        if (dis < dis_limit)
        {
            this->receive_gift();
        }
    }
}

void NPC::receive_gift()
{
    communicate("Thank you, I just love it!", "smile");
}
