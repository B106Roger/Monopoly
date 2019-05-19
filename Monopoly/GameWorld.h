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
		playerPosition = "0000";  // �H0/1�r���ܪ��a�O�_�b���a
		ownerId = -1;             // ��@�O�Ȧ檺
	}
	int type;
	int position; // 0~27
	int ownerId;
	wstring name;
	int buyCose;
	vector<int> updateCost;
	string playerPosition;
};