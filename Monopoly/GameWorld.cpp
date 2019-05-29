#include "GameWorld.h"
#include"Monopoly.h"
#include<fstream>
vector<Player> GameWorld::playerList;
Bank GameWorld::bank;
vector<RealEstate> GameWorld::gameMap;
int GameWorld::playerState;
vector<Chance> GameWorld::chanceList;
vector<Chance> GameWorld::destinyList;
GameBoard GameWorld::gameBoard;
ActionBoard GameWorld::actionBoard;
ConsoleBoard GameWorld::consoleBoard;
wstring GameWorld::mapName;
int GameWorld::reamainRound;
int GameWorld::obstaclePosition;

GameWorld::GameWorld()
{
	// ===============================================================
	// 將dice圖片讀入
	// ===============================================================
	locale::global(locale(""));
	diceImages.push_back(vector<wstring>());
	wstring dicePath = L"dice//dice";
	for (int i = 1; i <= 6; i++) {
		diceImages.push_back(vector<wstring>());
		wifstream inputFile; // dice1 ~ 6 跑一輪
		wstring fileName = dicePath + to_wstring(i) + L".txt";
		inputFile.open(fileName);
		if (!inputFile.is_open()) { cout << "cannot open dice"; }
		wstring line;
		do {
			getline(inputFile, line);
			diceImages[i].push_back(line);
		} while (!inputFile.eof());

		inputFile.close();
	}
	// ===============================================================


	// ===============================
	// 增加骰子的隨機性
	// ===============================
	srand(time(NULL));
	// ===============================
}


GameWorld::~GameWorld()
{
	chanceList.clear();
	destinyList.clear();
}

// 遊戲迴圈
void GameWorld::gameStart()
{
	Monopoly::setCursorSize(false, 0);
	gameBoard.printMap();
	actionBoard.printFrame();
	int initialPlayer =  playerState;
	while (true)
	{																
		gameBoard.printPlayerAsset();
		int actionMode = actionBoard.getMenuOption();
		switch (actionMode)
		{
		case 0:                       // 玩家資訊
		{
			actionBoard.printPlayerInfo();
			break;
		}
		case 1:                       // 存款
		{
			int number = actionBoard.printWithdrawDeposit(false);
			playerList[playerState].deposit(number);
			break;
		}
		case 2:                       // 提款
		{
			int number = actionBoard.printWithdrawDeposit(true);
			playerList[playerState].withdraw(number);
			break;
		}
		case 3:                       // 股票開盤
		{
			actionBoard.printStock();
			break;
		}
		case 4:                       // 買股票
		{
			vector<int> numberOfStock = actionBoard.printBuyStock();
			playerList[playerState].bankBalance -= bank.buyStock(playerList[playerState], numberOfStock);
			break;
		}
		case 5:                       // 賣股票
		{
			vector<int> numberOfStock = actionBoard.printSellStock();
			playerList[playerState].bankBalance += bank.soldStock(playerList[playerState], numberOfStock);
			break;
		}
		case 6:                       // 擲骰子
		{
			diceStage();
			
			playerState++;
			int playerAmount = playerList.size();
			playerState %= playerAmount;
			if (playerState == 0)
			{
				bank.stockUpate();
			}
			break;
		}
		}

		

	}
}

void GameWorld::getChanceList()
{
	wifstream file;
	file.open(L"Chance.txt");
	if (file.is_open())
	{
		wstring message;
		int type, number;
		while (file >> message) {
			Chance tmp;
			tmp.message = message;
			file >> type >> number;
			tmp.type = type;
			tmp.number = number;
			chanceList.push_back(tmp);
		}
	}
}

void GameWorld::getDestinyList()
{
	wifstream file;
	file.open("Destiny.txt");
	if (file.is_open()) {
		wstring message;
		int type, number;
		while (file >> message) {
			Chance tmp;
			tmp.message = message;
			file >> type >> number;
			tmp.type = type;
			tmp.number = number;
			destinyList.push_back(tmp);
		}
	}
}

void GameWorld::drawAChance()
{
	srand(time(NULL));
	int index = rand() % chanceList.size();
	actionBoard.printChance(index);
	if (chanceList[index].type == 0) {
		playerList[playerState].cash += chanceList[index].number;
	}
	else if (chanceList[index].type == 1) {
		playerList[playerState].remoteDice += chanceList[index].number;
	}
	else if (chanceList[index].type == 2) {
		playerList[playerState].stopRound += chanceList[index].number;
	}
}

void GameWorld::drawADestiny()
{
	srand(time(NULL));
	int index = rand() % destinyList.size();
	actionBoard.printDestiny(index);
	if (destinyList[index].type == 0) {
		playerList[playerState].cash += destinyList[index].number;
	}
	else if (destinyList[index].type == 1) {
		playerList[playerState].remoteDice += destinyList[index].number;
	}
	else if (destinyList[index].type == 2) {
		playerList[playerState].stopRound += destinyList[index].number;
	}
}

void GameWorld::diceStage() {

	// 測試用code
	// =================================
	// playerList[playerState].stopRound++;
	// playerList[playerState].remoteDice++;
	// =================================


	if (playerList[playerState].stopRound > 0) {// 步驟一：能不能走動
		actionBoard.stopRoundAnim(); 
		playerList[playerState].stopRound--;
	}
	else { // 能走動
		int diceNumber;
		if (playerList[playerState].remoteDice > 0) { // 步驟二：使用遙控骰子與否
			diceNumber = actionBoard.assignDiceNumber();
			if (diceNumber) { // 1 ~ 6
				// 顯示骰子
				playDiceAni(diceNumber, false);
			}
			else { // 0
				// 骰子動畫
				diceNumber = rand() % 6 + 1;
				playDiceAni(diceNumber, true);
			}
		}
		else {
			// 骰子動畫
			diceNumber = rand() % 6 + 1;
			playDiceAni(diceNumber, true);
		}
		// 步驟三：玩家走動動畫
		playerWalkAni(diceNumber);
		// 步驟四：依據玩家走到的位置，進行購置、升級、付費、機會、命運
		playerLocation();
	}
}

void GameWorld::playDiceAni(int diceNum, bool playAni) {


	int startX = 70/*gameBoard.startX + gameBoard.width / 2*/; // width 和length是假的
	int startY = 14/*gameBoard.startY + gameBoard.length / 2*/;

	int aniTime = 12;

	if (playAni) { // 隨機亂數時，使用動畫
		for (int i = 0; i < aniTime; i++) {
			int random = rand() % 6 + 1;
			if (i == aniTime - 1) { 
				random = diceNum;
				Monopoly::setColor(6, 0);
			}
			for (int j = 0; j < diceImages[random].size(); j++) {
				Monopoly::setCursor(startX, startY + j);
				wcout << diceImages[random][j] << L"　";
			}
			Sleep(50 + i * 50); // 由快到慢
		}
	}
	else { // 使用遙控骰子時，直接顯示骰子點數
		Monopoly::setColor(6, 0);
		for (int i = 0; i < diceImages[diceNum].size(); i++) {
			Monopoly::setCursor(startX, startY + i);
			wcout << diceImages[diceNum][i] << L"　";
		}
	}
	Monopoly::setColor();

}

void GameWorld::playerWalkAni(int distance) {
	for (int i = distance; i != 0; --i)
	{
		int & playerPosition = playerList[playerState].playerPosition;
		int oldPosition = playerPosition++;
		playerPosition %= 28;
		gameBoard.printItem(oldPosition);
		gameBoard.printItem(playerPosition);
		Sleep(200);
	}
}

void GameWorld::playerLocation() {
	if (gameMap[playerList[playerState].playerPosition].type == -1) { // 走到命運時
		drawADestiny();
	}
	else if (gameMap[playerList[playerState].playerPosition].type == -2) { // 走到機會時
		drawAChance();
	}
	else if(gameMap[playerList[playerState].playerPosition].ownerId == -1){ // 走到空地時

		int buyCost = gameMap[playerList[playerState].playerPosition].buyCost; // 空地價位
		int &myMoney = playerList[playerState].cash; // 現金
		wstring houseName = gameMap[playerList[playerState].playerPosition].name;
		int &ownerId = gameMap[playerList[playerState].playerPosition].ownerId;  // 持有者
		int position = gameMap[playerList[playerState].playerPosition].position; // 房產所在地

		if (buyCost > myMoney) { // 現金買不起
			actionBoard.moneyInefficientAnim(0); // 空地mode = 0
		}
		else { // 現金買得起
			bool mode = actionBoard.buyOrNot(0, houseName);
			if (mode == true) { // 購買，將現金扣除，過戶，顯示星星
				myMoney -= buyCost;
				ownerId = playerState;
				gameBoard.printItem(position);// 顯示星星
			}
		}
	}
	else if (gameMap[playerList[playerState].playerPosition].ownerId == playerState && gameMap[playerList[playerState].playerPosition].level < 3) { // 走到自己的地時，而且地產等級小於三
		int &level = gameMap[playerList[playerState].playerPosition].level; // 等級
		int rate = gameMap[playerList[playerState].playerPosition].rate[level]; // 升級費率
		int upgrateCost = gameMap[playerList[playerState].playerPosition].buyCost * rate; // 升級價格
		int &myMoney = playerList[playerState].cash; // 現金
		wstring houseName = gameMap[playerList[playerState].playerPosition].name;
		int &ownerId = gameMap[playerList[playerState].playerPosition].ownerId;  // 持有者
		int position = gameMap[playerList[playerState].playerPosition].position; // 房產所在地

		if (upgrateCost > myMoney) { // 現金升級不起
			actionBoard.moneyInefficientAnim(1); // 空地mode = 0
		}
		else { // 現金升級得起
			bool mode = actionBoard.buyOrNot(1, houseName);
			if (mode == true) { // 升級，將現金扣除，等級++，顯示星星
				myMoney -= upgrateCost;
				level += 1;
				gameBoard.printItem(position);// 顯示星星
			}
		}
	}
	else if (gameMap[playerList[playerState].playerPosition].ownerId != playerState) { // 走到其他人的地時(上面已經濾掉無人地情況)

		int level = gameMap[playerList[playerState].playerPosition].level; // 等級
		int toll = gameMap[playerList[playerState].playerPosition].tolls[level]; // 過路費

		int &myMoney = playerList[playerState].cash; // 現金
		int &myBalance = playerList[playerState].bankBalance; // 存款
		
		if (myMoney + myBalance < toll) { // 現金、存款付不起
			myMoney = 0; myBalance = 0;
			// 進入賣股票、賣房產、宣告破產介面(actionBoard)
		}
		else { // 現金、存款付得起
			// 減去toll
			// 顯示支付過路費提示
		}
	}
}