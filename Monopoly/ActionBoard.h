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
	
	void printStock();             // 印出股票版
	vector<int> printBuyStock();   // 印出股票購買介面
	void printPlayerInfo();        // 印出玩家資訊
	int printWithdrawDeposit(bool isWithdraw);    // 印出存款提款介面
	~ActionBoard();

private:
	const vector<wstring>& getActionList();

	// ============================================
	// 玩家資訊的板子
	// ============================================
	void choosePlayerInfo(int infoMode, int playerId, int indexY, int lineHeight, int indexX); // 三選一的code
	void printPlayerInfoMain(int playerId, int indexY, int lineHeight); // 玩家一般資訊(含標頭、尾)
	void printPlayerInfoStock(int playerId, int indexY, int lineHeight, int indexX);// 玩家股票資訊(含標頭、尾)
	void printPlayerInfoHouse(int playerId, int indexY, int lineHeight, int indexX);// 玩家房產資訊(含標頭、尾)
	// ============================================

	// ============================================
	// 印出一種股票名稱及購買數量
	// ============================================
	void printBuyStockNumber(int stockId, int number, int x, int y, bool light);
	void printTotalStock(vector<int> & ref,int x, int y);
	// ============================================


	void headerTip(wstring); // 標頭
	void tailTip(); // 頁尾
};