#pragma once
#include<Windows.h>
#include<conio.h>
#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include"GameWorld.h"
#include"FileReader.h"
using namespace std;

class Monopoly
{
public:
	
	Monopoly();
	~Monopoly();
	void monopolyInit();       // 初始化遊戲參數 (地圖、聲音.....)
	void monopolyLoop();       // 遊戲流程迴圈

	static void printFrame(int xpos, int ypos, int xsize, int ysize, wstring title = L"");// 印大外框
	void printBoard(int xpos, int ypos);     // 印主選單
	void printWord(int xpos, int ypos, int width, int height);   // 印主選單的字

	void printArt();
	void printArtSleep();
	void clearFrame();

	int isFirstStart = true;
	const int startX = 0;     // 視窗左上角x,y視窗
	const int startY = 0;
	const int width = 64;     // 視窗長寬
	const int height = 36;

	int boardX = 60;
	int boardY = 10;
	int boardWidth = 20;
	int boardHeight = 31;

	int wordX;
	int wordY;
	int wordWidth;
	int wordHeight;
	

	// 0 GameMode; 1 ContinueMode; 2 RuleMode; 3 SettingMode; 4 ExitMode
	int mode;
	int modeAmount = 5;
	static wstring settingFileName;     // 設定檔檔名
	static wstring gameMapFileName;     // 遊戲地圖檔名-新遊戲開始時所套用的地圖
	static wstring musicFileName;       // 遊戲音樂檔名
	static wstring gameRecordFileName;  // 遊戲記錄檔名
	static GameWorld gameWorld;         // 遊戲世界


	static FileReader fileReader;       // 讀取檔案class 
	// 以下皆為console視窗設定函數
	// 0 黑, 1 藍, 2 綠, 3淺藍, 4 紅, 5 紫, 6土黃, 7 白灰, 8 灰, 9 亮藍,10亮綠, 11亮淺藍, 12淺紅, 13淺粉, 14淺黃 15 白
	static void setColor(int fontColor = 7, int backgroundColor = 0);
	static void setCursor(int x, int y);
	static void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1
};

