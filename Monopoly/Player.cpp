#include "Player.h"
 

Player::Player():
	id(-1),cash(0),bankBalance(0),stopRound(0),playerPosition(0),remoteDice(0)
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
