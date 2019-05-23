#include "GameBoard.h"
#include"Monopoly.h"


GameBoard::GameBoard()
{
}


GameBoard::~GameBoard()
{
}

void GameBoard::printItem(int index)
{
	int y, x;
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
	printFrame(x * 2 * (boxWidth - 1), y * (boxLength - 1), boxWidth, boxLength);
	++y;
	x += 2;
	Monopoly::setCursor(x * 2 * (boxWidth - 1), y);
	wcout << GameWorld::gameMap[index].name;
	int a = 1 + 1;
	//for(int i = 0; i < GameWorld)

}

void GameBoard::printMap()
{
	for (int i = 0; i < 28; i++)
	{
		printItem(i);
	}
}

void GameBoard::printFrame(int xpos, int ypos, int xsize, int ysize, wstring title)
{
	Monopoly::setColor();
	wstring upper;
	wstring lower(xsize - 2, L'¡×');
	wstring side(xsize - 2, L'¡@');
	lower = L"¡´" + lower;
	lower.push_back(L'¡´');
	side = L"¡ü" + side;
	side.push_back(L'¡ü');
	if (int(title.size()) != 0)
	{
		int leftspace = (xsize - int(title.size()) - 2) / 2;
		int rightspace = xsize - int(title.size()) - 2 - leftspace;
		upper = title;
		upper = wstring(leftspace, L'¡×') + upper + wstring(rightspace, L'¡×');
		upper.insert(0, 1, L'¡´');
		upper.push_back(L'¡´');
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