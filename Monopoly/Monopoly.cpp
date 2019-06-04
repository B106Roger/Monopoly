#include "Monopoly.h"

wstring Monopoly::musicFileName;
wstring Monopoly::gameMapFileName;
wstring Monopoly::settingFileName;
wstring Monopoly::gameRecordFileName;
GameWorld Monopoly::gameWorld;
FileReader Monopoly::fileReader;

Monopoly::Monopoly()
{
	srand(time(NULL));
	setCursorSize(false, 0);
	monopolyInit();
	GameWorld::getChanceList();
	GameWorld::getDestinyList();
}

Monopoly::~Monopoly()
{
}
void Monopoly::monopolyInit()
{
	musicFileName = L"";
	gameMapFileName = L"basemap.txt";
	settingFileName = L"";
	gameRecordFileName = L"";
	settingMode = 0;
	mode = 0;
}

// 主選單Loop
void Monopoly::monopolyLoop()
{
	system("CLS");
	/*mode = 0;
	monopolyInit();
	fileReader.readAndSetData();
	while (mode != 3)
	{
		if (mode == 0)
		{
			gameWorld.gameStart();
		}
		else if (mode == 1)
		{
			// Setting code
		}
		else if (mode == 2)
		{
			// Detail code
		}
	}*/
	
	// Step1 : 印初始動畫
	if (isFirstStart) {
		printArt();
	}
	// Step2 : 印選單
	wstring title = L"";
	printBoard(boardX, boardY);
	isFirstStart = false;
	// Step3 : 讓玩家選擇

	while (true) {
		if (_kbhit())
		{
			int ch = _getch();
			// 按下Enter鍵後
			if (ch == '\r')
			{
				setCursorSize(true, 0); // 歸還游標
				if (mode == 0)
				{
					// 玩家人數選單
					int numberOfPlayer = 4;
					clearFrame();
					gameWorld.initGameWorld(numberOfPlayer);
					fileReader.readAndSetMap();
					gameWorld.gameStart(/*playerAmount*/); // 進入遊戲，打算傳入遊玩人數
				}
				else if (mode == 1)
				{
					// Continue，進入選單(another loop)
					wstring tmpGameRecordFileName = fileReader.getFilename("continue");
					if (tmpGameRecordFileName.size() == 0u)
					{
						continue;
					}
					else
					{
						gameRecordFileName = tmpGameRecordFileName;
						fileReader.readAndSetRecord();   // 讀取遊戲
						clearFrame();
						gameWorld.gameStart();
					}
					
				}
				else if (mode == 2)
				{
					printRule();
					system("pause>nul");
					// Rule，規則畫面
				}
				else if (mode == 3) {
					setting();
					//printSettingBoard(boardX, boardY);
					// Setting，設定選單(another loop)
				}
				else if (mode == 4) {
					// Exit，break
					exitArt();
					break;
				}
				clearFrame();
				printArt();
				printBoard(boardX, boardY);
			}
			// 按下方向鍵後
			else if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: // 上
					if (mode == 0) mode = 4;
					else mode--;
					break;
				case 80: // 下
					if (mode == 4) mode = 0;
					else mode++;
					break;
				};
				//printWordWide(wordX, wordY, wordWidth, wordHeight); // 更新已選取選項位置
				printWord(boardX, boardY);
			}
		}
	}
}



void Monopoly::printBoard(int xpos, int ypos) {
	setCursorSize(false, 0);
	setColor(9, 0);
	int lineWidth = 2;
	for (int i = 0; i < boardHeight; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < boardWidth; j++) {
			if (i == 0 || i == boardHeight - 1 || i % lineWidth == 0) // 上
			{
				if (j == 0) wcout << L"●";// 左上角
				else if (j == boardWidth - 1) wcout << L"●";// 右上角
				else wcout << L"＝";// 上方
			}
			else// 中
			{
				if (j == 0 || j == boardWidth - 1) wcout << L"∥";// 中間
				else wcout << L"　"; // 
			}
		}
	}
	setColor();
	/*wordX = boardX + 2; // 減邊框
	wordY = boardY + 1; // 減邊框
	wordWidth = boardWidth - 2; // 減邊框長度
	wordHeight = (boardHeight - (modeAmount + 1)) / modeAmount; // 算出單格長度
	printWordWide(wordX, wordY, wordWidth, wordHeight);*/
	printWord(boardX, boardY);
}



// 印出主選單選項(細版)
void Monopoly::printWord(int xpos, int ypos) {
	setColor();
	wstring mainMenu[] = { L"開始遊戲", L"繼續遊戲", L"規則說明", L"遊戲設定", L"離開遊戲" };
	ypos += 1;

	for (int i = 0; i < 5; i++) {
		if (mode == i) setColor(0, 15);
		else setColor();
		int xShift = xpos + boardWidth / 2 + mainMenu[i].length();
		Monopoly::setCursor(xShift, ypos + i * 2);
		wcout << mainMenu[i];
	}


	setColor();
}

// 印出主選單選項(寬版)
void Monopoly::printWordWide(int xpos, int ypos, int width, int height) {
	
	setColor();

	
	if (mode == 0) setColor(0, 15);
	else setColor();
	for (int i = 0; i < height; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < width; j++) {
			wcout << L"　";
		}
	}
	Monopoly::setCursor(xpos + 12, ypos + 2);
	wcout << L"開始遊戲";



	
	if (mode == 1) Monopoly::setColor(0, 15);
	else setColor();
	ypos += 6;
	for (int i = 0; i < height; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < width; j++) {
			wcout << L"　";
		}
	}
	ypos -= 6;
	Monopoly::setCursor(xpos + 12, ypos + 8);
	wcout << L"繼續遊戲";

	
	if (mode == 2) setColor(0, 15);
	else setColor();
	ypos += 12;
	for (int i = 0; i < height; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < width; j++) {
			wcout << L"　";
		}
	}
	ypos -= 12;
	Monopoly::setCursor(xpos + 12, ypos + 14);
	wcout << L"規則說明";

	
	if (mode == 3) setColor(0, 15);
	else setColor();
	ypos += 18;
	for (int i = 0; i < height; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < width; j++) {
			wcout << L"　";
		}
	}
	ypos -= 18;
	Monopoly::setCursor(xpos + 12, ypos + 20);
	wcout << L"遊戲設定";

	
	if (mode == 4) setColor(0, 15);
	else setColor();
	ypos += 24;
	for (int i = 0; i < height; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < width; j++) {
			wcout << L"　";
		}
	}
	ypos -= 24;
	Monopoly::setCursor(xpos + 12, ypos + 26);
	wcout << L"離開遊戲";

	setColor();

}

// 印出開頭背景
void Monopoly::printArt() {
	fstream inputMonopoly("art/monopoly.txt", ios::in);
	fstream inputMoney("art/fadatsai.txt", ios::in);
	setCursorSize(false, 0);

	string line;
	int yPos = 3;

	setColor(6, 0);
	while (getline(inputMonopoly, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
	}


	yPos = 3;
	setColor(6, 0);
	while (getline(inputMoney, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
	}

	inputMonopoly.close();
	inputMoney.close();
	setColor();
}

// 印出開頭背景，有特效
void Monopoly::printArtSleep() {
	fstream inputMonopoly("art/monopoly.txt", ios::in);
	fstream inputMoney("art/fadatsai.txt", ios::in);
	setCursorSize(false, 0);

	string line;
	int yPos = 3;

	setColor(6, 0);
	while (getline(inputMonopoly, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
		Sleep(100);
	}


	yPos = 3;
	setColor(6, 0);
	while (getline(inputMoney, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
		Sleep(100);
	}

	inputMonopoly.close();
	inputMoney.close();
	setColor();
}

// 清空畫面
void Monopoly::clearFrame() {
	setColor();
	for (int i = 0; i < 49; i++) {
		setCursor(0, i);
		for (int j = 0; j < 188; j++) {
			wcout << L"　";
		}
	}

}

void Monopoly::printRule()
{
	clearFrame();
	setCursor(startX + 80, startY + 3);
	wcout << L"規則說明";
	wfstream fileRule("rule.txt", ios::in);
	wstring line;
	int xPos = startX + 25, yPos = startY + 5;
	while (fileRule >> line) {
		setCursor(xPos, yPos);
		wcout << line;
		yPos += 2;
	}
}

void Monopoly::exitArt()
{
	clearFrame();
	string line;
	setColor(6, 0);
	for (int i = 0; i < 10; i++) {
		fstream file1("exitArt/1.txt", ios::in);
		fstream file2("exitArt/2.txt", ios::in);
		fstream file3("exitArt/3.txt", ios::in);
		fstream file4("exitArt/4.txt", ios::in);
		fstream file5("exitArt/5.txt", ios::in);
		fstream file6("exitArt/6.txt", ios::in);
		fstream file7("exitArt/7.txt", ios::in);
		fstream file8("exitArt/8.txt", ios::in);
		setCursorSize(false, 0);
		int yPos = 3;
		while (getline(file1, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file2, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file3, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file4, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file5, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file6, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file7, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
		yPos = 3;
		while (getline(file8, line)) {
			setCursor(3, yPos);
			cout << line << endl;
			yPos++;
		}
	}
	clearFrame();
	setColor();
	fstream theEnd("exitArt/theEnd.txt", ios::in);
	setCursor(3, 10);
	int yPos = 3;
	while (getline(theEnd, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
	}
	Sleep(3000);
	clearFrame();
	setCursor(30, 10);
	wstring end = L"製作團隊：洪偉傑、林奕辰、謝維毅感謝您的遊玩";
	for (int i = 0; i < end.size(); i++) {
		wcout << end[i];
		Sleep(50);
	}
	Sleep(3000);
}

// ==============================================
// 設定
// ===============================================
void Monopoly::printSettingWord(int xpos, int ypos) {
	setColor();
	wstring mainMenu[] = { L"更換地圖", L"更換音樂", L"更換背景", L"回主選單" };
	ypos += 1;

	for (int i = 0; i < 4; i++) {
		if (settingMode == i) setColor(0, 15);
		else setColor();
		int xShift = xpos + boardWidth / 2 + mainMenu[i].length();
		Monopoly::setCursor(xShift, ypos + i * 2);
		wcout << mainMenu[i];
	}


	setColor();
}

void Monopoly::printSettingBoard(int xpos, int ypos) {
	setCursorSize(false, 0);
	setColor(9, 0);
	int lineWidth = 2;
	for (int i = 0; i < boardHeight; i++) {
		setCursor(xpos, ypos + i);
		for (int j = 0; j < boardWidth; j++) {
			if (i == 0 || i == boardHeight - 1 || i % lineWidth == 0) // 上
			{
				if (j == 0) wcout << L"●";// 左上角
				else if (j == boardWidth - 1) wcout << L"●";// 右上角
				else wcout << L"＝";// 上方
			}
			else// 中
			{
				if (j == 0 || j == boardWidth - 1) wcout << L"∥";// 中間
				else wcout << L"　"; // 
			}
		}
	}
	setColor();
	printSettingWord(boardX, boardY);
}

void Monopoly::setting()
{
	printSettingBoard(boardX, boardY);
	settingMode = 0;
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				if (ch == 72)          // 上
				{
					settingMode--;
					if (settingMode == -1) settingMode = 3;
				}
				else if (ch == 80)    // 下
				{
					settingMode++;
					if (settingMode == 4) settingMode = 0;
				}
				printSettingBoard(boardX, boardY);
			}
			else if (ch == '\r')
			{
				switch (settingMode)
				{
				case 0: 
				{
					// getmap
					fileReader.resetAllData();
					previewMap();
					break;
				}
				case 1:
				{
					wstring tmpMusicFileNname = fileReader.getFilename("music");
					if (tmpMusicFileNname.size() == 0u)
					{
						// 表示讀檔失敗 或沒音樂
					}
					else
					{
						Monopoly::musicFileName = tmpMusicFileNname;
						string str = "music/";
						str += WstringToString(Monopoly::musicFileName);
						 
						PlaySound(TEXT(str.c_str()), NULL, SND_FILENAME | SND_ASYNC);
						// 撥音樂
					}
					break;
				}
				case 2:
				{
					// change background
					break;
				}
				case 3:
					break;
				}

				if (settingMode != 3)
				{
					printArt();
					printSettingBoard(boardX, boardY);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void Monopoly::previewMap()
{
	clearFrame();
	fileReader.previewMap(string("map"));
}

// ===============================================


// Console介面的helper function

// 印大外框
void Monopoly::printFrame(int xpos, int ypos, int xsize, int ysize, wstring title) {
	setColor();
	wstring upper;
	wstring lower(xsize - 2, L'＝');
	wstring side(xsize - 2, L'　');
	lower = L"●" + lower;
	lower.push_back(L'●');
	side = L"∥" + side;
	side.push_back(L'∥');
	if (int(title.size()) != 0)
	{
		int leftspace = (xsize - int(title.size()) - 2) / 2;
		int rightspace = xsize - int(title.size()) - 2 - leftspace;
		upper = title;
		upper = wstring(leftspace, L'＝') + upper + wstring(rightspace, L'＝');
		upper.insert(0, 1, L'●');
		upper.push_back(L'●');
	}
	else
	{
		upper = lower;
	}

	for (int i = 0; i < ysize; i++)
	{
		setCursor(xpos, ypos + i);
		if (i == 0)
		{
			wcout << upper;
		}
		else if (i == ysize - 1)
		{
			wcout << lower;
		}
		else
		{
			wcout << side;
		}
	}
}

// 設定顏色
void Monopoly::setColor(int f, int b)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

// 設定座標
void Monopoly::setCursor(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// 取得目前游標位置
void Monopoly::getCursor(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}

// 設定座標visible
void Monopoly::setCursorSize(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

string Monopoly::WstringToString(const wstring str)
{// wstring转string
	unsigned len = str.size() * 4;
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	size_t i;
	wcstombs_s(&i, p,len, str.c_str(), len);
	std::string str1(p);
	delete[] p;
	return str1;
}