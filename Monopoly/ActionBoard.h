#pragma once

#include<iomanip>
#include<iostream>
#include<vector>
#include<string>

using namespace std;
class ActionBoard
{
public:
	ActionBoard();
	const int startX = 100;
	const int startY = 0;
	const int width = 25;
	const int length = 33;

	int getMenuOption();

	void printFrame(int xpos, int ypos, int xsize, int ysize, wstring title = L"");  // �L�XactionBoard���خ�
	void printFrame();
	void printMenu(int selectedIndex);
	void printStock();      // �L�X�Ѳ���
	~ActionBoard();

private:
	const vector<wstring>& getActionList();

};

