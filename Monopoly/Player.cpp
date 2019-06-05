#include "Player.h"
#include"Monopoly.h"
#include"Bank.h"

Player::Player():
	id(-1),cash(0),bankBalance(0),stopRound(0),playerPosition(0),remoteDice(0),debt(0),repamentRound(0)
{
}
bool Player::withdraw(int dollars)
{
	if (bankBalance < dollars)
	{
		cash += bankBalance;
		bankBalance = 0;
		return false;
	}
	else
	{
		cash += dollars;
		bankBalance -= dollars;
		return true;
	}
}
bool Player::deposit(int dollars)
{
	if (cash < dollars)
	{
		bankBalance += cash;
		cash = 0;
		return false;
	}
	else
	{
		cash -= dollars;
		bankBalance += dollars;
		return true;
	}
}

Player::~Player()
{
}

//void Player::buyStock()
//{
//	const int startX = 100;
//	const int startY = 0;
//	Monopoly::setCursor(startX + 8, startY + 4);
//	wcout << setw(6) << L"���q" << setw(6) << L"����" <<setw(4) << L"��X" << setw(5) << L"���Ѽ�" << setw(4) << L"�R�J" << endl;
//	for (int i = 0; i < Bank::stockList.size(); i++) {
//		Monopoly::setCursor(startX + 8, startY + 5 + i);
//		wcout << setw(4) << Bank::stockList[i].name << L"|";
//		wcout << setw(6) << Bank::stockList[i].currentDollars << L"|";
//	}
//}
