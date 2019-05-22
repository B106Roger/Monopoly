#include"FileReader.h"
#include"Monopoly.h"
#include"GameWorld.h"
#include <sstream>


FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

void FileReader::readAndSetMap()
{
	wifstream in;
	wstring fileName = Monopoly::gameMapFileName,tmpWstr;
	if (fileName.size() != 0u)
	{
		cout << 123;
		in.open(fileName);
		if (in.is_open() == true)
		{
			cout << 123;

			int numberOfRealEstate = 0;
			int numberOfPlayer = 0;
			// 取得地產資訊
			in >> GameWorld::mapName;
			in >> numberOfRealEstate;
			in >> numberOfPlayer;
			while (numberOfRealEstate--)
			{
				RealEstate tmp;
				in >> tmp.position;
				in >> tmp.name;
				in >> tmp.type;
				in >> tmp.buyCost;
				in >> tmp.tolls[0];
				in >> tmp.tolls[1];
				in >> tmp.tolls[2];
				in >> tmp.tolls[3];
				GameWorld::gameMap.push_back(tmp);
			}
			in >> tmpWstr;
			in >> GameWorld::playerState;
			// 取得玩家現金地產資訊
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
			// 取得玩家存款股票資訊
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
