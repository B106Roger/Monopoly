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
	vector<Stock> stockList;                   // 布
	vector<vector<StockRecord>> stockOwnerList;// 產Τ布
	int computeAsset(Player & p1);             // 璸衡產羆戈玻
	void stockUpate();                         // 穝布虫基
};


struct Stock                 // 布戈
{
	int stockId;
	int currentDollars;
	int previousDollars;
	wstring name;
};

struct StockRecord           // 產┮Τ布籔癸琈眎计
{
	int player_id;
	int stockId;
	int number;
};
//(1.0 +- rand() % 100 / 1000.0) * currentDollars;
	
