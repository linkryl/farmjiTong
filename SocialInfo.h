#pragma once
#include <string>
#include <map>
#include "cocos2d.h"
using namespace cocos2d;
// ί�нṹ
struct Entrust
{
  // �����ί�еĸ���
  int num;
  // ί�е�id
  int id;
  // ������
  std::string master;
  // ������ı�
  std::string requirement;//��Ӧ����20
  // �������Ʒ
  std::string item;
  Entrust() { id = num++; }
  Entrust(const std::string& master, const  std::string& requirement, const  std::string& item) : master(master), requirement(requirement), item(item) { id = id++; }
};
class SocialInfo
{
public:
  // �øж��������½��ĵ��ζ�Ӧ������
  std::map<int, int> delta_favorability = { {1, 100}, {2, 200}, {3, 500} };//������
  // �͸���NPC�ĺøж�
  std::map<std::string, int> favorabilities;//intֵ��Ӧ����10

  // ����NPC�����ί��
  std::vector<Entrust> entrusts;
  // NPC������
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
    static SocialInfo* instance = new SocialInfo(); // ʹ�þ�̬�ֲ�������ʼ��
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
    // ʹ�� erase-remove idiom �Ƴ�ָ�� id ������Ԫ��
    entrusts.erase(
      std::remove_if(entrusts.begin(), entrusts.end(),
        [id](const Entrust& entrust) { return entrust.id == id; }),
      entrusts.end()
    );
  }
};