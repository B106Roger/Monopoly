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
	static vector<Stock> stockList;                   // 股票列表
	vector<vector<StockRecord>> stockOwnerList;// 玩家持有股票
	int computeAsset(Player & p1);             // 計算玩家總資產
	void stockUpate();                         // 更新股票單價
private:
	static void initialStock();			//用於初始化股票資訊
};

struct Stock                 // 存股票資料
{
	int stockId;
	int currentDollars;
	int previousDollars;
	wstring name;
};

struct StockRecord           // 存玩家所持有股票與對映張數
{
	int player_id;
	int stockId;
	int number;
};
//(1.0 +- rand() % 100 / 1000.0) * currentDollars;
	
