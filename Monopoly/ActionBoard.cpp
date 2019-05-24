#include "ActionBoard.h"
#include"Monopoly.h"
#include"Bank.h"

ActionBoard::ActionBoard()
{
}

void ActionBoard::printStock()
{
	wcout << setw(6) << L"公司" << setw(6) << L"上次價格" << setw(6) << L"本日價格" << setw(5) << L"脹/跌" << endl;
	for (int i = 0; i < Bank::stockList.size(); i++) {
		wcout << setw(4) << Bank::stockList[i].name << L"|";
		wcout << setw(9) << Bank::stockList[i].previousDollars << L"|";
		wcout << setw(9) << Bank::stockList[i].currentDollars << L"|";		
		if (Bank::stockList[i].currentDollars > Bank::stockList[i].previousDollars) {
			Monopoly::setColor(2, 0);
			wcout << setw(5) << L"↑" << endl;
		}
		else if (Bank::stockList[i].currentDollars < Bank::stockList[i].previousDollars) {
			Monopoly::setColor(4, 0);
			wcout << setw(5) << L"↓" << endl;
		}
		else
			wcout << setw(5) << L"-" << endl;
		Monopoly::setColor();
	}
}

void ActionBoard::printFrame()
{	
	Monopoly::setColor();
	const int width = 40;
	const int length = 32;
	const int xpos = 100, ypos = 0;
	
	Monopoly::setCursor(xpos, ypos);
	wcout << L'●';
	Monopoly::setCursor(xpos, ypos + length);
	wcout << L'●';
	Monopoly::setCursor(xpos + 2, ypos);
	for (int i = 0; i < width; i += 2)
		wcout << L'＊';
	Monopoly::setCursor(xpos + 2, ypos + length);
	for (int i = 0; i < width; i += 2) {
		wcout << L'＊';
	}
	for (int i = 1; i < length; i++) {
		Monopoly::setCursor(xpos + width, ypos + i);
		wcout << L'＊';
		Monopoly::setCursor(xpos, ypos + i);
		wcout << L'＊';
	}
	Monopoly::setCursor(xpos + width, ypos);
	wcout << L'●';
	Monopoly::setCursor(xpos + width, ypos + length);
	wcout << L'●';
}


ActionBoard::~ActionBoard()
{
}
