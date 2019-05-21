#pragma once
#include<string>
#include<vector>
#include"Player.h"
using namespace std;
struct Stock;
struct StockRecord;
class Bank
{
public:
	Bank();
	~Bank();
	vector<Stock> stockList;
	vector<vector<StockRecord>> stockOwnerList;
	int computeAsset(Player & p1);

};


struct Stock
{
	int stockId;
	int currentDollars;
	int previousDollars;
	wstring name;
};

struct StockRecord
{
	int player_id;
	int stockId;
	int number;
};
//(1.0 +- rand() % 100 / 1000.0) * currentDollars;
	
