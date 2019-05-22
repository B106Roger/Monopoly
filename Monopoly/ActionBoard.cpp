#include "ActionBoard.h"



ActionBoard::ActionBoard()
{
}

void ActionBoard::printStock(vector<Stock> stockList)
{
	wcout << setw(4) << L"公司" << setw(5) << L"上次價格" << setw(5) << L"本日價格" << setw(3) << L"帳/跌" << endl;
	for (int i = 0; i < stockList.size(); i++) {
		wcout << setw(4) << stockList[i].name << L"|";
		wcout << setw(5) << stockList[i].previousDollars << L"|";
		wcout << setw(5) << stockList[i].currentDollars << L"|";		
		if (stockList[i].currentDollars > stockList[i].previousDollars) {
			SetColor(2, 0);
			wcout << setw(3) << "↑" << endl;
		}
		else if (stockList[i].currentDollars < stockList[i].previousDollars) {
			SetColor(4, 0);
			wcout << setw(3) << "↓" << endl;
		}
		else
			wcout << setw(3) << L"-" << endl;
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
