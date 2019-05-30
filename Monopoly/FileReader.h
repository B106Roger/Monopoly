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
	void readAndSetData();        // Ū��Monopoly::gameMapFileName �����ɮר�GameWorld
	void resetAllData();          // reset�Ҧ�gameWorld���Ѽ�
	void saveFile();              // �x�s�ɮ�
	
	bool getFilename(string foldername);
private:
	vector<FS::path> getAllFile(const FS::path & ps);
	void displayFolder(const vector<FS::path> & fileList, int index);         // ��ܬY�Ӹ�Ƨ��U���Ҧ��ɮסA�����ϥΪ̿��

};

