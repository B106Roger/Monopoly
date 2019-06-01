#pragma once
#include<string>
#include<fstream>
#include<filesystem>
#include <sstream>
#include<conio.h>
using namespace std;
namespace FS = experimental::filesystem;
class FileReader
{
public:
	FileReader();
	~FileReader();
	const int startX = 60;
	const int startY = 10;

	const wstring continuePath = L"continue";
	const wstring mapPath = L"map";
	void readAndSetRecord();        // 讀取Monopoly::gameRecordFileName 內的檔案到GameWorld
	void readAndSetMap();         // 讀取Monopoly::gameMapFilaeName 內的檔案到GameWorld
	void resetAllData();          // reset所有gameWorld的參數
	void saveRecord();              // 儲存檔案
	
	bool getFilename(string foldername);
private:
	vector<FS::path> getAllFile(const FS::path & ps);
	void displayFolder(const vector<FS::path> & fileList, int index);         // 顯示某個資料夾下的所有檔案，並讓使用者選擇

};

