#pragma once
#include <string>
#include <map>
#include "cocos2d.h"
using namespace cocos2d;
// 委托结构
struct Entrust
{
  // 提出的委托的个数
  int num;
  // 委托的id
  int id;
  // 请求者
  std::string master;
  // 请求的文本
  std::string requirement;//不应长于20
  // 请求的物品
  std::string item;
  Entrust() { id = num++; }
  Entrust(const std::string& master, const  std::string& requirement, const  std::string& item) : master(master), requirement(requirement), item(item) { id = id++; }
};
class SocialInfo
{
public:
  // 好感度提升和下降的档次对应的数字
  std::map<int, int> delta_favorability = { {1, 100}, {2, 200}, {3, 500} };//已弃用
  // 和各个NPC的好感度
  std::map<std::string, int> favorabilities;//int值不应大于10

  // 各个NPC提出的委托
  std::vector<Entrust> entrusts;
  // NPC的名字
  std::vector<std::string> NPC_names;

  SocialInfo()
  {
    add_NPC("Abigail");
    Entrust en1("Abigail", "I need crops", "FarmIcon");
    Entrust en2("Alex", "I need fish", "FishIcon");
    add_entrust(en1);
    add_entrust(en2);
  }
  static SocialInfo* getInstance()
  {
    static SocialInfo* instance = new SocialInfo(); // 使用静态局部变量初始化
    return instance;
  }
  void add_NPC(const std::string& NPC_name)
  {
    NPC_names.push_back(NPC_name);
    favorabilities[NPC_name] = 0;
  }
  void add_NPCs(const std::vector<std::string>& NPC_names_)
  {
    for (const auto& name : NPC_names_)
      add_NPC(name);
  }
  void add_entrust(const Entrust& entrust)
  {
    entrusts.push_back(entrust);
  }
  void add_entrusts(const std::vector<Entrust>& entrusts_)
  {
    for (const auto& entrust : entrusts_)
      add_entrust(entrust);
  }
  void decrease_favorability(const std::string& name)
  {
    --favorabilities[name];
  }
  void increase_favorability(const std::string& name)
  {
    ++favorabilities[name];
  }
  int NPC_favorability(const std::string& name)
  {
    return favorabilities[name];
  }
  void solve_entrust(int id)
  {
    // 使用 erase-remove idiom 移除指定 id 的所有元素
    entrusts.erase(
      std::remove_if(entrusts.begin(), entrusts.end(),
        [id](const Entrust& entrust) { return entrust.id == id; }),
      entrusts.end()
    );
  }
};