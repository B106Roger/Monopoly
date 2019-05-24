#include "GameBoard.h"
#include"Monopoly.h"


GameBoard::GameBoard()
{
}


GameBoard::~GameBoard()
{
}
// 印出地圖的第N個位置
void GameBoard::printItem(int index)
{
	int y, x;          // 全形為基準的座標
	if (index <= 7)
	{
		y = 0;
		x = index;
	}
	else if (index <= 13)
	{
		y = index - 7;
		x = 7;
	}
	else if (index <= 21)
	{
		y = 7;
		x = 21 - index;
	}
	else if (index <= 27)
	{
		x = 0;
		y = 28 - index;
	}
	int boxX = x * 2 * (boxWidth - 1), boxY = y * (boxLength - 1); // 在螢幕上實際的座標(半形為基準)
	const RealEstate & ref = GameWorld::gameMap[index];
	// 印出框框
	printFrame(boxX, boxY, boxWidth, boxLength);
	// 印土地名稱
	Monopoly::setCursor(boxX + 2, boxY + 1);
	wcout << ref.name;
	// 印玩家位置
	Monopoly::setCursor(boxX + 2, boxY + 2);
	for (auto const & ele : GameWorld::playerList)
	{
		if (ele.playerPosition == index)
		{
			int color = getPlayerColor(ele.id);
			Monopoly::setColor(color);
			wcout << L"●";
		}
	}
	Monopoly::setColor();
	// 印路障 + (價格或房子)
	Monopoly::setCursor(boxX + 2, boxY + 3);
	if (GameWorld::obstaclePosition == index)
	{
		wcout << L"▲";
	}
	if (ref.type == 1 && ref.ownerId != -1)
	{
		Monopoly::setColor(7, getPlayerColor(ref.ownerId));
		wcout << wstring(ref.level, L'★');
		Monopoly::setColor();
	}
}

// 印出整份地圖
void GameBoard::printMap()
{
	for (int i = 0; i < 28; i++)
	{
		printItem(i);
	}
}

// helper function for printItem
void GameBoard::printFrame(int xpos, int ypos, int xsize, int ysize, wstring title)
{
	Monopoly::setColor();
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
		Monopoly::setCursor(xpos, ypos + i);
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

// 取得玩家專用顏色
int GameBoard::getPlayerColor(int id)
{
	int color = 7;
	switch (id)
	{
	case 0:
		color = 5;
		break;
	case 1:
		color = 1;
		break;
	case 2:
		color = 2;
		break;
	case 3:
		color = 6;
		break;
	}
	return color;
}