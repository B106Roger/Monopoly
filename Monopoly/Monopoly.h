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
	void monopolyInit();       // ��l�ƹC���Ѽ� (�a�ϡB�n��.....)
	void monopolyLoop();       // �C���y�{�j��
	













	static wstring settingFileName;     // �]�w���ɦW
	static wstring gameMapFileName;     // �C���a���ɦW
	static wstring musicFileName;       // �C�������ɦW
	static wstring gameRecordFileName;  // �C���O���ɦW
	static GameWorld gameWorld;         // �C���@��
	// �H�U�Ҭ�console�����]�w���
	// 0 ��, 1 ��, 2 ��, 3�L��, 4 ��, 5 ��, 6�g��, 7 �զ�, 8 ��, 9 �G��,10�G��, 11�G�L��, 12�L��, 13�L��, 14�L�� 15 ��
	static void setColor(int fontColor = 7, int backgroundColor = 0);
	static void setCursor(int x, int y);
	static void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1
};

