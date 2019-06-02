#include "GameBoard.h"
#include"Monopoly.h"


GameBoard::GameBoard()
{
}


GameBoard::~GameBoard()
{
}
// 印出地圖的第N個位置
void GameBoard::printItem(int index,int xPos,int yPos, int color)
{
	int y, x;          // 全形為基準的座標
	if (index <= 7)
	{
		y = 0;
		x = index;
	}
	else if (index <= 13)
	{
		y = index - 7;
		x = 7;
	}
	else if (index <= 21)
	{
		y = 7;
		x = 21 - index;
	}
	else if (index <= 27)
	{
		x = 0;
		y = 28 - index;
	}
	int boxX = x * 2 * (boxWidth - 1) + xPos, boxY = y * (boxLength - 1) + yPos; // 在螢幕上實際的座標(半形為基準)
	const RealEstate & ref = GameWorld::gameMap[index];
	// 印出框框
	printFrame(boxX, boxY, boxWidth, boxLength);
	// 印土地名稱
	Monopoly::setCursor(boxX + 2, boxY + 1);
	Monopoly::setColor(color, getPlayerColor(ref.ownerId));
	wcout << ref.name;
	
	// 印玩家位置
	Monopoly::setColor();
	Monopoly::setCursor(boxX + 2, boxY + 2);
	for (auto const & ele : GameWorld::playerList)
	{
		if (ele.playerPosition == index)
		{
			int color = getPlayerColor(ele.id);
			Monopoly::setColor(color);
			wcout << L"●";
		}
	}
	Monopoly::setColor();
	// 印路障 + (價格或房子)
	Monopoly::setCursor(boxX + 2, boxY + 3);
	if (GameWorld::obstaclePosition == index)
	{
		wcout << L"▲";
	}
	if (ref.type == 1 && ref.ownerId != -1)
	{
		Monopoly::setColor(7, getPlayerColor(ref.ownerId));
		wcout << wstring(ref.level, L'★');
		Monopoly::setColor();
	}
}

// 印出整份地圖
void GameBoard::printMap(int xPos, int yPos)
{
	for (int i = 0; i < 28; i++)
	{
		printItem(i,xPos,yPos);
	}
}

// helper function for printItem
void GameBoard::printFrame(int xpos, int ypos, int xsize, int ysize, wstring title)
{
	Monopoly::setColor();
	wstring upper;
	wstring lower(xsize - 2, L'＝');
	wstring side(xsize - 2, L'　');
	lower = L"●" + lower;
	lower.push_back(L'●');
	side = L"∥" + side;
	side.push_back(L'∥');
	if (int(title.size()) != 0)
	{
		int leftspace = (xsize - int(title.size()) - 2) / 2;
		int rightspace = xsize - int(title.size()) - 2 - leftspace;
		upper = title;
		upper = wstring(leftspace, L'＝') + upper + wstring(rightspace, L'＝');
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

// 取得玩家專用顏色
int GameBoard::getPlayerColor(int id)
{
	int color = 7;
	switch (id)
	{
	case 0:
		color = 5;
		break;
	case 1:
		color = 1;
		break;
	case 2:
		color = 2;
		break;
	case 3:
		color = 6;
		break;
	default:
		color = 0;
	}
	return color;
}

void GameBoard::printRound(int indexX, int indexY) {
	Monopoly::setCursor(indexX, indexY -= 2);
	wcout  << L"剩餘回和數：　" << GameWorld::reamainRound << L"回";
}

// 印出玩家資產
void GameBoard::printPlayerAsset()
{
	Monopoly::setColor();
	int indexX = startX + (boxWidth + 2) * 2;
	int indexY = startY + (boxLength + 1) * 2;
	int indexWidth = 15, indexLength = 3;
	int nameLength = 8;
	printRound(indexX, indexY);
	Monopoly::setCursor(indexX, indexY);
	wcout << wstring((indexWidth - 5)/2, L'－') << L"玩家總資產" << wstring((indexWidth - 5) / 2, L'－');
	int i = 0;
	indexY++;
	for (auto & ref: GameWorld::playerList)
	{
		printFrame(indexX, indexY + i * (indexLength-1), indexWidth, indexLength);

		ref.id == GameWorld::playerState ? Monopoly::setColor(15, getPlayerColor(ref.id)) : Monopoly::setColor();
		Monopoly::setCursor(indexX + 2, indexY + i * (indexLength - 1) + 1);
		wcout.fill(L'　');
		if (ref.id != -1) {
			wcout << L"Player " << ref.id;

			Monopoly::setCursor(indexX + 2 + nameLength * 2, indexY + i * (indexLength - 1) + 1);
			cout << GameWorld::bank.computePlayerAsset(ref) << endl;
		}
		else {
			wcout << L"Player " << i;

			Monopoly::setCursor(indexX + 2 + nameLength * 2, indexY + i * (indexLength - 1) + 1);
			cout << "破產" << endl;
		}
		++i;
	}
}


void GameBoard::printItemDetail(int index)
{
	int xPos = 62, yPos = 6;
	RealEstate & realEstate = GameWorld::gameMap[index];
	int width = 20, length = 19;
	Monopoly::printFrame(xPos, yPos, width, length);

	xPos += 6; yPos++;
	Monopoly::setCursor(xPos, yPos);
	wcout << L"地點名稱: " << realEstate.name;
	

	wstring locationType;
	if (realEstate.type == -1)
		locationType = L"機會";
	else if (realEstate.type == -2)
		locationType = L"命運";
	else if (realEstate.type == 1)
		locationType = L"房產";
	else if (realEstate.type == 0)
		locationType = L"起點";
	yPos+=2;
	Monopoly::setCursor(xPos, yPos);
	wcout << L"物件類型: " << locationType;

	if (realEstate.type == 1)
	{
		yPos += 2;
		Monopoly::setCursor(xPos, yPos);
		wcout << L"空地價格: " << realEstate.buyCost;

		yPos += 2;
		Monopoly::setCursor(xPos, yPos);
		wcout << L"過路費: " << L"0階過路費 " << realEstate.tolls[0];;

		xPos += 8; yPos += 2;
		Monopoly::setCursor(xPos, yPos);
		wcout << L"1階過路費 " << realEstate.tolls[1];

		yPos += 2;
		Monopoly::setCursor(xPos, yPos);
		wcout << L"2階過路費 " << realEstate.tolls[2];

		yPos += 2;
		Monopoly::setCursor(xPos, yPos);
		wcout << L"3階過路費 " << realEstate.tolls[3];
	}
}

void GameBoard::clearItemDetail()
{
	int xPos = 62, yPos = 6;
	int width = 20, length = 19;
	wstring whiteSpace(20, L'　');
	for (int i = 0; i < length; i++)
	{
		Monopoly::setCursor(xPos, yPos + i);
		wcout << whiteSpace;
	}
}