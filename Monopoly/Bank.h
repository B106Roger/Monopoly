#pragma once
#include<string>
#include<vector>
#include"Player.h"
using namespace std;
class Bank
{
public:
	Bank();
	~Bank();
	vector<Stock> stockList;
	int computeAsset(Player & p1);
};


struct Stock
{
	int id;
	int currentDollars;
	int previousDollars;
	wstring name;
};


//(1.0 + rand() % 100 / 1000.0) * currentDollars;
	
