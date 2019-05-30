#include"FileReader.h"
#include"Monopoly.h"
#include"GameWorld.h"

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}

// Ū�� Monopoly::gameRecordFilename �A�����T�{Monopoly::gameRecordFilename������
void FileReader::readAndSetData()
{
	// ���mGameWorld���Ѽ�
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
			wstring bankString;

			

			if (in >> bankString)
			{
				in.get();//�h��\n �r��

				for (int i = 0; i < numberOfPlayer; i++)
				{
					int playerId, balance,stockId;
					getline(in, line);
					ss.clear();
					ss.str(line);
					ss >> playerId;
					ss >> GameWorld::playerList[playerId].bankBalance;
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

		}
		else wcout << L"fail open " << fileName;
	}
	
}

// ���]�C���Ѽ�
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
				if (ch == 80)          // ���U
				{
					++index;
					index == fileListSize ? (index = 0) : 0;
				}
				else if (ch == 72)     // ���W
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
			else if (ch == 27)          // ��Esc������}
			{
				Monopoly::gameRecordFileName = L"";
				return false;
			}
		}
	}
}

// ����ɮ�
void FileReader::displayFolder(const vector<FS::path> & fileList, int index)
{
	// ����ɮצW�ټe��
	int width = 20, fileListSize = (int)fileList.size();
	// �̦h����ɮצW��
	int maxmumPrintFile = 6;
	// �M�w����ɮצW�٪�index
	int start = 0, end = fileListSize, displayIndex = 0;
	for (; start < end; start+= maxmumPrintFile)
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
		// �L�X�p�خ�
		Monopoly::printFrame(startX, startY + 2 * displayIndex, width, 3);
		// �]�w��Ц�m �òM�Ÿ����
		Monopoly::setCursor(startX + 4, startY + 2 * displayIndex + 1);
		wcout << wstring(width - 3, L'�@');
		// �L�X�ɦW�A���n�ɬ��ɦW�ۦ�
		index == start ? Monopoly::setColor(0, 15) : Monopoly::setColor();
		Monopoly::setCursor(startX + 4, startY + 2 * displayIndex + 1);
		if (start < fileListSize)
		{
			wcout << fileList[start].filename();
		}
	}
}

// ���w��Ƨ��W�١A���o�ӥؿ����U���ɮ�
vector<FS::path> FileReader::getAllFile(const FS::path & ps)
{
	vector<FS::path> fileList;
	// �p�G�o���O��Ƨ��N���X
	if (FS::is_regular_file(ps))
	{
		return fileList;
	}
	// �����Ƨ��U�Ҧ����ɮשθ�Ƨ�
	for (FS::directory_iterator it(ps); it != FS::directory_iterator(); it++)
	{
		fileList.push_back(it->path());
	}
	return fileList;
}

void FileReader::saveFile()
{
	if (Monopoly::gameRecordFileName.size() == 0u)
	{
		//Monopoly::gameRecordFileName = actionBoard.userInputFileName();
	}
	wofstream out;
	wstring fileanme = continuePath + +L"//" + Monopoly::gameRecordFileName;
	out.open(fileanme);
	if (out.is_open() == false)
	{
		Monopoly::setCursor(0, 0);
		cout << "fail open file\n";
	}
	out << GameWorld::mapName << L" " << GameWorld::reamainRound << " " << GameWorld::playerList.size() << endl;
	for (const auto &ref: GameWorld::gameMap)
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

	out << L"bank" << endl;
	for (auto & player : GameWorld::playerList)
	{
		out << player.id << L" " << to_wstring(player.bankBalance) << L" ";
		for (auto &ref : Bank::stockOwnerList[player.id])
		{
			if (ref.number == 0)
				continue;
			out << ref.stockId << L" " << to_wstring(ref.number) << L" ";
		}
		out << endl;
	}
	out.close();

}