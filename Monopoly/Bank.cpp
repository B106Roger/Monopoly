#include "Bank.h"
vector<Stock> Bank::stockList;


Bank::Bank()
{
	initialStock();
}


Bank::~Bank()
{
}

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

