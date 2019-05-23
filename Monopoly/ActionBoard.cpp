#include "ActionBoard.h"



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
			SetColor(2, 0);
			wcout << setw(5) << L"↑" << endl;
		}
		else if (Bank::stockList[i].currentDollars < Bank::stockList[i].previousDollars) {
			SetColor(4, 0);
			wcout << setw(5) << L"↓" << endl;
		}
		else
			wcout << setw(5) << L"-" << endl;
		SetColor();
	}
}

void ActionBoard::SetColor(int f, int b)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

ActionBoard::~ActionBoard()
{
}
