#pragma once
#include"Bank.h"
#include<iomanip>
#include<Windows.h>
#include<iostream>
class ActionBoard
{
public:
	ActionBoard();
	void printStock();
	~ActionBoard();
private:
	// 0 ��, 1 ��, 2 ��, 3�L��, 4 ��, 5 ��, 6�g��, 7 �զ�, 8 ��, 9 �G��,10�G��, 11�G�L��, 12�L��, 13�L��, 14�L�� 15 ��
	static void SetColor(int fontColor = 7, int backgroundColor = 0);

};

