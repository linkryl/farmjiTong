#pragma once
#include "cocos2d.h"
#include "PlayerData.h"
#include "Util.h"
#include <map>
#include <string>
using namespace cocos2d;

// 用于遍历Player的各个身体部分的宏
#define PLAYER_TRAVELSAL(part) for (const auto part : parts)
#define TOOL_TRAVELSAL(tool) for (const auto tool : tools)
#define WEAPON_TRAVELSAL(weapon) for (const auto weapon : weapons)

class Player;
enum Part_catogory { HUMAN, TOOL, WEAPON, WEARING };

class PlayerPart : public Sprite
{
protected:
    // 帧的宽度与高度
    const int width = 16, height = 32;
    // 玩家运气
    float luck;
    // 玩家速度
    int speed;
    // Player虚节点对象
    Player* player;
    // 这部分的类别
    Part_catogory part_catogory;
    // 这部分的名称
    std::string part_name;
    // 名称映射到类别
    std::map<std::string, Part_catogory> nameToCatogory = { {"body", HUMAN}, {"arm", HUMAN}, {"axe", TOOL},
        {"pickaxe", TOOL}, {"hoe", TOOL}, { "sword", WEAPON }, {"sickle", WEARING} };
    std::map<Motion, int> hashValue = { {GO, 147}, {LIGHT_HIT, 458}, {HEAVY_HIT, 749}, {STAND, 8674} };
    std::map<std::string, int> partNameHash = { {"body", 4556498}, {"arm", 843458}, {"axe", 43545364},
        {"pickaxe", 56431512}, {"hoe", 54444545}, {"sword", 9522665}, {"sickle", 984213056} };
public:
    PlayerPart() : luck(0.0f), speed(1) {}
    PlayerPart(const std::string& part_name, const int width_ = 16, const int height_ = 32) : luck(0.0f), speed(1), part_name(part_name), width(width_), height(height_)
    {
        part_catogory = nameToCatogory[part_name];
    }

    void go(const Direction direction, const Part_catogory catogory = HUMAN);
    virtual void stand(const Direction direction);
    virtual void light_hit(const Direction direction);
    virtual void heavy_hit(const Direction direction);

    void setPlayer(Player* player);
    Player* getPlayer();

    static PlayerPart* create(const std::string& path, const std::string& part_name);
};

class Player : public Node
{
private:
    // 角色的身体各个部分
    Vector<PlayerPart*> parts;
    // 角色手持的工具（重击动作）
    Vector<PlayerPart*> tools;
    // 角色手持的武器（轻击动作）
    Vector<PlayerPart*> weapons;
    // 角色的衣着
    Vector<PlayerPart*> wearings;

    // 幸运值
    float luck;
    // 速度
    int speed;
    // 朝向方向
    Direction faceTo;
    // 所在地图
    TMXTiledMap* tmxMap;
public:
    Player(TMXTiledMap* map = nullptr) : luck(0), speed(1), faceTo(DOWN) {
        tmxMap = map;
    }

    void setTiledMap(TMXTiledMap* map);
    TMXTiledMap* getTiledMap();
    void add_part(const std::string& path, const std::string& part_name);
    void add_tool(const std::string& path, const std::string& tool_name);
    void add_weapon(const std::string& path, const std::string& weapon_name);
    void go(Direction direction);
    void heavy_hit();
    void light_hit();
    void stand();
    void setPosition(const Vec2& vec);
    void setScale(const float scale);
    Vector<PlayerPart*> get_parts();
    Vector<PlayerPart*> get_tools();
    Vector<PlayerPart*> get_weapons();

    static Player* create();
};