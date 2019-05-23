#include<iostream>
#include"Monopoly.h"
#include<locale>
using namespace std;

int main()
{
	locale::global(locale(""));
	Monopoly monopoly;
	system("PAUSE");
	monopoly.monopolyLoop();
	return 0;
}