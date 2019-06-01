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
	//void setNewGame();
	void initGameWorld(int numberOfPlayer);

	// mode 
	int mode;
	static wstring mapName;
	static vector<Player> playerList; // 玩家列表
	static Bank bank;                 // 銀行 PlayerId = -1
	static vector<RealEstate> gameMap;// 遊戲地圖資訊
	static int playerState;           // 目前倫到哪個玩家
	static vector<Chance> chanceList; // 機會列表  
	static vector<Chance> destinyList;// 命運列表
	static int reamainRound;          // 剩餘回合數
	static int obstaclePosition;      // 為路障位置 
	//display static data member
	static GameBoard gameBoard;       // 負責地圖的顯示
	static ActionBoard actionBoard;   // 面的顯示
	static ConsoleBoard consoleBoard; // 負責consol負責玩家操作介e文字的顯示
	
	static void getChanceList();
	static void getDestinyList();
private:

	// 擲骰子階段
	// ============================================
	void diceStage();
	void playDiceAni(int diceNum, bool playAni);
	void playerWalkAni(int distance);
	void playerLocation();		// 判斷玩家所在位置與對應動作
	void drawAChance();			// 走到機會時呼叫
	void drawADestiny();			// 走到命運時呼叫
	void bankruptcy();          // 破產時，將房產清
	
	vector<vector<wstring>> diceImages;
	// ============================================

	// 更新路障
	void updateObstacle();

	// 遊戲結束時要做的判斷
	// ============================================
	bool isAllBankrupt();			// 是否n-1家都破產
	int getRichestPlayer();         // 找最有錢的玩家id
};

struct RealEstate
{
	RealEstate()
	{
		// 去掉PlayerPostion 因為每次骰色子要找player 目前的位置不好找
		ownerId = -1;             // 當作是銀行的
		level = 0;
		tolls.resize(4);
		rate = { 0.75, 1.0, 1.25 };
	}
	int type;          // 類型 1地產, -1 機會
	int position;      // 0~27
	int ownerId;       // 持有者id(玩家id)
	wstring name;      // 地產名稱
	int buyCost;       // 地產價格
	vector<int> tolls; // 過路費(一律給現金)
	int level;         // 物產等級 0 ~ 3
	vector<double> rate;

	int mortgageRealEstate()
	{
		ownerId = -1;
		level = 0;
		int returnVal = buyCost;
		for (int i = 0; i < level; i++)
		{
			returnVal += int(buyCost * rate[i]);
		}
		return int(returnVal * 0.8);
	}
};

struct Chance
{
	wstring message;
	int type;     // 0: +-$, 1: 遙控色子, 2:暫停回合
	int number;   // 依據type有不同的效果
};