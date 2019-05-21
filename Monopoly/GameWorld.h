#pragma once
#include "Player.h"
#include"Bank.h"
#include"GameBoard.h"
#include"ConsoleBoard.h"
#include"ActionBoard.h"
struct RealEstate;
struct Chance;
class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void gmaeStart();

	
	static vector<Player> playerList;
	static Bank bank;               // PlayerId = -1
	static vector<RealEstate> gameMap;
	static int playerState;         // 目前倫到哪個玩家
	static vector<Chance> chanceList;
	static vector<Chance> destinyList;
	int round;                      // 第幾回合
	int obstaclePosition;     // 為路障位置 
	//display static data member
	static GameBoard gameBoard;
	static ActionBoard actionBoard;
	static ConsoleBoard consoleBoard;

};

struct RealEstate
{
	RealEstate()
	{
		playerPosition = "0000";  // 以0/1字串表示玩家是否在此地
		ownerId = -1;             // 當作是銀行的
		level = 0;
	}
	int type;          // 類型 1地產, -1 機會
	int position;      // 0~27
	int ownerId;       // Player1
	wstring name;      // 地產名稱
	int buyCost;       // 土地價格
	
	vector<int> tolls; // 過路費(一律給現金)
	int level;         // 物產等級 0 ~ 3
	string playerPosition;
	int mortgageRealEstate()
	{
		ownerId = -1;
		level = 0;
		double rate = 0.75;
		int returnVal = buyCost;
		for (int i = 0; i < level; i++)
		{
			returnVal += buyCost * rate;
			rate += 0.25;
		}
		return returnVal * 0.8;
	}
};

struct Chance
{
	string message;
	int type;     // 0: +-$, 1: 遙控色子, 2:暫停回合
	int number;   // 依據type有不同的效果
};