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
	std::string requirement;
	// 请求的物品
	std::string item;
	Entrust() { id = num++; }
	Entrust(std::string master, std::string requirement, std::string item) : master(master), requirement(requirement), item(item) { id = id++; }
};
class SocialInfo
{
private:
	// 好感度提升和下降的档次对应的数字
	std::map<int, int> delta_favorability = { {1, 100}, {2, 200}, {3, 500} };
	// 和各个NPC的好感度
	std::map<std::string, int> favorabilities;
	// 各个NPC提出的委托
	Vector<Entrust> entrusts;
	// NPC的名字
	Vector<std::string> NPC_names;
public:
	SocialInfo() {}
	void add_NPC(const std::string& NPC_name)
	{
		NPC_names.pushBack(NPC_name);
		favorabilities[NPC_name] = 0;
	}
	void add_NPCs(const Vector<std::string> NPC_names_)
	{
		for (const auto& name : NPC_names_)
			add_NPC(name);
	}
	void add_entrust(const Entrust& entrust)
	{
		entrusts.pushBack(entrust);
	}
	void add_entrusts(const Vector<Entrust> entrusts_)
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
		for (const auto& entrust : entrusts)
		{
			if (entrust.id == id)
				entrusts.eraseObject(entrust);
		}
	}
};