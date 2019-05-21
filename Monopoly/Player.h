#pragma once
#include<string>
#include<vector>
using namespace std;
class Player
{
public:
	Player();
	~Player();


	wstring name;
	int id;
	int cash;
	int bankBalance;
	int stopRound;            //玩家停止移動的剩餘回合數
	int withdraw(int dollars);
	int deposit(int dollars);
	// int buyStock(Stock & stock, int number);
	// int soldStock(Stock& stock, int number);
};
