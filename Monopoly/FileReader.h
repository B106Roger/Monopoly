#pragma once

#include<string>
#include<fstream>

using namespace std;
class FileReader
{
public:
	FileReader();
	~FileReader();
	void readAndSetData();        // Ū��Monopoly::gameMapFileName �����ɮר�GameWorld
	void resetAllData();          // reset�Ҧ�gameWorld���Ѽ�
};

