#pragma once
#include "Player.h"
class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void gmaeStart();


	static vector<Player> playerList;
	static Player Bank;               // PlayerId = -1
	static vector<realEstate> gameMap;
	// StockDepartment   Stock
	// RealEstateDepartment    RealEstate
};

struct realEstate
{
	realEstate()
	{
		playerPosition = "0000";  // 以0/1字串表示玩家是否在此地
		ownerId = -1;             // 當作是銀行的
	}
	int type;
	int position; // 0~27
	int ownerId;
	wstring name;
	int buyCose;
	vector<int> updateCost;
	string playerPosition;
};