#pragma once
#include<string>
#include<vector>
using namespace std;
class Player
{
public:
	Player();
	~Player();


	wstring name;             // ���a�W��
	int id;                   // ���aid
	int cash;                 // ���a�{��
	int bankBalance;          // ���a�s��
	int stopRound;            // ���a����ʪ��Ѿl�^�X��
	int playerPosition;       // ���a�Ҧb�a
	int remoteDice;           // ������l�ƶq// �s�C���C�H�K�O�ذe������l
	int withdraw(int dollars);// ����
	int deposit(int dollars); // �s��
	void buyStock();
	void soldStock();
};
