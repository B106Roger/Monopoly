#pragma once
#include "Player.h"
#include"Bank.h"
#include"GameBoard.h"
#include"ConsoleBoard.h"
#include"ActionBoard.h"
#include"Player.h"
struct RealEstate;
struct Chance;
class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void gameStart();
	// mode 
	int mode;
	static wstring mapName;
	static vector<Player> playerList; // ���a�C��
	static Bank bank;                 // �Ȧ� PlayerId = -1
	static vector<RealEstate> gameMap;// �C���a�ϸ�T
	static int playerState;           // �ثe�ۨ���Ӫ��a
	static vector<Chance> chanceList; // ���|�C��  
	static vector<Chance> destinyList;// �R�B�C��
	static int reamainRound;          // �Ѿl�^�X��
	static int obstaclePosition;      // �����٦�m 
	//display static data member
	static GameBoard gameBoard;       // �t�d�a�Ϫ����
	static ActionBoard actionBoard;   // �t�d���a�ާ@���������
	static ConsoleBoard consoleBoard; // �t�dconsole��r�����

};

struct RealEstate
{
	RealEstate()
	{
		// �h��PlayerPostion �]���C�����l�n��player �ثe����m���n��
		ownerId = -1;             // ��@�O�Ȧ檺
		level = 0;
		tolls.resize(4);
	}
	int type;          // ���� 1�a��, -1 ���|
	int position;      // 0~27
	int ownerId;       // ������id(���aid)
	wstring name;      // �a���W��
	int buyCost;       // �a������
	vector<int> tolls; // �L���O(�@�ߵ��{��)
	int level;         // �������� 0 ~ 3
	
	int mortgageRealEstate()
	{
		ownerId = -1;
		level = 0;
		double rate = 0.75;
		int returnVal = buyCost;
		for (int i = 0; i < level; i++)
		{
			returnVal += int(buyCost * rate);
			rate += 0.25;
		}
		return int(returnVal * 0.8);
	}
};

struct Chance
{
	string message;
	int type;     // 0: +-$, 1: ������l, 2:�Ȱ��^�X
	int number;   // �̾�type�����P���ĪG
};