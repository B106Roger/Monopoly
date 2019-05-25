#pragma once

#include<iomanip>
#include<iostream>
#include<vector>
#include<string>

using namespace std;
class ActionBoard
{
public:
	ActionBoard();
	const int startX = 100;
	const int startY = 0;
	const int width = 30;
	const int length = 33;

	int getMenuOption();

	void printFrame(int xpos, int ypos, int xsize, int ysize, wstring title = L"");  // 印出actionBoard的框框
	void printFrame();
	void printMenu(int selectedIndex);
	
	void printStock();      // 印出股票版
	void printPlayerInfo();
	~ActionBoard();

private:
	const vector<wstring>& getActionList();
	void choosePlayerInfo(int infoMode, int playerId, int indexY, int lineHeight, int indexX); // 三選一的code
	void printPlayerInfoMain(int playerId, int indexY, int lineHeight); // 玩家一般資訊(含標頭、尾)
	void printPlayerInfoStock(int playerId, int indexY, int lineHeight, int indexX);// 玩家股票資訊(含標頭、尾)
	void printPlayerInfoHouse(int playerId, int indexY, int lineHeight, int indexX);// 玩家房產資訊(含標頭、尾)
	void headerTip(wstring); // 標頭
	void tailTip(); // 頁尾
};