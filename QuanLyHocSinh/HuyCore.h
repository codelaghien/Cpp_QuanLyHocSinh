#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>

#include "HuyStudent.h"
#include "HuyStack.h"
#include "HuyWindows.h" 
#include "HuyColors.h"
#include "HuyUnicode.h"
#include "HuySize.h"
#include "HuyStudent.h"
#include "HuyCurrentConsole.h"
#include "HuyIO.h"

class HuyCore
{
private:
	HuyWindows _HuyWindows;
	HuyStack _Students;

public:
	HuyCore(const unicode* title, int backgroundColor = 0, int foregroundColor = 7);
	~HuyCore();

	void intro();
	void run() {
		listStudents();
	}
	void addStudent();
	void listStudents();
	void updateStudentList();
	void printBottomCommands();
	void alert(wstring titles[], int size, int closeTime = 3);
	void byeBye();

private:
	wstring printHeader();
	wstring getHeader();
	wstring printFooter(int row);
	wstring printData(HuyStudent student, int row, int stt, bool display = true);
	void saveData(string fileName, bool excel = false);
};

