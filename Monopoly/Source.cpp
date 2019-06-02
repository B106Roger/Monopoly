#include<iostream>
#include"Monopoly.h"
#include<locale>
using namespace std;

int main()
{
	locale::global(locale(""));
	Monopoly monopoly;
	system("pause>nul");
	monopoly.monopolyLoop();

	return 0;
}