#include "ActionBoard.h"
#include"Monopoly.h"
#include"Bank.h"

ActionBoard::ActionBoard()
{
}
ActionBoard::~ActionBoard()
{
}

// 印出actionBoard的框框
void ActionBoard::printFrame(int xpos, int ypos, int xsize, int ysize, wstring title) {
	Monopoly::setColor();
	wstring upper;
	wstring lower(xsize - 2, L'＊');
	wstring side(xsize - 2, L'　');
	lower = L"●" + lower;
	lower.push_back(L'●');
	side = L"＊" + side;
	side.push_back(L'＊');
	if (int(title.size()) != 0)
	{
		int leftspace = (xsize - int(title.size()) - 2) / 2;
		int rightspace = xsize - int(title.size()) - 2 - leftspace;
		upper = title;
		upper = wstring(leftspace, L'＊') + upper + wstring(rightspace, L'＊');
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
void ActionBoard::printFrame()
{
	printFrame(startX, startY, width, length, L"");
}
// 印出選菜單
void ActionBoard::printMenu(int selectedIndex)
{
	const int gapX = 6, gapY = 6;
	const int menuX = startX + gapX, menuY = startY + gapY;
	const int menuW = width - 2 * gapX, menuL = 3;
	const vector<wstring> & actionList = getActionList();
	for (int i = 0; i < int(actionList.size()); i++)
	{
		printFrame(menuX, menuY + i * (menuL - 1), menuW, menuL);
		if (selectedIndex == i) Monopoly::setColor(0, 7);
		else Monopoly::setColor();
		Monopoly::setCursor(menuX + 4, menuY + i * (menuL - 1) + 1);
		wcout << actionList[i];
	}
	Monopoly::setColor();
} 

// 讓使用者選擇菜單
int ActionBoard::getMenuOption()
{
	int mode = 0;
	printMenu(mode);
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();

				if (ch == 80)         // 按下
				{
					++mode;
					mode ==int(getActionList().size()) ? mode = 0 : 0;
				}
				else if (ch == 72)    // 按上
				{
					--mode;
					mode == -1 ? mode = int(getActionList().size())-1 : 0;
				}
				printMenu(mode);
			}
			else if (ch == '\r')
			{
				return mode;
			}
		}
	}
}

// 印出股票版
void ActionBoard::printStock()
{
	printFrame();
	Monopoly::setCursor(startX + 4, startY + 4);
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

// 遊戲中的選單
const vector<wstring>& ActionBoard::getActionList()
{
	static const vector<wstring> actionList({
		L"玩家資訊",
		L"存款",
		L"提款",
		L"股票開盤",
		L"買股票",
		L"賣股票",
		L"擲骰子"
	});
	return actionList;
}