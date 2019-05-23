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
	vector<Stock> stockList;                   // �Ѳ��C��
	vector<vector<StockRecord>> stockOwnerList;// ���a�����Ѳ�
	int computeAsset(Player & p1);             // �p�⪱�a�`�겣
	void stockUpate();                         // ��s�Ѳ����
};


struct Stock                 // �s�Ѳ����
{
	int stockId;
	int currentDollars;
	int previousDollars;
	wstring name;
};

struct StockRecord           // �s���a�ҫ����Ѳ��P��M�i��
{
	int player_id;
	int stockId;
	int number;
};
//(1.0 +- rand() % 100 / 1000.0) * currentDollars;
	
