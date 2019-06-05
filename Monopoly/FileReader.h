#pragma once
#include<string>
#include<fstream>
#include<filesystem>
#include<sstream>
#include<algorithm>
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
	void readAndSetRecord();                // 讀取Monopoly::gameRecordFileName 內的檔案到GameWorld
	void readAndSetMap();                   // 讀取Monopoly::gameMapFilaeName 內的檔案到GameWorld
	void resetAllData();                    // reset所有gameWorld的參數 全部設為空
	void saveRecord();                      // 儲存檔案


	vector<FS::path> getAllFile(const FS::path & ps);                         // 取得某個路徑下所有的檔案
	void displayFolder(const vector<FS::path> & fileList, int index);         // 顯示某個資料夾下的所有檔案，並讓使用者選擇
	wstring getFilename(string foldername);                                      // 讓使用者選擇要用的檔案
	

	void previewMap(string foldername);
	void displayMapFolder(const vector<FS::path> & fileList, int index);
	wstring userInputFileName();
};

