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
	const int menuX = startX + gapX*2, menuY = startY + gapY;
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
	printFrame();
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
void ActionBoard::printChance(int index)
{
	printFrame();
	Monopoly::setCursor(startX + 8, startY + 5);
	wcout << (L"－－－－－－－你抽到的機會是－－－－－－－");
	Monopoly::setCursor(startX + 8, startY + 7);
	wstring message = GameWorld::chanceList[index].message;
	if (message.size() > 21) {
		for (int i = 0; i < 21; i++) {
			wcout << message[i];
		}
		Monopoly::setCursor(startX + 8, startY + 8);
		for (int i = 21; i < message.size(); i++)
			wcout << message[i];
	}
	else
		wcout << message;

	tailTip();
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
void ActionBoard::printDestiny(int index)
{
	printFrame();
	Monopoly::setCursor(startX + 8, startY + 5);
	wcout << (L"----------你抽到的命運是----------");
	Monopoly::setCursor(startX + 8, startY + 7);
	wstring message = GameWorld::destinyList[index].message;
	if (message.size() > 21) {
		for (int i = 0; i < 21; i++)
			wcout << message[i];
		Monopoly::setCursor(startX + 8, startY + 8);
		for (int i = 0; i < message.size(); i++)
			wcout << message[i];
	}
	else
		wcout << message;
	tailTip();
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

void ActionBoard::tailTip(wstring tip) {
	Monopoly::setCursor(startX + width / 2, startY + length - 2);
	wcout << tip;
}

void ActionBoard::pressEnterKeyToContinue() {
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

void ActionBoard::pressAnyKeyToContinue() {
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			printFrame();
			return;
		}
	}
}

// ========================================================================
// 印出股票版
// ========================================================================
void ActionBoard::printStock()
{
	printFrame();
	Monopoly::setCursor(startX + 8, startY + 4);
	wcout << setw(6) << L"公司" << setw(6) << L"上次價格" << setw(6) << L"本日價格" << setw(5) << L"脹/跌" << endl;
	for (int i = 0; i < Bank::stockList.size(); i++) {
		Monopoly::setCursor(startX + 8, startY + 5 + 2 * i);
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
	tailTip();
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
// ========================================================================

// ========================================================================
// 印出購買股票介面
// ========================================================================
vector<int> ActionBoard::printBuyStock()
{
	printFrame();                     // 清空ActionBoard
	Player currentPlayer = GameWorld::playerList[GameWorld::playerState];     // 取得當前玩家reference
	int lineHeight = 2;                                                       // 行間距，股票與股票之間的間距
	int indexX = startX + 4, indexY = startY + 3;                             // 股票列印位置
	vector<int> numberOfStock(int(Bank::stockList.size()), 0);                // 股票數量
	Monopoly::setColor();
	headerTip(L"----------股票交易所----------");
	Monopoly::setCursor(indexX, indexY);
	wcout << L"存款:　" << currentPlayer.bankBalance ;
	indexY += 2;
	// 列印交易版 標頭
	Monopoly::setCursor(indexX, indexY);
	wcout << L"股票名稱" << L'　';
	wcout << L"單股現價" << L'　';
	wcout << L"購買張數" << L'　';
	wcout << L"　總價格" << L'　';
	wcout << L"持有股數" << L'　';
	
	// 列印股票交易列表
	indexY += 2;
	int stockId = 0, previousId = 0;
	for (int i = 0; i < int(numberOfStock.size());i++)
	{
		printBuyStockNumber(i, numberOfStock[i], indexX, indexY + 2 * i, i == stockId);
		int owned;
		vector<StockRecord>::iterator it = find_if(
			GameWorld::bank.stockOwnerList[GameWorld::playerState].begin(),
			GameWorld::bank.stockOwnerList[GameWorld::playerState].end(),
			[i](StockRecord & ref) {return ref.stockId == i; }
		);
		if (it != GameWorld::bank.stockOwnerList[GameWorld::playerState].end())
			owned = it->number;
		else
			owned = 0;
		wcout << L'　';						//印現有持股數
		cout.width(4);
		cout << owned;
	}
	printTotalStock(numberOfStock, indexX, indexY + 2 * int(numberOfStock.size()));
	while (true)
	{
		if (_kbhit)
		{
			int ch = _getch();
			// 方向鍵操控數量
			if (ch == 224)   
			{
				ch = _getch();
				switch (ch)
				{
				case 72: //上
				{
					previousId = stockId;
					--stockId;
					if (stockId == -1)
					{
						stockId = int(numberOfStock.size()) - 1;
					}
					break;
				}
				case 80: //下
				{
					previousId = stockId;
					++stockId;
					if (stockId == int(numberOfStock.size()))
					{
						stockId = 0;
					}
					break;
				}
				case 75: //左
				{
					int & ref = numberOfStock[stockId];
					--ref;
					if (ref < 0) ref = 0;
					break;
				}
				case 77: //右
				{
					int & ref = numberOfStock[stockId], total = 0;
					++ref;
					for (int i = 0; i < int(numberOfStock.size()); i++)
					{
						total += numberOfStock[i] * Bank::stockList[i].currentDollars;
					}
					if (total > currentPlayer.bankBalance) --ref;
				}
				}
			}
			// Enter鍵 確認交易
			else if (ch == '\r')
			{
				return numberOfStock;
			}
			// Esc鍵 取消交易
			else if (ch == 27)
			{
				return vector<int>(int(Bank::stockList.size()), 0);
			}
			printBuyStockNumber(previousId, numberOfStock[previousId], indexX, indexY + 2 * previousId, false);
			printBuyStockNumber(stockId, numberOfStock[stockId], indexX, indexY + 2 * stockId, true);
			printTotalStock(numberOfStock, indexX, indexY + 2 * int(numberOfStock.size()));
		}
	}
}
vector<int> ActionBoard::printSellStock()
{
	printFrame();                     // 清空ActionBoard
	Player currentPlayer = GameWorld::playerList[GameWorld::playerState];     // 取得當前玩家reference
	int lineHeight = 2;                                                       // 行間距，股票與股票之間的間距
	int indexX = startX + 4, indexY = startY + 3;                             // 股票列印位置
	vector<int> numberOfStock(int(Bank::stockList.size()), 0);                // 股票數量
	vector<int> numberOfOwnedStock(int(Bank::stockList.size()), 0);                // 持有股票數量
	Monopoly::setColor();
	headerTip(L"----------股票交易所----------");
	Monopoly::setCursor(indexX, indexY);
	wcout << L"存款:　" << currentPlayer.bankBalance;
	indexY += 2;
	// 列印交易版 標頭
	Monopoly::setCursor(indexX, indexY);
	wcout << L"股票名稱" << L'　';
	wcout << L"單股現價" << L'　';
	wcout << L"賣出張數" << L'　';
	wcout << L"　總價格" << L'　';
	wcout << L"持有張數" << L'　';

	// 列印股票交易列表
	indexY += 2;
	int stockId = 0, previousId = 0;
	for (int i = 0; i < int(numberOfStock.size()); i++)
	{
		printBuyStockNumber(i, numberOfStock[i], indexX, indexY + 2 * i, i == stockId);
		int owned;																//找出某股的現有持股數
		vector<StockRecord>::iterator it = find_if(
			GameWorld::bank.stockOwnerList[GameWorld::playerState].begin(),
			GameWorld::bank.stockOwnerList[GameWorld::playerState].end(),
			[i](StockRecord & ref) {return ref.stockId == i; }
		);
		if (it != GameWorld::bank.stockOwnerList[GameWorld::playerState].end())
			owned = it->number;
		else
			owned = 0;
		numberOfOwnedStock[i] = owned;
		wcout << L'　';						
		cout.width(4);
		cout << owned;
	}
	printTotalStock(numberOfStock, indexX, indexY + 2 * int(numberOfStock.size()));
	while (true)
	{
		if (_kbhit)
		{
			int ch = _getch();
			// 方向鍵操控數量
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: //上
				{
					previousId = stockId;
					--stockId;
					if (stockId == -1)
					{
						stockId = int(numberOfStock.size()) - 1;
					}
					break;
				}
				case 80: //下
				{
					previousId = stockId;
					++stockId;
					if (stockId == int(numberOfStock.size()))
					{
						stockId = 0;
					}
					break;
				}
				case 75: //左
				{
					int & ref = numberOfStock[stockId];
					--ref;
					if (ref < 0) ref = 0;
					break;
				}
				case 77: //右
				{
					int & ref = numberOfStock[stockId];
					if (ref < numberOfOwnedStock[stockId]) {
						++ref;
					}
				}
				}
			}
			// Enter鍵 確認交易
			else if (ch == '\r')
			{
				return numberOfStock;
			}
			// Esc鍵 取消交易
			else if (ch == 27)
			{
				return vector<int>(int(Bank::stockList.size()), 0);
			}
			printBuyStockNumber(previousId, numberOfStock[previousId], indexX, indexY + 2 * previousId, false);
			printBuyStockNumber(stockId, numberOfStock[stockId], indexX, indexY + 2 * stockId, true);
			printTotalStock(numberOfStock, indexX, indexY + 2 * int(numberOfStock.size()));
		}
	}
}
void ActionBoard::printBuyStockNumber(int stockId, int number, int x, int y, bool light)
{
	Monopoly::setCursor(x, y);
	const struct Stock & ref = Bank::stockList[stockId];
	wcout.width(4);
	wcout.fill(L'　');
	wcout << ref.name << L'　';

	cout.width(8);
	cout.fill(' ');
	cout << ref.currentDollars;
	wcout << L'　';

	wcout << L'←';
	cout.width(4);
	cout.fill(' ');
	light == true ? Monopoly::setColor(0, 15) : Monopoly::setColor();
	cout << number;
	Monopoly::setColor();
	wcout << L'→';
	

	wcout << L'　';
	cout.width(8);
	cout << ref.currentDollars * number;


}
void ActionBoard::printTotalStock(vector<int> &ref,int x, int y)		//印總價格
{
	int total = 0;
	for (int i = 0; i < int(ref.size()); i++)
	{
		total += Bank::stockList[i].currentDollars * ref[i];
	}
	Monopoly::setCursor(x, y);
	cout.width(19 * 2);
	cout << total;
}
// ========================================================================

// ========================================================================
// 印出銀行存款介面
// ========================================================================
int ActionBoard::printWithdrawDeposit(bool isWithdraw)// 印出存款提款介面
{
	int gapX = 4;                                          // 單位(寬字元)
	int indexX = startX + gapX * 2, indexY = startY + 3;   // indexX座標 單位(窄字元)，因此gapX要乘2
	int indexWidth = width - 2 * gapX;
	const Player & ref = GameWorld::playerList[GameWorld::playerState];
	printFrame();
	if (isWithdraw == true)
	{
		printFrame(indexX, indexY, indexWidth, 7, L"銀行提款");
	}
	else
	{
		printFrame(indexX, indexY, indexWidth, 7, L"銀行存款");
	}

	Monopoly::setCursor(indexX + 6, indexY + 2);
	if (isWithdraw == true)
	{
		wcout << L"目前存款：" << ref.bankBalance;
	}
	else
	{
		wcout << L"目前現金：" << ref.cash;
	}
	int sizeOfDigit = 10;

	Monopoly::setColor(0, 15);
	Monopoly::setCursor(indexX + 6, indexY + 4);
	cout << string(sizeOfDigit, ' ');

	Monopoly::setCursor(indexX + 6, indexY + 4);
	string number;
	
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (isdigit(char(ch)))
			{
				if (int(number.size()) < sizeOfDigit)
				{
					cout << (char)ch;
					number.push_back(char(ch));
				}
			}
			else if (ch == 224)
			{
				_getch();
			}
			else if (ch == '\b')
			{
				if (int(number.size()) != 0)
				{
					cout << "\b \b";
					number.pop_back();
				}
			}
			else if (ch == '\r')
			{
				return atoi(number.c_str());
			}
			else if (ch == 27) // Esc 按鈕
			{
				return 0;
			}
		}
	}
}

// ===============================================
// 骰子階段的動畫、提示視窗
// ===============================================
void ActionBoard::stopRoundAnim(wstring upperLine, wstring lowerLine) {
	int frameWidth = width - 6;
	int frameHeight = 9;
	int cursorX = startX + 6;
	int cursorY = startY + length / 2 - frameHeight / 2;
	
	printFrame(); // 清空actionBoard
	printFrame(cursorX, cursorY, frameWidth, frameHeight, L"暫停回合"); // 印出提示視窗
	for (int i = 0; i < upperLine.length(); i++) { // 印出提示視窗的字
		Monopoly::setCursor(cursorX + 4 + i*2, cursorY + 2); // 一個全形字佔據2個x
		wcout << upperLine[i];
		Sleep(100);
	}
	for (int i = 0; i < lowerLine.length(); i++) {
		Monopoly::setCursor(cursorX + 4 + i * 2, cursorY + 4);
		wcout << lowerLine[i];
		Sleep(100);
	}
	wstring tailTip = L"~Ｅｎｔｅｒ　Ｔｏ　Ｃｏｎｔ~";
	for (int i = 0; i < tailTip.length(); i++) {
		Monopoly::setCursor(cursorX + 4 + i * 2, cursorY + 6);
		wcout << tailTip[i];

	}
	pressEnterKeyToContinue();
}

int ActionBoard::assignDiceNumber() { 
	int frameWidth = width - 6;
	int frameHeight = 9;
	int cursorX = startX + 6;
	int cursorY = startY + length / 2 - frameHeight / 2;

	printFrame(); // 清空畫面
	printFrame(cursorX, cursorY, frameWidth, frameHeight, L"遙控骰子"); // 印小選單

	int mode = 0; // 使用骰子:不使用
	int diceNumber = 1; // 指定點數
	
	printAssignDiceWord(cursorX, cursorY, mode, diceNumber);

	while (true)
	{
		if (_kbhit)
		{
			int ch = _getch();
			// 
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: //上
				{
					if(mode != 0) mode--; 
					break;
				}
				case 80: //下
				{
					if (mode != 1) mode++;
					break;
				}
				case 75: //左
				{
					if (mode == 0 && diceNumber != 1) diceNumber--;
					break;
				}
				case 77: //右
				{
					if (mode == 0 && diceNumber != 6) diceNumber++;
					break;
				}
				}
			}
			// Enter鍵 確認交易
			else if (ch == '\r')
			{
				if(mode == 1) return 0; // 不骰
				else return diceNumber; // 骰1~6點
			}
			printAssignDiceWord(cursorX, cursorY, mode, diceNumber);
		}
	}


}

void ActionBoard::printAssignDiceWord(int cursorX, int cursorY, int mode, int diceNumber) {

	//=========
	// 第一行
	//=========
	Monopoly::setCursor(cursorX + 4, cursorY + 2); // 一個全形字佔據2個x

	if (mode == 0) Monopoly::setColor(0, 15);
	else Monopoly::setColor();
	wcout << L"遙控骰子"; 

	Monopoly::setColor();
	wcout << L"　←";

	if (mode == 0) Monopoly::setColor(0, 15);
	else Monopoly::setColor();
	wcout << L"　" << diceNumber << L"　";

	Monopoly::setColor();
	wcout << L"→ ";

	//=========
	// 第二行
	//=========
	Monopoly::setCursor(cursorX + 4, cursorY + 4);
	if (mode == 1) Monopoly::setColor(0, 15);
	else Monopoly::setColor();
	wcout << L"不遙控";

	//=========
	// 第三行
	//=========
	Monopoly::setCursor(cursorX + 4, cursorY + 6);
	Monopoly::setColor();
	wcout << L"～Ｅｎｔｅｒ　Ｔｏ　Ｃｈｏｏｓｅ～";
}
// ===============================================



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
