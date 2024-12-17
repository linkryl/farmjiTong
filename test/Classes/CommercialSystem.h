#pragma once
#include <string>
#include <map>
#include <vector>
#include <random>
#include <ctime>
using namespace std;
class CommercialSystem
{
private:
	// 物品ID->物品价格
	map<int, int> IDToPrice;
	// 昨日的物品供给量
	map<int, int> yesterday_supply;
	// 昨日的物品需求量
	map<int, int> yesterday_demand;
	// 今日的物品供给量
	map<int, int> today_supply;
	// 今日的物品需求量
	map<int, int> today_demand;
public:
	// 输入ID-价格对序列来初始化价格
	void initialize_price(const vector<pair<int, int>>& input)
	{
		for (const auto& item : input)
		{
			int id = item.first;
			int price = item.second;
			IDToPrice[id] = price;
		}
	}
	// 每日更新价格
	void update_price()
	{
		srand(time(0));
		for (const auto& item : IDToPrice)
		{
			int id = item.first;
			int price = item.second;
			// 价格变化量
			int delta_price = rand() % int(price / 100.0);
			if (yesterday_demand[id] - yesterday_supply[id] > 0)
			{
				if (yesterday_supply[id])
					delta_price += price / 100.0 * ((float)yesterday_demand[id] / yesterday_supply[id]);
				else
					delta_price += price / 50.0;
			}
			else if (yesterday_demand[id] - yesterday_supply[id] == 0);
			else
			{
				if (yesterday_demand[id])
					delta_price -= price / 100.0 * ((float)yesterday_supply[id] / yesterday_demand[id]);
				else
					delta_price -= price / 50.0;
			}
			IDToPrice[id] += delta_price;
			yesterday_supply[id] = today_supply[id];
			today_supply[id] = 0;
			yesterday_demand[id] = today_demand[id];
			today_demand[id] = 0;
		}
	}
	// 添加一次需求
	void demand(int id, int amount)
	{
		today_demand[id] += amount;
	}
	// 添加一次供给
	void supply(int id, int amount)
	{
		today_supply[id] += amount;
	}
};