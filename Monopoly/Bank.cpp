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


// ��l�ƪѲ��C��
void Bank::stockUpate()
{
	for (int i = 0; i < stockList.size(); i++) {
		stockList[i].previousDollars = stockList[i].currentDollars;
		bool sign = rand() % 2;
		if(sign)
			stockList[i].currentDollars = (1.0 + rand() % 100 / 1000.0) * stockList[i].currentDollars;
		else 
			stockList[i].currentDollars = (1.0 + -rand() % 100 / 1000.0) * stockList[i].currentDollars;
	}
}

void Bank::initialStock()
{
	Stock stock1, stock2, stock3, stock4, stock5, stock6;
	stock1.currentDollars = 200;
	stock1.name = L"�{�H�q�l";
	stock1.previousDollars = 197;
	stock1.stockId = 1;
	stockList.push_back(stock1);

	stock2.currentDollars = 250;
	stock2.name = L"��x�n�q";
	stock2.previousDollars = 260;
	stock2.stockId = 2;
	stockList.push_back(stock2);

	stock3.currentDollars = 50;
	stock3.name = L"�@�@�ȳ�";
	stock3.previousDollars = 150;
	stock3.stockId = 3;
	stockList.push_back(stock3);

	stock4.currentDollars = 3800;
	stock4.name = L"�j�O���Y";
	stock4.previousDollars = 4085;
	stock4.stockId = 4;
	stockList.push_back(stock4);

	stock5.currentDollars = 50;
	stock5.name = L"�@���ާ�";
	stock5.previousDollars = 150;
	stock5.stockId = 5;
	stockList.push_back(stock5);

	stock6.currentDollars = 87;
	stock6.name = L"�­�s��";
	stock6.previousDollars = 99;
	stock6.stockId = 6;
	stockList.push_back(stock6);
}
int Bank::buyStock(Player & player, vector<int> numberOfStock)   // vector�s�Ѳ��ʶR�ƶq
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
{	//���w�n�檺�i�Ƴ��S���W�L�����Ѳ���
	int total = 0;
	int playerId = player.id;
	for (int i = 0; i < int(numberOfStock.size()); i++)
	{
		if (numberOfStock[i] != 0) {			//���n��X�~���B�z
			total += stockList[i].currentDollars * numberOfStock[i];
			vector<StockRecord>::iterator it = find_if(
				stockOwnerList[playerId].begin(),
				stockOwnerList[playerId].end(),
				[i](StockRecord & ref) {return ref.stockId == i; }
			);
			if (it != stockOwnerList[playerId].end())		//���n�汼���Ѳ��ý汼
			{
				it->number -= numberOfStock[i];
			}
		}

	}
	return total;
}


// �p�⪱�a�겣
int Bank::computePlayerAsset(Player & pl)
{
	int total = 0;
	total += pl.cash;
	total += pl.bankBalance;
	// �Ѳ�
	for (StockRecord & ref : stockOwnerList[pl.id])
	{
		int stockTargetId = ref.stockId;
		vector<Stock>::iterator it = find_if(stockList.begin(), stockList.end(), [stockTargetId](Stock & ref) {return ref.stockId == stockTargetId; });
		total += ref.number * it->currentDollars;
	}
	// �в�
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
