#pragma once
#pragma comment(lib, "winmm.lib")
#include<Windows.h>
#include<conio.h>
#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <thread>
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
	void printBoard(int xpos, int ypos);            // 印主選單
	void printPlayerBoard(int xpos, int ypos, int playerMode);		// 印玩家選單
	void printSettingBoard(int xpos, int ypos);     // 印主選單

	int player();									// 玩家人數迴圈
	void setting();                                  // 設定迴圈
	void printWord(int xpos, int ypos);             // 印設定選單
	void printPlayerWord(int xpos, int ypos, int playerMode);		// 印玩家人數選項
	void printSettingWord(int xpos, int ypos);      // 印設定選單 
	void previewMap();
	void printWordWide(int xpos, int ypos, int width, int height);   // 印主選單的字

	void printArt();
	void printArtSleep();
	void playSound(string str);
	void clearFrame();

	void printRule();			// 印規則
	void exitArt();				// 遊戲結束動畫

	int isFirstStart = true;
	const int startX = 0;     // 視窗左上角x,y視窗
	const int startY = 0;
	const int width = 64;     // 視窗長寬
	const int height = 36;

	int boardX = 60;
	int boardY = 25;
	int boardWidth = 20;
	int boardHeight = 11;

	int wordX;
	int wordY;
	int wordWidth;
	int wordHeight;
	

	// 0 GameMode; 1 ContinueMode; 2 RuleMode; 3 SettingMode; 4 ExitMode
	int mode;
	// 0 change map; 1 change music; 2 change background; 3 back to menu
	int settingMode;
	int modeAmount = 5;
	static wstring settingFileName;     // 設定檔檔名
	static wstring gameMapFileName;     // 遊戲地圖檔名-新遊戲開始時所套用的地圖
	static wstring musicFileName;       // 遊戲音樂檔名
	static wstring gameRecordFileName;  // 遊戲記錄檔名
	static wstring backgroundFileName;
	static GameWorld gameWorld;         // 遊戲世界
	static FileReader fileReader;       // 讀取檔案class 
	// 以下皆為console視窗設定函數
	// 0 黑, 1 藍, 2 綠, 3淺藍, 4 紅, 5 紫, 6土黃, 7 白灰, 8 灰, 9 亮藍,10亮綠, 11亮淺藍, 12淺紅, 13淺粉, 14淺黃 15 白
	static void setColor(int fontColor = 7, int backgroundColor = 0);
	static void setCursor(int x, int y);
	static void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1


	static string WstringToString(const wstring str);

	// Plays a specified waveform-audio file using MCI_OPEN and MCI_PLAY. 
	// Returns when playback begins. Returns 0L on success, otherwise 
	// returns an MCI error code.
	static DWORD playWAVEFile(HWND hWndNotify, LPSTR lpszWAVEFileName);
};

