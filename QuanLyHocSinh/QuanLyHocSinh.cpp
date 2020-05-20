// QuanLyHocSinh.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h> 
#include <string>
#include <algorithm>
#include <windows.h> 
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <fstream>      
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */ 

#include "HuyWindows.h";  
#include "HuyColors.h";   
#include "HuyCurrentConsole.h";  
#include "HuySize.h";  
#include "HuyStack.h";
#include "HuyStudent.h"
#include "HuyUnicode.h"
#include "HuyCore.h"
#include "HuyConfig.h"

#include <cstdlib>
#include <cstdio>  

using unicode = typename wchar_t;
using namespace std;

#define MAX_LENGTH		100 
#define EOL				'\0'     
#define MAX_COLUMNS 	30 

#define title L" Chương trình quản lý học sinh đơn giản "

int main()
{
	if (HuyConfig::loadConfig()) {
		HuyCore HuyCore(title, HuyColors::BLUE, HuyColors::WHITE);
		HuyCore.intro();
		HuyCore.run();
	}
	else {
		wstring errorTitle = L" Thông báo ";
		HuySize consoleSize = HuyCurrentConsole::getSize();
		HuyWindows win(0, 0, consoleSize.width, consoleSize.height, 1, HuyColors::BLUE, HuyColors::WHITE);
		win.showConsoleCursor(false);
		win.clearConsole();
		win.drawFrame();
		win.write(errorTitle, (consoleSize.width - errorTitle.size()) / 2, 0, HuyColors::RED, HuyColors::WHITE);
		errorTitle = L"Tập tin thiết lập config.txt bị lỗi";
		int row = (win.getHeight() / 2) - 3;
		win.write(errorTitle, (consoleSize.width - errorTitle.size()) / 2, row++, HuyColors::BLUE, HuyColors::WHITE);
		errorTitle = L"Xin vui lòng kiểm tra lại tập tin config.txt";
		win.write(errorTitle, (consoleSize.width - errorTitle.size()) / 2, row++, HuyColors::BLUE, HuyColors::WHITE);
		errorTitle = L"Nhấn phím bất kỳ để thoát";
		win.write(errorTitle, (consoleSize.width - errorTitle.size()) / 2, ++row, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
		char c = _getch();
	}
	return 0;
}
 