#pragma once
#include<string>
#include<vector>
using namespace std;
class Player
{
public:
	Player();
	~Player();


	wstring name;
	int id;
	int cash;
	int bankBalance;
	int stopRound;            //���a����ʪ��Ѿl�^�X��
	int withdraw(int dollars);
	int deposit(int dollars);
	// int buyStock(Stock & stock, int number);
	// int soldStock(Stock& stock, int number);
};
