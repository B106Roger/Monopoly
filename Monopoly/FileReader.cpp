#include"FileReader.h"
#include"Monopoly.h"
#include"GameWorld.h"

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}

// 重設遊戲參數 全部設為空
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

// ========================================================================
// ============= 印出foldername底下的所有檔案，供使用者選取，並讀檔 =======
// ========================================================================
// 圖像介面取得欲讀取之檔名
wstring FileReader::getFilename(string foldername)
{
	const FS::path absoluteFilename = FS::current_path() / foldername;
	vector<FS::path> fileList = getAllFile(absoluteFilename);
	int fileListSize = (int)fileList.size();
	int index = 0;
	Monopoly::setCursorSize(false, 0);
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
				return fileListSize == 0u ? L"" : fileList[index].filename();
			}
			else if (ch == 27)          // 案Esc鍵後離開
			{
				return L"";
			}
		}
	}
}

// 顯示檔案
void FileReader::displayFolder(const vector<FS::path> & fileList, int index)
{
	// 顯示檔案名稱寬度
	int width = 20, fileListSize = (int)fileList.size();
	// 最多顯示檔案名稱
	int maxmumPrintFile = 6;
	// 決定顯示檔案名稱的index
	int start = 0, end = fileListSize, displayIndex = 0;
	for (; start <= end; start += maxmumPrintFile)
	{
		if (start <= index && index < start + maxmumPrintFile)
		{
			end = start + maxmumPrintFile;
			break;
		}
	}

	for (; start < end; start++, displayIndex++)
	{
		Monopoly::setColor();
		// 印出小框框
		Monopoly::printFrame(startX, startY + 2 * displayIndex, width, 3);
		// 設定游標位置 並清空該欄位
		Monopoly::setCursor(startX + 4, startY + 2 * displayIndex + 1);
		wcout << wstring(width - 3, L'　');
		// 印出檔名，必要時為檔名著色
		index == start ? Monopoly::setColor(0, 15) : Monopoly::setColor();
		Monopoly::setCursor(startX + 4, startY + 2 * displayIndex + 1);
		if (start < fileListSize)
		{
			wcout << fileList[start].filename();
		}
	}
	Monopoly::setColor();
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
// ========================================================================



// ===================================================================
// ========= 讀取、儲存 繼續遊戲的檔案 ===========================================
// ===================================================================
// 讀取 Monopoly::gameRecordFilename ，必須確認Monopoly::gameRecordFilename不為空
void FileReader::readAndSetRecord()
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
				int position;
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
			wstring bankString;
			wstring playerInfoString;
			

			if (in >> bankString)
			{
				in.get();//去除\n 字元

				for (int i = 0; i < numberOfPlayer; i++)
				{
					int playerId,stockId;
					getline(in, line);
					ss.clear();
					ss.str(line);
					ss >> playerId;
					ss >> GameWorld::playerList[playerId].bankBalance;
					ss >> GameWorld::playerList[playerId].debt;
					ss >> GameWorld::playerList[playerId].repamentRound;
					ss >> GameWorld::playerList[playerId].remoteDice;
					ss >> GameWorld::playerList[playerId].stopRound;
					while (ss >> stockId)
					{
						StockRecord tmp;
						tmp.player_id = playerId;
						tmp.stockId = stockId;
						ss >> tmp.number;
						GameWorld::bank.stockOwnerList[playerId].push_back(tmp);
					}
				}
			}
			if (in >> playerInfoString)
			{
				in.get();//去除\n 字元

				for (int i = 0; i < numberOfPlayer; i++)
				{
					int playerId;
					getline(in, line);
					ss.clear();
					ss.str(line);
					ss >> playerId;
					ss >> GameWorld::playerList[playerId].debt;
					ss >> GameWorld::playerList[playerId].repamentRound;
					ss >> GameWorld::playerList[playerId].remoteDice;
					ss >> GameWorld::playerList[playerId].stopRound;
				}
			}
		}
		else wcout << L"fail open " << fileName;
	}
	
}

void FileReader::saveRecord()
{
	if (Monopoly::gameRecordFileName.size() == 0u)
	{
		Monopoly::gameRecordFileName = userInputFileName();
	}
	wofstream out;
	wstring fileanme = continuePath + +L"//" + Monopoly::gameRecordFileName;
	out.open(fileanme);
	if (out.is_open() == false)
	{
		Monopoly::setCursor(0, 0);
		cout << "fail open file\n";
	}

	// 輸出地產資訊
	out << GameWorld::mapName << L" " << GameWorld::reamainRound << " " << GameWorld::playerList.size() << endl;
	for (const auto &ref : GameWorld::gameMap)
	{
		wstring location = to_wstring(ref.position);
		if (location.size() == 1u)
		{
			location.insert(0, 1, L'0');
		}
		out << location << L" " << ref.name << L" " << to_wstring(ref.type) << L" ";
		if (ref.type == 1)
		{
			out << to_wstring(ref.buyCost) << L" ";
			for (auto integer : ref.tolls)
			{
				out << to_wstring(integer) << L" ";
			}
		}
		out << endl;
	}

	// 輸出玩家 現金房產
	out << L"playerstate " << GameWorld::playerState << endl;
	for (auto & player : GameWorld::playerList)
	{
		out << player.id << L" " << player.playerPosition << L" " << to_wstring(player.cash) << L" ";
		for (auto &ref : GameWorld::gameMap)
		{
			if (ref.ownerId == player.id)
			{
				wstring loc = to_wstring(ref.position);
				if (loc.size() == 1u)
				{
					loc.insert(0, 1, L'0');
				}
				out << loc << L" " << to_wstring(ref.level) << L" ";
			}
		}
		out << endl;
	}

	// 輸出玩家 存款房產
	out << L"bank" << endl;
	for (auto & player : GameWorld::playerList)
	{
		out << player.id << L" " << to_wstring(player.bankBalance) << L" ";

		out << to_wstring(player.debt) << L" " << to_wstring(player.repamentRound) << L" ";
		
		out << to_wstring(player.remoteDice) << L" " << player.stopRound << L" ";
		for (auto &ref : Bank::stockOwnerList[player.id])
		{
			if (ref.number == 0)
				continue;
			out << ref.stockId << L" " << to_wstring(ref.number) << L" ";
		}
		out << endl;
	}
	out << L"playerInfo" << endl;
	for (auto & player : GameWorld::playerList)
	{
		out << player.id << L"　";

		out << to_wstring(player.debt) << L" " << to_wstring(player.repamentRound) << L" ";

		out << to_wstring(player.remoteDice) << L" " << player.stopRound << endl;
	}

	out.close();

}

wstring FileReader::userInputFileName()
{
	int menuX = 112, menuY = 6, menuWidth = 16;
	int stringMaxSize = 12;
	
	Monopoly::printFrame(menuX, menuY, menuWidth, 5, L"輸入檔名");
	wstring result;
	Monopoly::setColor(0, 15);
	Monopoly::setCursor(menuX + 4, menuY + 2);
	wcout << left << wstring(12, L'　');
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
			}
			else if (ch == '\r')
			{
				GameWorld::mapName = result;
				result += L".txt";
				return result;
			}
			else if (ch == '\b')
			{
				if (result.size() > 0u)
				{
					result.pop_back();
					Monopoly::setCursor(menuX + 4, menuY + 2);
					wcout << left << result;
				}
			}
			else
			{
				if (result.size() < unsigned(stringMaxSize))
				{
					result.push_back(wchar_t(ch));
					Monopoly::setCursor(menuX + 4, menuY + 2);
					wcout << left << result;
				}
			}
		}
	}
}
// ===================================================================





void FileReader::readAndSetMap()
{
	// 重置GameWorld的參數
	wifstream in;
	wstring fileName = mapPath + L"//" + Monopoly::gameMapFileName, tmpWstr;
	if (fileName.size() != 0u)
	{
		in.open(fileName);
		if (in.is_open() == true)
		{
			int numberOfRealEstate = 28;
			// 取得地產資訊
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


		}
		else wcout << L"fail open " << fileName;
	}
}

void FileReader::previewMap(string foldername)
{
	const FS::path absoluteFilename = FS::current_path() / foldername;
	vector<FS::path> fileList = getAllFile(absoluteFilename);
	// 紀錄當前的地圖檔案名稱
	wstring currenMapFileNmae = Monopoly::gameMapFileName;
	// 顯示目前的地圖
	GameWorld::gameMap.clear();
	readAndSetMap();
	GameWorld::gameBoard.printMap(46, 0);

	int fileListSize = (int)fileList.size();
	int fileIndex = 0, mapIndex = 0;
	displayMapFolder(fileList, fileIndex);
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
					++fileIndex;  mapIndex = 0;
					fileIndex == fileListSize ? (fileIndex = 0) : 0;
				}
				else if (ch == 72)     // 按上
				{
					--fileIndex;  mapIndex = 0;
					fileIndex == -1 ? (fileIndex = fileListSize - 1) : 0;
				}
				
				if (ch == 80 || ch == 72)
				{
					displayMapFolder(fileList, fileIndex);
					Monopoly::gameMapFileName = fileList[fileIndex].filename();
					GameWorld::gameMap.clear();
					GameWorld::gameBoard.clearItemDetail();
					readAndSetMap();
					GameWorld::gameBoard.printMap(46, 0);
				}
				else
				{
					// 將舊的位置 其房產名稱刷新
					GameWorld::gameBoard.printItem(mapIndex, 46, 0);
					if (ch == 75) // 左
					{
						mapIndex--;
						if (mapIndex == -1) mapIndex = 27;
					}
					else if (ch == 77) // 右
					{
						mapIndex++;
						if (mapIndex == 28) mapIndex = 0;
					}
					// 將新的位置 其房產名稱刷新
					GameWorld::gameBoard.printItem(mapIndex, 46, 0, 4);
					GameWorld::gameBoard.printItemDetail(mapIndex);

				}
			}
			else if (ch == '\r')
			{
				Monopoly::gameMapFileName = fileList[fileIndex].filename();
				return ;
			}
			else if (ch == 27)          // 案Esc鍵後離開
			{
				Monopoly::gameMapFileName = currenMapFileNmae;

				FS::path currentFileName(absoluteFilename);
				currentFileName = currentFileName / Monopoly::gameMapFileName;
				if (find(fileList.begin(),fileList.end(), currentFileName) == fileList.end())
				{
					Monopoly::gameMapFileName = L"basemap.txt";
					return;
				}
				else
				{
					return;
				}
				
			}
		}
	}
}

void FileReader::displayMapFolder(const vector<FS::path> & fileList, int index)
{
	int myStartX = 0, myStartY = 0;
	// 顯示檔案名稱寬度
	int width = 20, fileListSize = (int)fileList.size(), height = 5;
	// 最多顯示檔案名稱
	int maxmumPrintFile = 10;
	// 決定顯示檔案名稱的index
	int start = 0, end = fileListSize, displayIndex = 0;
	for (; start < end; start += maxmumPrintFile)
	{
		if (start <= index && index < start + maxmumPrintFile)
		{
			end = start + maxmumPrintFile;
			break;
		}
	}

	for (; start < end; start++, displayIndex++)
	{
		Monopoly::setColor();
		// 印出小框框
		Monopoly::printFrame(myStartX, myStartY + (height - 1) * displayIndex, width, height);
		// 設定游標位置 並清空該欄位
		Monopoly::setCursor(myStartX + 4, myStartY + (height-1) * displayIndex + (height/2));
		wcout << wstring(width - 3, L'　');
		// 印出檔名，必要時為檔名著色
		index == start ? Monopoly::setColor(0, 15) : Monopoly::setColor();
		Monopoly::setCursor(myStartX + 4, myStartY + (height - 1) * displayIndex + (height / 2));
		if (start < fileListSize)
		{
			wcout << fileList[start].filename();
		}
	}
}
