#include"FileReader.h"
#include"Monopoly.h"
#include"GameWorld.h"
#include<codecvt>
#include<locale>
#include <sstream>


FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}

void FileReader::readAndSetData()
{
	resetAllData();
	wifstream in;
	wstring fileName = Monopoly::gameMapFileName,tmpWstr;
	if (fileName.size() != 0u)
	{
		in.open(fileName);
		//in.imbue(loc);
		if (in.is_open() == true)
		{
			int numberOfRealEstate = 28;
			int numberOfPlayer = 0;
			// ���o�a����T
			in >> GameWorld::mapName;
			in >> GameWorld::reamainRound;
			in >> numberOfPlayer;
			while (numberOfRealEstate--)
			{
				RealEstate tmp;
				in >> tmp.position;
				in >> tmp.name;
				in >> tmp.type;
				if (tmp.type == 1)
				{
					in >> tmp.buyCost;
					in >> tmp.tolls[0];
					in >> tmp.tolls[1];
					in >> tmp.tolls[2];
					in >> tmp.tolls[3];
				}
				GameWorld::gameMap.push_back(tmp);
			}
			in >> tmpWstr;
			in >> GameWorld::playerState;
			// ���o���a�{���a����T
			in.get(); //�h��\n �r��
			wstring line;
			wstringstream ss;
			for (int i = 0; i < numberOfPlayer; i++)
			{
				Player tmp;
				int position, level;
				getline(in, line);
				ss.clear();
				ss.str(line);
				ss >> tmp.id;
				ss >> tmp.playerPosition;
				ss >> tmp.cash;
				while (ss >> position)
				{
					GameWorld::gameMap[position].ownerId = tmp.id;
					ss >> GameWorld::gameMap[position].level;
				}
				GameWorld::playerList.push_back(tmp);
				GameWorld::bank.stockOwnerList.push_back(vector<StockRecord>());
			}
			// ���o���a�s�ڪѲ���T
			if (in >> line)
			{
				for (int i = 0; i < numberOfPlayer; i++)
				{
					int playerId, balance,stockId;
					getline(in, line);
					ss.clear();
					ss << line;
					ss >> playerId;
					ss >> GameWorld::playerList[playerId].bankBalance;
					while (ss >> stockId)
					{
						StockRecord tmp;
						tmp.player_id = playerId;
						tmp.stockId = stockId;
						in >> tmp.number;
						GameWorld::bank.stockOwnerList[playerId].push_back(tmp);
					}
				}
			}

		}
	}
	
}

void FileReader::resetAllData()
{
	GameWorld::mapName = L"";
	GameWorld::playerList.resize(0);
	GameWorld::bank.stockOwnerList.resize(0);
	GameWorld::gameMap.resize(0);
	GameWorld::playerState = -1;
	GameWorld::reamainRound = 0;
	GameWorld::obstaclePosition = -1;
}