#pragma once
#include<string>
using namespace std;
class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	const int startX = 0;
	const int startY = 0;
	const int width = 56;
	const int length = 56;
	const int boxWidth = 7;
	const int boxLength = 5;
	void printItem(int index);
	void printMap();
	void printFrame(int xpos, int ypos, int xsize, int ysize, wstring title = L"");
	int getPlayerColor(int playerid);

private:
	
};

//　－－－－－－－－
//　－
//　－
//　－
//　－
//　－
//　－
//　－－－－－－－－