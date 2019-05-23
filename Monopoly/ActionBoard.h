#pragma once
#include"Bank.h"
#include<iomanip>
#include<Windows.h>
#include<iostream>
class ActionBoard
{
public:
	ActionBoard();
	void printStock(vector<Stock>);
	~ActionBoard();
private:
	// 0 ¶Â, 1 ÂÅ, 2 ºñ, 3²LÂÅ, 4 ¬õ, 5 µµ, 6¤g¶À, 7 ¥Õ¦Ç, 8 ¦Ç, 9 «GÂÅ,10«Gºñ, 11«G²LÂÅ, 12²L¬õ, 13²L¯», 14²L¶À 15 ¥Õ
	static void SetColor(int fontColor = 7, int backgroundColor = 0);

};

