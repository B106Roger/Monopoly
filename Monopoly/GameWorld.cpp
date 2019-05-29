#include "GameWorld.h"
#include"Monopoly.h"
#include<fstream>
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
	chanceList.clear();
	destinyList.clear();
}

// 遊戲迴圈
void GameWorld::gameStart()
{
	Monopoly::setCursorSize(false, 0);
	gameBoard.printMap();
	actionBoard.printFrame();
	int initialPlayer =  playerState;
	while (true)
	{																								
		int actionMode = actionBoard.getMenuOption();
		switch (actionMode)
		{
		case 0:                       // 玩家資訊
		{
			actionBoard.printPlayerInfo();
			break;
		}
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
			if (gameMap[playerList[playerState].playerPosition].type == -1) {
				drawADestiny();
			}
			else if (gameMap[playerList[playerState].playerPosition].type == -2) {
				drawAChance();
			}
			playerState++;
			playerState %= 4;
			break;
		}
		}

		if (playerState == initialPlayer)
		{
			bank.stockUpate();
		}

	}
}

void GameWorld::getChanceList()
{
	wifstream file;
	file.open(L"Chance.txt");
	if (file.is_open())
	{
		wstring message;
		int type, number;
		while (file >> message) {
			Chance tmp;
			tmp.message = message;
			file >> type >> number;
			tmp.type = type;
			tmp.number = number;
			chanceList.push_back(tmp);
		}
	}
}

void GameWorld::getDestinyList()
{
	wifstream file;
	file.open("Destiny.txt");
	if (file.is_open()) {
		wstring message;
		int type, number;
		while (file >> message) {
			Chance tmp;
			tmp.message = message;
			file >> type >> number;
			tmp.type = type;
			tmp.number = number;
			destinyList.push_back(tmp);
		}
	}
}

void GameWorld::drawAChance()
{
	srand(time(NULL));
	int index = rand() % chanceList.size();
	actionBoard.printChance(index);
	if (chanceList[index].type == 0) {
		playerList[playerState].cash += chanceList[index].number;
	}
	else if (chanceList[index].type == 1) {
		playerList[playerState].remoteDice += chanceList[index].number;
	}
	else if (chanceList[index].type == 2) {
		playerList[playerState].stopRound += chanceList[index].number;
	}
}

void GameWorld::drawADestiny()
{
	srand(time(NULL));
	int index = rand() % destinyList.size();
	actionBoard.printDestiny(index);
	if (destinyList[index].type == 0) {
		playerList[playerState].cash += destinyList[index].number;
	}
	else if (destinyList[index].type == 1) {
		playerList[playerState].remoteDice += destinyList[index].number;
	}
	else if (destinyList[index].type == 2) {
		playerList[playerState].stopRound += destinyList[index].number;
	}
}

