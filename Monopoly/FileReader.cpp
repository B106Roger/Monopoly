#include"FileReader.h"
#include"Monopoly.h"
#include"GameWorld.h"

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}

// 讀取 Monopoly::gameRecordFilename ，必須確認Monopoly::gameRecordFilename不為空
void FileReader::readAndSetData()
{
	// 重置GameWorld的參數
	resetAllData();
	wifstream in;
	wstring fileName = continuePath + L"//" + Monopoly::gameRecordFileName,tmpWstr;
	if (fileName.size() != 0u)
	{
		in.open(fileName);
		if (in.is_open() == true)
		{
			int numberOfRealEstate = 28;
			int numberOfPlayer = 0;
			// 取得地產資訊
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
			// 取得玩家現金地產資訊
			in.get(); //去除\n 字元
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
		else wcout << L"fail open " << fileName;
	}
	
}

// 重設遊戲參數
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


bool FileReader::getFilename(string foldername)
{
	const FS::path absoluteFilename = FS::current_path() / foldername;
	vector<FS::path> fileList = getAllFile(absoluteFilename);
	int fileListSize = (int)fileList.size();
	int index = 0;
	displayFolder(fileList, index);
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				if (ch == 80)          // 按下
				{
					++index;
					index == fileListSize ? (index = 0) : 0;
				}
				else if (ch == 72)     // 按上
				{
					--index;
					index == -1 ? (index = fileListSize - 1) : 0;
				}
				displayFolder(fileList, index);
			}
			else if (ch == '\r')
			{
				Monopoly::gameRecordFileName = fileList[index].filename();
				return true;
			}
			else if (ch == 27)          // 案Esc鍵後離開
			{
				Monopoly::gameRecordFileName = L"";
				return false;
			}
		}
	}
}

// 顯示檔案
void FileReader::displayFolder(const vector<FS::path> & fileList, int index)
{
	int width = 20, fileListSize = (int)fileList.size();
	int maxmumPrintFile = 6;
	// 決定顯示欄位的index
	int start = index, end = fileListSize - 1,displayIndex = 0;
	if (end - start >= maxmumPrintFile)
	{
		end = start + maxmumPrintFile;
	}
	else if (end - start < maxmumPrintFile)
	{
		start = end - maxmumPrintFile;
		if (start < 0)
		{
			start = 0;
		}
	}

	for (; start <= end; start++, displayIndex++)
	{
		Monopoly::printFrame(startX, startY + 2 * displayIndex, width, 3);
		Monopoly::setCursor(startX + 4, startY + 2 * displayIndex + 1);
		index == start ? Monopoly::setColor(0, 15) : Monopoly::setColor();
		wcout << fileList[start].filename();
	}
}

// 給定資料夾名稱，取得該目錄底下的檔案
vector<FS::path> FileReader::getAllFile(const FS::path & ps)
{
	vector<FS::path> fileList;
	// 如果這不是資料夾就跳出
	if (FS::is_regular_file(ps))
	{
		return fileList;
	}
	// 獲取資料夾下所有的檔案或資料夾
	for (FS::directory_iterator it(ps); it != FS::directory_iterator(); it++)
	{
		fileList.push_back(it->path());
	}
	return fileList;
}