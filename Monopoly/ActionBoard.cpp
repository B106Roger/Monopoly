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

// ========================================================================
// 印出玩家資訊的區塊
// ========================================================================
void ActionBoard::printPlayerInfo() {

	// 因為不會更新全部actionBoard，所以手動刷新
	printFrame();
	int infoMode = 0;
	
	int playerId = GameWorld::playerState;// 取得當前玩家為誰
	int indexY = 0; // cursor y position，一路向下++
	int lineHeight = 2; // 行間距，目前 間隔一個 + 自己本行 = 2
	int indexX = 2; // subHeader的向右縮排兩個全形字

	// + 4 : 向右縮兩個全形字 / + 2 : 向下縮一個全形字
	printPlayerInfoMain(playerId, indexY, lineHeight);

	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();

				if (ch == 75)         // 按左
				{
					
					if (infoMode != 0) {
						infoMode--;
						printFrame();
						choosePlayerInfo(infoMode, playerId, indexY, lineHeight, indexX);
					}
				}
				else if (ch == 77)    // 按右
				{
					
					if (infoMode != 2) {
						infoMode++;
						printFrame();
						choosePlayerInfo(infoMode, playerId, indexY, lineHeight, indexX);
					}
				}
			}
			if (ch == '\r') {
				printFrame();
				return;
			}

		}
	}
}

void ActionBoard::choosePlayerInfo(int infoMode, int playerId, int indexY, int lineHeight, int indexX) {
	if (infoMode == 0) printPlayerInfoMain(playerId, indexY, lineHeight);
	else if(infoMode == 1) printPlayerInfoStock(playerId, indexY, lineHeight, indexX);
	else if(infoMode == 2) printPlayerInfoHouse(playerId, indexY, lineHeight, indexX);
}

void ActionBoard::printPlayerInfoMain(int playerId, int indexY, int lineHeight) {

	// 頁首標頭
	headerTip(L"----------玩家資訊----------");
	indexY += lineHeight;

	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight;
	wcout << L"玩家ID : ";
	Monopoly::setColor(GameWorld::gameBoard.getPlayerColor(playerId), 0);
	wcout << playerId;
	Monopoly::setColor();

	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight;
	wcout << L"玩家圖案 : ";
	Monopoly::setColor(GameWorld::gameBoard.getPlayerColor(playerId), 0);
	wcout << L"●";
	Monopoly::setColor();

	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight;
	wcout << L"玩家現金 : ";
	wcout << GameWorld::playerList[playerId].cash;

	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight;
	wcout << L"玩家存款 : ";
	wcout << GameWorld::playerList[playerId].bankBalance;

	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight;
	wcout << L"遙控骰子 : ";
	wcout << GameWorld::playerList[playerId].remoteDice;

	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight;
	wcout << L"暫停回合 : ";
	wcout << GameWorld::playerList[playerId].stopRound;

	// 頁底提示按鈕
	tailTip();
};
void ActionBoard::printPlayerInfoStock(int playerId, int indexY, int lineHeight, int indexX) {

	headerTip(L"----------玩家資訊----------");
	indexY += lineHeight;
	// ==============================================================================
	// 印股票
	// ==============================================================================
	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight; // header
	wcout << L"玩家股票 : ";
	int indent = 1; // 要縮排幾格
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"股票名稱";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"持股股數";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"單股現價";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indexY += lineHeight;// sub-header
	wcout << L"總價值";
	for (int i = 0; i < GameWorld::bank.stockOwnerList[playerId].size(); i++) {
		indent = 1; // 要縮排幾格

		// 取出資訊，利於易讀性
		int stockId = GameWorld::bank.stockOwnerList[playerId][i].stockId;
		wstring name = GameWorld::bank.stockList[stockId].name;
		int number = GameWorld::bank.stockOwnerList[playerId][i].number;
		int price = GameWorld::bank.stockList[stockId].currentDollars;

		Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
		wcout << name;
		Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
		wcout << number;
		Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
		wcout << price;
		Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indexY += lineHeight;// sub-header
		wcout << number * price;
	}
	// ==============================================================================

	// 頁底提示按鈕
	tailTip();
};
void ActionBoard::printPlayerInfoHouse(int playerId, int indexY, int lineHeight, int indexX) {

	headerTip(L"----------玩家資訊----------");
	indexY += lineHeight;
	// ==============================================================================
	// 印房產
	// ==============================================================================
	Monopoly::setCursor(startX + 4, startY + 2 + indexY); indexY += lineHeight; // header
	wcout << L"玩家房產 : ";

	int indent = 1; // 要縮排幾格(全形字)
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"房產名稱";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"房產地段";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"房產價格";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
	wcout << L"房產等級";
	Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indexY += lineHeight;// sub-header
	wcout << L"過路費";

	for (int i = 0; i < GameWorld::gameMap.size(); i++) {
		if (GameWorld::gameMap[i].ownerId == playerId) {
			wstring name = GameWorld::gameMap[i].name;
			int blockId = GameWorld::gameMap[i].position;
			int price = GameWorld::gameMap[i].buyCost;
			int level = GameWorld::gameMap[i].level;
			int tolls = GameWorld::gameMap[i].tolls[level];
			indent = 1; // 要縮排幾格(全形字)
			Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
			wcout << name;
			Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
			wcout << blockId;
			Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
			wcout << price;
			Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indent += 5;// sub-header
			wcout << level;
			Monopoly::setCursor(startX + 4 + indexX * indent, startY + 2 + indexY); indexY += lineHeight;// sub-header
			wcout << tolls;
		}
	}
	// ==============================================================================

	// 頁底提示按鈕
	tailTip();
};

// ========================================================================

void ActionBoard::headerTip(wstring tip) {
	Monopoly::setCursor(startX + 4, startY + 2);
	wcout << tip;
};

void ActionBoard::tailTip() {
	Monopoly::setCursor(startX + width / 2, startY + length - 2);
	wcout << L"←　Ｅｎｔｅｒ　→";
}


// 印出股票版
void ActionBoard::printStock()
{
	printFrame();
	Monopoly::setCursor(startX + 4, startY + 4);
	wcout << setw(6) << L"公司" << setw(6) << L"上次價格" << setw(6) << L"本日價格" << setw(5) << L"脹/跌" << endl;
	for (int i = 0; i < Bank::stockList.size(); i++) {
		Monopoly::setCursor(startX + 4, startY + 5 + i);
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

	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == '\r') {
				printFrame();
				return;
			}
				
		}
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
