#pragma once
#include<Windows.h>
#include<conio.h>
#include<string>
#include<iostream>
#include"GameWorld.h"
using namespace std;

class Monopoly
{
public:
	// 0 GameMode;  1 SettingMode; 2 DetailMode; 3 ExitMode
	Monopoly();
	~Monopoly();
	void monopolyInit();       // 初始化遊戲參數 (地圖、聲音.....)
	void monopolyLoop();       // 遊戲流程迴圈





	static wstring settingFileName;     // 設定檔檔名
	static wstring gameMapFileName;     // 遊戲地圖檔名
	static wstring musicFileName;       // 遊戲音樂檔名
	static wstring gameRecordFileName;  // 遊戲記錄檔名
	static GameWorld gameWorld;         // 遊戲世界
	// 以下皆為console視窗設定函數
	// 0 黑, 1 藍, 2 綠, 3淺藍, 4 紅, 5 紫, 6土黃, 7 白灰, 8 灰, 9 亮藍,10亮綠, 11亮淺藍, 12淺紅, 13淺粉, 14淺黃 15 白
	static void setColor(int fontColor = 7, int backgroundColor = 0);
	static void setCursor(int x, int y);
	static void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1
};

