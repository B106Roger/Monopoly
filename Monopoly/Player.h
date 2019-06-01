#pragma once
#include<string>
#include<vector>
using namespace std;
class Player
{
public:
	Player();
	~Player();
	wstring name;				// 玩家名稱
	int id;						// 玩家id，-1：破產時為-1
	int cash;					// 玩家現金
	int bankBalance;			// 玩家存款
	int stopRound;				// 玩家停止移動的剩餘回合數
	int playerPosition;			// 玩家所在地
	int remoteDice;				// 遙控色子數量// 新遊戲每人免費贈送遙控色子
	bool withdraw(int dollars);	// 提款
	bool deposit(int dollars);	// 存款

};
