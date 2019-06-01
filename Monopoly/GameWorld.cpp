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
	updateObstacle(); // 路障生成
	actionBoard.printFrame();
	bool gameFinish = false;
	int playerAmount = playerList.size(); // 若4人中有3人破產，playerList.size()仍為4
	int round = (reamainRound * playerAmount - playerState) + 1;
	/*(reamainRound - 1) * int(playerList.size()) + playerState + 1;*/
	//while (--round)
	//{
	//	bool turnFinish = false;
	//	while (!turnFinish)
	//	{

	//		// after throw dice turnFinish = true;
	//	}

	//}
	while (!gameFinish)
	{																
		gameBoard.printPlayerAsset(); // 
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

			// 不太可能發生的code，理論上可以刪了他
			if (playerAmount == 1 && isAllBankrupt()) {
				actionBoard.loseBoard();// 顯示玩家失敗的提示
				gameFinish = true;// 跳出遊戲迴圈
				break;
			} // Warning：搬到下面會infinite loop

			do {
				playerState++;
				if (playerState == playerAmount) { // 用尾部判斷更新
					playerState %= playerAmount;
					bank.stockUpate();
					updateObstacle();
					reamainRound--;
				}
			} while (playerList[playerState].id == -1);
			
			if (isAllBankrupt()) { // 其他家都破產
				actionBoard.winBoard(1, playerList[playerState]);// 顯示玩家勝利的提示
				gameFinish = true;// 跳出遊戲迴圈
			}
			else if (reamainRound == 0) { // 20回結束
				actionBoard.winBoard(0, playerList[getRichestPlayer()]);// 結束遊戲，顯示勝利
				gameFinish = true;// 跳出遊戲迴圈
			}

			break;
		}
		case -1:
			int returnValue = actionBoard.getEscOption();
			switch(returnValue)
			{
			case 0:        // 繼續遊戲
				break;
			case 1:        // 儲存遊戲
				Monopoly::fileReader.saveRecord();
				break;
			case 2:        // 回到主選單
				return;
			}
		}
	}
}

// 新遊戲設定
void GameWorld::initGameWorld(int numberOfPlayer)
{
	int initialCash = 40000;
	playerList.clear();
	bank.stockOwnerList.clear();
	for (int i = 0; i < numberOfPlayer; i++)
	{
		Player p;  //id(-1),cash(0),bankBalance(0),stopRound(0),playerPosition(0),remoteDice(0)
		p.id = i;
		p.cash = initialCash;
		playerList.push_back(p);
		bank.stockOwnerList.push_back(vector<StockRecord>());
	}
	gameMap.clear();
	
}

void GameWorld::updateObstacle() {
	int pre = obstaclePosition;
	obstaclePosition = rand() % 28;
	if(pre >= 0) gameBoard.printItem(pre);
	gameBoard.printItem(obstaclePosition);
}


// ===================================
// 骰子階段
// ===================================

// 機會與命運
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


// 骰子階段主幹
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

// 骰子動畫
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
			Sleep(50 + i * 20); // 由快到慢
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

// 玩家走路動畫
void GameWorld::playerWalkAni(int distance) {
	for (int i = distance; i != 0; --i)
	{
		int & playerPosition = playerList[playerState].playerPosition;
		int oldPosition = playerPosition++;
		playerPosition %= 28;
		gameBoard.printItem(oldPosition);
		gameBoard.printItem(playerPosition);
		if (playerPosition == obstaclePosition) {
			actionBoard.obstacleAnim();
			break;
		}
		else if (playerPosition == 0) {
			playerList[playerState].cash += 500;
			actionBoard.startingPointAnim(); // 提示動畫
			gameBoard.printPlayerAsset(); // 更新遊戲版子的資訊
		}
		Sleep(200);
	}
}

// 玩家到訪地區判斷(副幹)
void GameWorld::playerLocation() {
	Player &player = playerList[playerState]; // 玩家
	RealEstate &house = gameMap[playerList[playerState].playerPosition]; // 房子

	// 五種到訪地區
	if (house.type == -1) { // 走到命運時
		drawADestiny();
	}
	else if (house.type == -2) { // 走到機會時
		drawAChance();
	}
	else if(house.ownerId == -1 && house.position != 0){ // 購買：走到空地時，起點不能買

		if (house.buyCost > player.cash) { // 現金買不起
			actionBoard.moneyInefficientAnim(0); // 空地mode = 0
		}
		else { // 現金買得起
			bool mode = actionBoard.buyOrNot(0, house.name);
			if (mode == true) { // 購買，將現金扣除，過戶，顯示星星
				player.cash -= house.buyCost;
				house.ownerId = playerState;
				gameBoard.printItem(house.position);// 顯示星星
			}
		}
	}
	else if (house.ownerId == playerState && house.level < 3) { // 升級：走到自己的地時，而且地產等級小於三
		int upgrateCost = house.buyCost * house.rate[house.level]; // 升級價格

		if (upgrateCost > player.cash) { // 現金升級不起
			actionBoard.moneyInefficientAnim(1); // 己地mode = 1
		}
		else { // 現金升級得起
			bool mode = actionBoard.buyOrNot(1, house.name);
			if (mode == true) { // 升級，將現金扣除，等級++，顯示星星
				player.cash -= upgrateCost;
				house.level += 1;
				gameBoard.printItem(house.position);// 顯示星星
			}
		}
	}
	else if (house.ownerId != playerState && house.position != 0) { // 過路：走到其他人的地時(上面已經濾掉無人地情況)

		int toll = house.tolls[house.level]; // 過路費
		Player &playerGet = playerList[house.ownerId];


		player.cash -= toll; // 失去方
		playerGet.cash += toll; // 獲得方
		actionBoard.payTollAnim(house.name, toll); // 支付提示
		gameBoard.printPlayerAsset(); // 更新版上資產
	}
	
	// 進行破產判斷
	if (player.cash < 0) {

		player.cash += player.bankBalance; // 提取存款，放入現金
		player.bankBalance = 0; // 存款變成0

		int totalAsset = bank.computePlayerAsset(playerList[playerState]); // 總資產
		if (totalAsset < 0) { 
			actionBoard.bankruptcyAnim(); // 付不起提示
			// 將玩家id設為破產
			player.id = -1;
			gameBoard.printItem(player.playerPosition); // 讓玩家消失在地圖上
			// 將玩家房產初始化(level = 0, ownerId = -1)
			// 初始化同時也要更新gameBoard
			bankruptcy();
		}
		else if(player.cash < 0){
			actionBoard.sellOutMenu(player);
		}
	}
}

void GameWorld::bankruptcy() {
	Player &player = playerList[playerState];
	player.cash = 0; // 清空現金
	player.bankBalance = 0; // 清空存款
	bank.bankruptStock(playerState); // 清空股票
	for (int i = 0; i < gameMap.size(); i++) { // 清空房產
		if (gameMap[i].ownerId == playerState) {
			gameMap[i].mortgageRealEstate(); // 將ownerId, level初始化
			gameBoard.printItem(gameMap[i].position); // 更新gameMap上的圖案
		}
	}
}

//=======================================================
// 遊戲結束判斷
//=======================================================
bool GameWorld::isAllBankrupt() {

	int playerAmount = playerList.size();

	if (playerAmount == 1) { // 一人遊玩狀況
		if(playerList[0].id == -1)return true;
		else return false;
	}

	int bankruptAmount = 0;

	for (int i = 0; i < playerAmount; i++) { // 2-4人遊玩狀況
		if (playerList[i].id == -1) {
			bankruptAmount++;
		}
	}
	if (bankruptAmount == playerAmount - 1) return true;
	else return false;
}

int GameWorld::getRichestPlayer() {
	int richest = -1;
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i].id != -1 && richest == -1) { // 找到第一個沒破產的人
			richest = playerList[i].id;
		}
		else if (playerList[i].id != -1 && bank.computePlayerAsset(playerList[richest]) < bank.computePlayerAsset(playerList[i])) { // 沒破產而且比richest還有錢
			richest = i;
		}
	}
	return richest;
}
//=======================================================