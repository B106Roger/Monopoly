#include "Monopoly.h"

wstring Monopoly::musicFileName;
wstring Monopoly::gameMapFileName;
wstring Monopoly::settingFileName;
wstring Monopoly::gameRecordFileName;
GameWorld Monopoly::gameWorld;
FileReader Monopoly::fileReader;

Monopoly::Monopoly()
{
	monopolyInit();
}

Monopoly::~Monopoly()
{
}
void Monopoly::monopolyInit()
{
	musicFileName = L"";
	gameMapFileName = L"map//basemap.txt";
	settingFileName = L"";
	gameRecordFileName = L"";
}

void Monopoly::monopolyLoop()
{
	mode = 0;
	monopolyInit();
	while (mode != 3)
	{
		if (mode == 0)
		{
			fileReader.readAndSetMap();
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
	}
}


















// static function
// 設定座標
void Monopoly::setCursor(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// 設定顏色
void Monopoly::setColor(int f, int b)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
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
