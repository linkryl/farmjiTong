#pragma once
#include <string>
#include <vector>
#include <map>
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
	std::string requirement;
	// �������Ʒ
	std::string item;
	Entrust() { id = num++; }
	Entrust(std::string master, std::string requirement, std::string item) : master(master), requirement(requirement), item(item) { id = id++; }
};
class SocialInfo
{
private:
	// �øж��������½��ĵ��ζ�Ӧ������
	std::map<int, int> delta_favorability = { {1, 100}, {2, 200}, {3, 500} };
	// �͸���NPC�ĺøж�
	std::map<std::string, int> favorabilities;
	// ����NPC�����ί��
	std::vector<Entrust> entrusts;
	// NPC������
	std::vector<std::string> NPC_names;
public:
	SocialInfo() {}
	void add_NPC(const std::string& NPC_name)
	{
		NPC_names.push_back(NPC_name);
		favorabilities[NPC_name] = 0;
	}
	void add_NPCs(const std::vector<std::string> NPC_names_)
	{
		for (const auto& name : NPC_names_)
			add_NPC(name);
	}
	void add_entrust(const Entrust& entrust)
	{
		entrusts.push_back(entrust);
	}
	void add_entrusts(const std::vector<Entrust> entrusts_)
	{
		for (const auto& entrust : entrusts_)
			add_entrust(entrust);
	}
	void decrease_favorability(std::string name, int extent)
	{
		favorabilities[name] -= delta_favorability[extent];
	}
	void increase_favorability(std::string name, int extent)
	{
		favorabilities[name] += delta_favorability[extent];
	}
	int NPC_favorability(std::string name)
	{
		return favorabilities[name];
	}
	void solve_entrust(int id)
	{
		for (auto it = entrusts.begin(); it != entrusts.end(); )
		{
			const auto& entrust = *it;
			if (entrust.id == id)
				entrusts.erase(it);
		}
	}
};