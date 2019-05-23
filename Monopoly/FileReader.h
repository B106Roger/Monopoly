#pragma once

#include<string>
#include<fstream>

using namespace std;
class FileReader
{
public:
	FileReader();
	~FileReader();
	void readAndSetData();        // 讀取Monopoly::gameMapFileName 內的檔案到GameWorld
	void resetAllData();          // reset所有gameWorld的參數
};

