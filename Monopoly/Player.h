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
	int playerPosition;
	int remoteDice;           // ������l�ƶq// �s�C���C�H�K�O�ذe������l
	int withdraw(int dollars);
	int deposit(int dollars);
	// int buyStock(Stock & stock, int number);
	// int soldStock(Stock& stock, int number);
};
