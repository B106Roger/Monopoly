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

void GameWorld::gameStart()
{
	gameBoard.printMap();
	while (true)
	{

	}
}

