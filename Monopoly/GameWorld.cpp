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


GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::gameStart()
{
	
}

