#include "Player.h"
#include "DialogFrame.h"
#include "StoreScene.h"
#include <functional>
#include <random>
#include <ctime>
#include "Constant.h"
#include "Scenes/BagScene.h"
#include "skill.h"
#include "Utils/SceneUtil.h"
#include "SocialInfo.h"
#include "Item.h"
#include "Systems/Farm_system.h"
#include "Systems/Livestock_farm_system.h"
#include "AudioPlayer.h"

void PlayerPart::go(const Direction direction, const Part_catogory catogory, const int id)
{
    // һ��6֡
    const int upper_limit = 6;
    // ÿһ֡�����ļ��
    const float frameGap = 0.2;
    int originDistance = speed * BASE_MOVE_DISTANCE, distance = originDistance;
    for (int i = 1; i <= originDistance; ++i) {
        Vec2 pos = modifyVec2(Vec2(getPosition()), direction, i);
        if (!canMove(getPlayer()->getTiledMap(), pos, direction)) {
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
    else if (catogory == TOOL || catogory == WEAPON || catogory == SHADOW)
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
    if (catogory != WEARING && catogory != SHADOW)
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
    const float frameGap = 0.07;
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
void Player::regist(MotionManager* motionManager, Node* father)
{
    motionManager->add_movableObject(this);
    father->addChild(this);
    auto farmer_parts = this->get_parts();
    auto farmer_tools = this->get_tools();
    auto farmer_weapons = this->get_weapons();
    auto farmer_wearings = this->get_wearings();
    auto farmer_shadow = this->get_shadow();
    for (auto wearing : farmer_wearings)
        father->addChild(wearing);
    for (auto part : farmer_parts)
        if (part->part_name == "arm")
            father->addChild(part);
        else
            father->addChild(part);
    if (farmer_tools)
        father->addChild(farmer_tools);
    if (farmer_weapons)
        father->addChild(farmer_weapons);
}
void Player::regist(MotionManager* motionManager, Node* father, int Zorder)
{
    if (father == this->_parent)
        return;
    motionManager->add_movableObject(this);
    auto farmer_parts = this->get_parts();
    auto farmer_tools = this->get_tools();
    auto farmer_weapons = this->get_weapons();
    auto farmer_wearings = this->get_wearings();
    auto farmer_shadow = this->get_shadow();
    if (1)
    {
        for (auto i : farmer_parts)
            i->_parent = nullptr;
        for (auto i : farmer_wearings)
            i->_parent = nullptr;
        farmer_tools->_parent = nullptr;
        farmer_weapons->_parent = nullptr;
        farmer_shadow->_parent = nullptr;
        _parent = nullptr;
    }
    father->addChild(this, Zorder);
    for (auto wearing : farmer_wearings)
        father->addChild(wearing, Zorder + 1);
    for (auto part : farmer_parts)
        if (part->part_name == "arm")
            father->addChild(part, Zorder + 2);
        else
            father->addChild(part);
    if (farmer_tools)
        father->addChild(farmer_tools, Zorder + 3);
    if (farmer_weapons)
        father->addChild(farmer_weapons, Zorder + 4);
    if (farmer_shadow)
        father->addChild(farmer_shadow, Zorder - 6);
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
    parts.push_back(part);
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
    // ��� wearingId �Ƿ���� wearing_name��������������ʼ��
    if (wearingId.find(wearing_name) == wearingId.end())
    {
        wearingId[wearing_name] = 0;
    }

    // ���� wearingId
    wearingId[wearing_name] = id;

    std::string real_path = path + "/" + wearing_name + "_" + std::to_string(id) + "/" +
        wearing_name + "_" + std::to_string(id) + "_walk_down.png";
    auto part = PlayerPart::create(real_path, wearing_name);
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 1.0 / 3));
    if (wearings.size() >= 2)
    {
        wearings.clear();
    }
    wearings.push_back(part);
}
void Player::add_shadow(const std::string& path)
{
    auto part = PlayerPart::create(path, "shadow");
    part->setPlayer(this);
    part->setAnchorPoint(Vec2(0.5, 1.0 / 3));
    shadow = part;
}

void Player::go(Direction direction)
{
    faceTo = direction;

    PLAYER_TRAVELSAL(part)
    {
        part->go(direction);
    }
    WEARING_TRAVELSAL(wearing)
    {
        wearing->go(direction, WEARING, wearingId[wearing->part_name]);
    }
    tool->go(direction, TOOL);
    weapon->go(direction, WEAPON);
    shadow->go(direction, SHADOW);
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
                break;
            }
        }
    }
    Skill* skill = Skill::getInstance();
    //3120�Ǻ���
    //3121������
    //3122������
    //3123������
    //3124�Ǵ󺣲�
    //3125�Ǻ���
    //3126�Ǵ�˵֮��
    // �������
    srand(time(0));
    std::map<int, float> probabilities = { {3120, 0.5}, {3121,0.4}, {3122,0.15}, {3123,0.15}, {3124,0.05}, {3125,0.05}, {3126,0.001} };
    for (int i = 3120; i <= 3126; i++)
    {
        float probability = probabilities[i];
        while (probability >= 1)
        {
            probability -= 1;
            bag->addItem(i, 1);
            skill->add_fishing_exp(1 / probability / 5);
        }
        int a = rand() % (int)(1 / probability);
        if (a == 0)
        {
            bag->addItem(i, 1); 
            skill->add_fishing_exp(1 / probability / 5);
        }
    }
}

void Player::watering()
{
    std::map<int, std::string> numToString = { {UP,"up"}, {RIGHT, "right"}, {LEFT, "left"}, {DOWN, "down"} };
    if (faceTo != UP)
    {
        PLAYER_TRAVELSAL(part)
        {
            if (part->part_name == "arm")
            {
                part->setTexture("motion/watering_" + numToString[faceTo] + "/arm_watering_" + numToString[faceTo] + ".png");
            }
        }
    }
}

void Player::open_backpack()
{
    Director::getInstance()->pushScene(BagScene::createScene());
}

void Player::stand()
{
    PLAYER_TRAVELSAL(part)
    {
        part->stand(faceTo, HUMAN);
    }
    WEARING_TRAVELSAL(wearing)
    {
        wearing->stand(faceTo, WEARING);
    }
    if (tool != nullptr)
        tool->stand(faceTo, TOOL);
    if (weapon != nullptr)
        weapon->stand(faceTo, WEAPON);
    if (shadow != nullptr)
        shadow->stand(faceTo, SHADOW);
}

void Player::setPosition(const Vec2& vec)
{
    Node::setPosition(vec);
    PLAYER_TRAVELSAL(part)
    {
        part->setPosition(vec);
    }
    WEARING_TRAVELSAL(wearing)
    {
        wearing->setPosition(vec);
    }
    if (tool != nullptr)
        tool->setPosition(vec);
    if (weapon != nullptr)
        weapon->setPosition(vec);
    if (shadow != nullptr)
        shadow->setPosition(vec);
}

void Player::setScale(const float scale)
{
    PLAYER_TRAVELSAL(part)
    {
        part->setScale(scale);
    }
    WEARING_TRAVELSAL(wearing)
    {
        wearing->setScale(scale);
    }
    if (tool != nullptr)
        tool->setScale(scale);
    if (weapon != nullptr)
        weapon->setScale(scale);
    if (shadow != nullptr)
        shadow->setScale(scale);
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
    auto watering = cocos2d::EventKeyboard::KeyCode::KEY_L;
    auto openBag = cocos2d::EventKeyboard::KeyCode::KEY_B;

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
        if (!canMove(this->getTiledMap(), pos, direction)) return;
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
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (currentTime - lastFishingTime >= std::chrono::seconds(1))
        {
            this->fishing();
            lastFishingTime = currentTime;
        }
    }
    // ��ˮ
    else if (information->keyMap[watering] && !move) {
        information->keyMap[watering] = false;
        this->watering();
        audioPlayer("../Resources/Music/water.ogg", false);
        Farm_system::getInstance()->add_water(100, pos.x, pos.y);
        Liverstock_farm_system::getInstance()->add_water(100, pos.x, pos.y);
    }
    else if (information->keyMap[openBag])
    {
        information->keyMap[openBag] = false;
        this->open_backpack();
    }

    if (information->keyMap[communicate] && !move) {
        // ��ȡ������Ʒ
        auto bag = Bag::getInstance();
        auto itemInHand = bag->itemInHand;
        // ũ��������
        if (itemInHand == PARSNIP_SEED || itemInHand == WHEAT_SEED) {
            int pixelX = pos.x, pixelY = pos.y;
            bool ok = Farm_system::getInstance()->plant_seed(itemInHand, pixelX, pixelY);
            if (ok) {
                bag->removeItem(itemInHand, 1);
            }
        }
        else if (itemInHand == PIG_SEED) {
            int pixelX = pos.x, pixelY = pos.y;
            bool ok = Liverstock_farm_system::getInstance()->plant_seed(itemInHand, pixelX, pixelY);
            if (ok) {
                bag->removeItem(itemInHand, 1);
            }
        }
        else if (itemInHand == FOOD) {
            int pixelX = pos.x, pixelY = pos.y;
            bool ok = Farm_system::getInstance()->add_fertilizer(100, pixelX, pixelY);
            if (ok) {
                bag->removeItem(itemInHand, 1);
            }
            ok = Liverstock_farm_system::getInstance()->add_food(100, pixelX, pixelY);
            if (ok) {
                bag->removeItem(itemInHand, 1);
            }
        }
    }

    auto currentPosition = pos;
    currentPosition.x += this->getScaleX() / 2;
    currentPosition.y += this->getScaleY() / 2;

    // ����λ��
    information->playerPosition = currentPosition;
    // ����Ѫ��
    health += information->deltaPlayerHealth;
}

std::vector<PlayerPart*> Player::get_parts()
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
std::vector<PlayerPart*> Player::get_wearings()
{
    return wearings;
}
PlayerPart* Player::get_shadow()
{
    return shadow;
}
Player* Player::getInstance()
{
    static Player* player = create();
    return player;
}
Player* Player::create()
{
    Player* player = new Player();
    player->bag = Bag::getInstance();
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
    thisDialog = dialogFrame;
    //dialogFrame->setPosition(Vec2(-625, -800));
    //this->addChild(dialogFrame);
    auto notificationNode = Director::getInstance()->getNotificationNode();
    //auto topLayer = Layer::create();
    //topLayer->addChild(dialogFrame);
    notificationNode->addChild(dialogFrame);

    // ���ùرհ�ť�Ļص�����
    dialogFrame->setCloseCallback([&]() {
        CCLOG("Dialog closed!");
        communicating = false;
        });
    // ���öԻ���ͷ��
    dialogFrame->setAvatar("characters/portraits/Abigail/Abigail_common.png");
    dialogFrame->setDialogList(dialogs);

}

void NPC::communicate(const std::string& text, const std::string& emotion)
{
    if (communicating) return;
    communicating = true;
    auto dialogFrame = DialogFrame::create(text);
    thisDialog = dialogFrame;
    auto notificationNode = Director::getInstance()->getNotificationNode();
    //auto topLayer = Layer::create();
    //topLayer->addChild(dialogFrame);
    notificationNode->addChild(dialogFrame);

    // ���ùرհ�ť�Ļص�����
    dialogFrame->setCloseCallback([&]() {
        CCLOG("Dialog closed!");
        communicating = false;
        });
    // ���öԻ���ͷ��
    dialogFrame->setAvatar("characters/portraits/Abigail/Abigail_"+ emotion +".png");
}

void NPC::moveUpdate(MotionManager * information)
{
    auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_C;
    auto gift = cocos2d::EventKeyboard::KeyCode::KEY_G;
    auto right = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    if (information->keyMap[communicate])
    {
        information->keyMap[communicate] = false;
        // ��������ܽ�����
        const int dis_limit = 30;
        float dis = abs(information->playerPosition.x - this->getPosition().x) +
            abs(information->playerPosition.y - this->getPosition().y);
        if (dis < dis_limit && (this->thisDialog == nullptr || !this->thisDialog->ifCreated))
        {
            this->communicate();
        }
        else if (dis < dis_limit && this->thisDialog->ifCreated)
        {
            thisDialog->closeDialog();
            communicating = false;
            thisDialog = nullptr;
        }
        information->keyMap[communicate] = true;
    }
    else if (information->keyMap[gift])
    {
        information->keyMap[gift] = false;
        // ��������ܽ�����
        const int dis_limit = 30;
        float dis = abs(information->playerPosition.x - this->getPosition().x) +
            abs(information->playerPosition.y - this->getPosition().y);

        if (dis < dis_limit && (this->thisDialog == nullptr || !this->thisDialog->ifCreated))
        {
            this->receive_gift();
        }
        else if (dis < dis_limit && this->thisDialog->ifCreated)
        {
            thisDialog->closeDialog();
            communicating = false;
            thisDialog = nullptr;
        }
    }
    else if (information->keyMap[right])
    {
        information->keyMap[right] = false;
        thisDialog->nextDialog();
    }
}

void NPC::receive_gift()
{
    communicate("Thank you, I just love it!", "smile");
    auto socialInfo = SocialInfo::getInstance();
    socialInfo->increase_favorability("Abigail");
}

void Pierre::communicate()
{
    Director::getInstance()->pushScene(StoreScene::createScene());
}

void Pierre::moveUpdate(MotionManager* information)
{
    auto communicate = cocos2d::EventKeyboard::KeyCode::KEY_C;
    if (information->keyMap[communicate])
    {
        information->keyMap[communicate] = false;
        // ��������ܽ�����
        const int dis_limit = 30;
        float dis = abs(information->playerPosition.x - this->getPosition().x) +
            abs(information->playerPosition.y - this->getPosition().y);
        if (dis < dis_limit)
        {
            this->communicate();
        }
    }
}