#include "Player.h"
#include "DialogFrame.h"
#include <functional>

void PlayerPart::go(const Direction direction, const Part_catogory catogory, const int id)
{
    // ��׼�ٶ�
    double base_speed = 80;
    // һ��6֡
    const int upper_limit = 6;
    // ÿһ֡�����ļ��
    const float frameGap = 0.2;
    int originDistance = speed * base_speed, distance = originDistance;
    for (int i = 1; i <= originDistance; ++i) {
        Vec2 pos = modifyVec2(Vec2(getPosition()), direction, i);
        if (!can_move(getPlayer()->getTiledMap(), pos, direction)) {
            distance = i - 1;
            break;
        }
    }
    // ����
    Vec2 moveVec2 = generateVec2(direction, distance);
    auto moveAction = MoveBy::create(upper_limit * frameGap * distance / originDistance, moveVec2);
    // ����ӳ�䵽string
    std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
    if (catogory == HUMAN)
    {
        // ����
        // ����֡����map
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

        // ��������Spawn
        auto moveSpawn = Spawn::createWithTwoActions(moveAction, animate);

        const size_t hash_value = partNameHash[part_name] + direction + hashValue[GO];
        moveSpawn->setTag(hash_value);
        // ���if������֤�˶���������ж�������;�����
        const auto sign = this->_actionManager->getActionByTag(hash_value, this);
        if (this->_actionManager->getActionByTag(hash_value, this) == nullptr)
        {
            // UP�ǵ�һ��ö���࣬LEFT�����һ��
            for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
                // �����������Ķ���
                if (i != direction)
                    this->stopActionByTag(i - direction + hash_value);
            this->runAction(moveSpawn);
        }
    }
    else if (catogory == TOOL || catogory == WEAPON)
    {
        const size_t hash_value = partNameHash[part_name] + direction + hashValue[GO];
        moveAction->setTag(hash_value);
        // ���if������֤�˶���������ж�������;�����
        const auto sign = this->_actionManager->getActionByTag(hash_value, this);
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
    else if (catogory == WEARING)
    {
        const size_t hash_value = partNameHash[part_name] + direction + hashValue[GO];
        moveAction->setTag(hash_value);
        // ���if������֤�˶���������ж�������;�����
        const auto sign = this->_actionManager->getActionByTag(hash_value, this);
        if (this->_actionManager->getActionByTag(hash_value, this) == nullptr)
        {
            // UP�ǵ�һ��ö���࣬LEFT�����һ��
            for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
                // �����������Ķ���
                if (i != direction)
                    this->stopActionByTag(i - direction + hash_value);
            this->runAction(moveAction);
        }
        // ��������
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
        // ����ӳ�䵽string
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
    // һ��6֡
    const int upper_limit = 6;
    // ÿһ֡�����ļ��
    const float frameGap = 0.05;
    // ����ӳ�䵽string
    std::map<int, std::string> numToString = { {UP,"light_hit_up"}, {RIGHT, "light_hit_right"}, {LEFT, "light_hit_left"}, {DOWN, "light_hit_down"} };
    // ����
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
    // ���if������֤�˶���������ж�������;�����
    const auto sign = this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this);
    if (this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this) == nullptr)
    {
        // UP�ǵ�һ��ö���࣬LEFT�����һ��
        for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
            // �����������Ķ���
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
    // һ��6֡
    const int upper_limit = 6;
    // ÿһ֡�����ļ��
    const float frameGap = 0.10;
    // ����ӳ�䵽string
    std::map<int, std::string> numToString = { {UP,"heavy_hit_up"}, {RIGHT, "heavy_hit_right"}, {LEFT, "heavy_hit_left"}, {DOWN, "heavy_hit_down"} };
    // ����
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
    // ���if������֤�˶���������ж�������;�����
    const auto sign = this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this);
    if (this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this) == nullptr)
    {
        // UP�ǵ�һ��ö���࣬LEFT�����һ��
        for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
            // �����������Ķ���
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
    tool = part;
    //tools.pushBack(PlayerPart::create(path, tool_name));
}

void Player::add_weapon(const std::string& path, const std::string& weapon_name)
{
    auto part = PlayerPart::create(path, weapon_name);
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 1.0 / 3));
    weapon = part;
}

void Player::add_wearing(const std::string& path, const std::string& wearing_name, const int id)
{
    // ���Ķ�Ӧ�·��ı��
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
    tool->go(direction, TOOL);
    weapon->go(direction, WEAPON);
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
    // �������Ͽ����������ɴ಻Ҫ��
    if (faceTo != UP)
       tool->heavy_hit(faceTo);
}

void Player::light_hit()
{
    PLAYER_TRAVELSAL(part)
    {
        part->light_hit(faceTo);
    }
    // ����һ���ģ����Ͽ��Ķ���������
    if (faceTo != UP)
        weapon->light_hit(faceTo);
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
    if (tool != nullptr)
        tool->stand(faceTo, TOOL);
    if (weapon != nullptr)
        weapon->stand(faceTo, WEAPON);
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
    if (tool != nullptr)
        tool->setPosition(vec);
    if (weapon != nullptr)
        weapon->setPosition(vec);
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
    if (tool != nullptr)
        tool->setScale(scale);
    if (tool != nullptr)
        weapon->setScale(scale);
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

    bool move = false;
    Direction direction;
    if (information->keyMap[left])
    {
        move = true;
        direction = LEFT;
    }
    else if (information->keyMap[right])
    {
        move = true;
        direction = RIGHT;
    }
    else if (information->keyMap[down])
    {
        move = true;
        direction = DOWN;
    }
    else if (information->keyMap[up])
    {
        move = true;
        direction = UP;
    }
    auto pos = this->get_parts().at(0)->getPosition();
    if (this) {
        CCLOG("Position %f %f", pos.x, pos.y);
    }
    if (move)
    {
        if (!can_move(this->getTiledMap(), pos, direction)) return;
        this->go(direction);
    }

    // ���ػ� 
    if (information->keyMap[light_hit] && !move)
    {
        this->light_hit();
    }
    else if (information->keyMap[heavy_hit] && !move)
    {
        this->heavy_hit();
    }
    // ����
    else if (information->keyMap[fishing] && !move)
        this->fishing();
    auto currentPosition = this->parts.at(0)->getPosition();
    currentPosition.x += this->getScaleX() / 2;
    currentPosition.y += this->getScaleY() / 2;

    information->playerPosition = currentPosition;
}

Vector<PlayerPart*> Player::get_parts()
{
    return parts;
}

PlayerPart* Player::get_tools()
{
    return tool;
}

PlayerPart* Player::get_weapons()
{
    return weapon;
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
    if (communicating) return;
    communicating = true;
    // �Ի��򲿷�
    auto dialogFrame = DialogFrame::create(dialogs.at(0));
    dialogFrame->setPosition(Vec2(-625, -800));
    this->addChild(dialogFrame);

    // ���ùرհ�ť�Ļص�����
    dialogFrame->setCloseCallback([&]() {
        CCLOG("Dialog closed!");
        communicating = false;
        });
    // ���öԻ���ͷ��
    dialogFrame->setAvatar("chracters/portraits/Abigail/Abigail_common.png");
    dialogFrame->setDialogList(dialogs);

}

void NPC::communicate(const std::string& text, const std::string& emotion)
{
    if (communicating) return;
    communicating = true;
    auto dialogFrame = DialogFrame::create(text);
    dialogFrame->setPosition(Vec2(-625, -800));
    this->addChild(dialogFrame);

    // ���ùرհ�ť�Ļص�����
    dialogFrame->setCloseCallback([&]() {
        CCLOG("Dialog closed!");
        communicating = false;
        });
    // ���öԻ���ͷ��
    dialogFrame->setAvatar("chracters/portraits/Abigail/Abigail_"+ emotion +".png");
}

void NPC::moveUpdate(MotionManager * information)
{
    auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_C;
    auto gift = cocos2d::EventKeyboard::KeyCode::KEY_G;
    if (information->keyMap[communicate])
    {
        // ��������ܽ�����
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
        // ��������ܽ�����
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
