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

// �C���j��
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
		case 0:                       // ���a��T
			break;
		case 1:                       // �s��
			break;
		case 2:                       // ����
			break;
		case 3:                       // �Ѳ��}�L
			actionBoard.printStock();
			system("PAUSE");
			break;
		case 4:                       // �R�Ѳ�
			break;
		case 5:                       // ��Ѳ�
			break;
		case 6:                       // �Y��l
			// �P�_�ण��Ȼ몺function
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

