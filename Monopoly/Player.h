#pragma once
#include<string>
#include<vector>

struct stockHolderRecord;
struct realEstateHolderRecord;
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
	vector<stockHolderRecord> stockRecord;
	vector<realEstateHolderRecord> realEstateRecord;
	int stopRound;
	int withdraw(int dollars);
	int deposit(int dollars);
	// int buyStock(Stock & stock, int number);
	// int soldStock(Stock& stock, int number);
};

struct stockHolderRecord
{
	int stockId;
	int number;
};
struct realEstateHolderRecord
{
	int realEstateId;
	int numberOfHouse;
};