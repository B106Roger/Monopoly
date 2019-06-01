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
		double percent = (rand() % 401 - 200); // (-200 - +200) / 1000.0
		if (percent >= 100) percent = 100;
		else if (percent <= -100) percent = -100;
		percent /= 1000.0;
		stockList[i].currentDollars = (1.0 + percent) * stockList[i].currentDollars;
		
	
		
	}
}

void Bank::initialStock()
{
	Stock stock1, stock2, stock3, stock4, stock5, stock6;
	stock1.currentDollars = 200;
	stock1.name = L"腥象電子";
	stock1.previousDollars = 197;
	stock1.stockId = 0;
	stockList.push_back(stock1);

	stock2.currentDollars = 250;
	stock2.name = L"賣台積電";
	stock2.previousDollars = 260;
	stock2.stockId = 1;
	stockList.push_back(stock2);

	stock3.currentDollars = 55;
	stock3.name = L"　　裙創";
	stock3.previousDollars = 50;
	stock3.stockId = 2;
	stockList.push_back(stock3);

	stock4.currentDollars = 3800;
	stock4.name = L"大力光頭";
	stock4.previousDollars = 4085;
	stock4.stockId = 3;
	stockList.push_back(stock4);

	stock5.currentDollars = 45;
	stock5.name = L"　神盾局";
	stock5.previousDollars = 50;
	stock5.stockId = 4;
	stockList.push_back(stock5);

	stock6.currentDollars = 87;
	stock6.name = L"威剛製藥";
	stock6.previousDollars = 93;
	stock6.stockId = 5;
	stockList.push_back(stock6);
}
int Bank::buyStock(Player & player, vector<int> numberOfStock)   // vector存股票購買數量
{
	int total = 0;
	int playerId = player.id;
	for (int i = 0; i < int(numberOfStock.size()); i++)
	{
		int stockId = stockList[i].stockId;
		total += stockList[i].currentDollars * numberOfStock[i];
		vector<StockRecord>::iterator it = find_if(
			stockOwnerList[playerId].begin(), 
			stockOwnerList[playerId].end(), 
			[i, stockId](StockRecord & ref) {return ref.stockId == stockId; }
		);
		if (it == stockOwnerList[playerId].end())
		{
			stockOwnerList[playerId].push_back(StockRecord{ playerId,stockId,numberOfStock[i ]});
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

void Bank::bankruptStock(int playerState) {
	for (StockRecord & ref : stockOwnerList[playerState])
	{
		ref.number = 0;
	}
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
		vector<Stock>::iterator it = find_if(stockList.begin(), stockList.end(), [stockTargetId](Stock & stock) {return stock.stockId == stockTargetId; });
		total += ref.number * it->currentDollars;
	}
	// 房產
	for (RealEstate & ref : GameWorld::gameMap)
	{
		if (ref.ownerId != pl.id)
		{
			continue;
		}
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

int Bank::computePlayerStockAsset(Player & p1) {
	int total = 0;
	// 股票
	for (StockRecord & ref : stockOwnerList[p1.id])
	{
		int stockTargetId = ref.stockId;
		vector<Stock>::iterator it = find_if(stockList.begin(), stockList.end(), [stockTargetId](Stock & ref) {return ref.stockId == stockTargetId; });
		total += ref.number * it->currentDollars;
	}
	return total;
}