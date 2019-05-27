#include "Bank.h"
#include"GameWorld.h"
vector<Stock> Bank::stockList;
vector<vector<StockRecord>> Bank::stockOwnerList;

Bank::Bank()
{
	initialStock();
}


Bank::~Bank()
{
}


// 初始化股票列表
void Bank::stockUpate()
{
	for (int i = 0; i < stockList.size(); i++) {
		stockList[i].previousDollars = stockList[i].currentDollars;
		stockList[i].currentDollars = (1.0 + -rand() % 100 / 1000.0) * stockList[i].currentDollars;
	}
}

void Bank::initialStock()
{
	Stock stock1, stock2, stock3, stock4, stock5, stock6;
	stock1.currentDollars = 200;
	stock1.name = L"腥象電子";
	stock1.previousDollars = 197;
	stock1.stockId = 1;
	stockList.push_back(stock1);

	stock2.currentDollars = 250;
	stock2.name = L"賣台積電";
	stock2.previousDollars = 260;
	stock2.stockId = 2;
	stockList.push_back(stock2);

	stock3.currentDollars = 50;
	stock3.name = L"　　裙創";
	stock3.previousDollars = 150;
	stock3.stockId = 3;
	stockList.push_back(stock3);

	stock4.currentDollars = 3800;
	stock4.name = L"大力光頭";
	stock4.previousDollars = 4085;
	stock4.stockId = 4;
	stockList.push_back(stock4);

	stock5.currentDollars = 50;
	stock5.name = L"　神盾局";
	stock5.previousDollars = 150;
	stock5.stockId = 5;
	stockList.push_back(stock5);

	stock6.currentDollars = 87;
	stock6.name = L"威剛製藥";
	stock6.previousDollars = 99;
	stock6.stockId = 6;
	stockList.push_back(stock6);
}
int Bank::buyStock(Player & player, vector<int> numberOfStock)   // vector存股票購買數量
{
	int total = 0;
	int playerId = player.id;
	for (int i = 0; i < int(numberOfStock.size()); i++)
	{
		total += stockList[i].currentDollars * numberOfStock[i];
		vector<StockRecord>::iterator it = find_if(
			stockOwnerList[playerId].begin(), 
			stockOwnerList[playerId].end(), 
			[i](StockRecord & ref) {return ref.stockId == i; }
		);
		if (it == stockOwnerList[playerId].end())
		{
			stockOwnerList[playerId].push_back(StockRecord{ playerId,i,numberOfStock[i ]});
		}
		else
		{
			it->number += numberOfStock[i];
		}

	}
	return total;
}

int Bank::soldStock(Player & player, vector<int>numberOfStock)
{	//假定要賣的張數都沒有超過持有股票數
	int total = 0;
	int playerId = player.id;
	for (int i = 0; i < int(numberOfStock.size()); i++)
	{
		if (numberOfStock[i] != 0) {			//有要賣出才做處理
			total += stockList[i].currentDollars * numberOfStock[i];
			vector<StockRecord>::iterator it = find_if(
				stockOwnerList[playerId].begin(),
				stockOwnerList[playerId].end(),
				[i](StockRecord & ref) {return ref.stockId == i; }
			);
			if (it != stockOwnerList[playerId].end())		//找到要賣掉的股票並賣掉
			{
				it->number -= numberOfStock[i];
			}
		}

	}
	return total;
}


// 計算玩家資產
int Bank::computePlayerAsset(Player & pl)
{
	int total = 0;
	total += pl.cash;
	total += pl.bankBalance;
	// 股票
	for (StockRecord & ref : stockOwnerList[pl.id])
	{
		int stockTargetId = ref.stockId;
		vector<Stock>::iterator it = find_if(stockList.begin(), stockList.end(), [stockTargetId](Stock & ref) {return ref.stockId == stockTargetId; });
		total += ref.number * it->currentDollars;
	}
	// 房產
	for (RealEstate & ref : GameWorld::gameMap)
	{
		int estateCost = ref.buyCost;
		double rate = 0.75;
		if (ref.ownerId == pl.id)
		{
			for (int i = 0; i < ref.level; i++)
			{
				estateCost += int(rate * (double)ref.buyCost);
			}
			rate += 0.25;
		}
		total += estateCost;
	}
	return total;
}
