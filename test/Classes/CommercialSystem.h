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
	// ��ƷID->��Ʒ�۸�
	map<int, int> IDToPrice;
	// ���յ���Ʒ������
	map<int, int> yesterday_supply;
	// ���յ���Ʒ������
	map<int, int> yesterday_demand;
	// ���յ���Ʒ������
	map<int, int> today_supply;
	// ���յ���Ʒ������
	map<int, int> today_demand;
public:
	// ����ID-�۸����������ʼ���۸�
	void initialize_price(const vector<pair<int, int>>& input)
	{
		for (const auto& item : input)
		{
			int id = item.first;
			int price = item.second;
			IDToPrice[id] = price;
		}
	}
	// ÿ�ո��¼۸�
	void update_price()
	{
		srand(time(0));
		for (const auto& item : IDToPrice)
		{
			int id = item.first;
			int price = item.second;
			// �۸�仯��
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
	// ���һ������
	void demand(int id, int amount)
	{
		today_demand[id] += amount;
	}
	// ���һ�ι���
	void supply(int id, int amount)
	{
		today_supply[id] += amount;
	}
};