#include "GameWorld.h"
#include"Monopoly.h"
vector<Player> GameWorld::playerList;
Bank GameWorld::bank;
vector<RealEstate> GameWorld::gameMap;
int GameWorld::playerState;
vector<Chance> GameWorld::chanceList;
vector<Chance> GameWorld::destinyList;
GameBoard GameWorld::gameBoard;
ActionBoard GameWorld::actionBoard;
ConsoleBoard GameWorld::consoleBoard;
wstring GameWorld::mapName;
int GameWorld::reamainRound;
int GameWorld::obstaclePosition;

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

// 遊戲迴圈
void GameWorld::gameStart()
{
	Monopoly::setCursorSize(false, 0);
	gameBoard.printMap();
	actionBoard.printFrame();
	while (true)
	{
		int actionMode = actionBoard.getMenuOption();
		switch (actionMode)
		{
		case 0:                       // 玩家資訊
			actionBoard.printPlayerInfo();
			break;
		case 1:                       // 存款
		{
			int number = actionBoard.printWithdrawDeposit(false);
			playerList[playerState].deposit(number);
			break;
		}
		case 2:                       // 提款
		{
			int number = actionBoard.printWithdrawDeposit(true);
			playerList[playerState].withdraw(number);
			break;
		}
		case 3:                       // 股票開盤
		{
			actionBoard.printStock();
			system("pause>nul");
			break;
		}
		case 4:                       // 買股票
		{
			vector<int> numberOfStock = actionBoard.printBuyStock();
			playerList[playerState].bankBalance -= bank.buyStock(playerList[playerState], numberOfStock);
			break;
		}
		case 5:                       // 賣股票
		{
			vector<int> numberOfStock = actionBoard.printSellStock();
			playerList[playerState].bankBalance += bank.soldStock(playerList[playerState], numberOfStock);
			break;
		}

		case 6:                       // 擲骰子
		{
			// 判斷能不能值骰的function
			int distance = rand() % 6 + 1;
			for (int i = distance; i != 0; --i)
			{
				int & playerPosition = playerList[playerState].playerPosition;
				int oldPosition = playerPosition++;
				playerPosition %= 28;
				gameBoard.printItem(oldPosition);
				gameBoard.printItem(playerPosition);
				Sleep(200);
			}
			playerState++;
			playerState %= 4;
			break;
		}
		}
	}
}

