#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>

class HuyCommon
{ 
    public:
		static wstring trim(wstring str);
		static string trim(string str); 
		static wstring headerPadding(wstring header, int width, wstring fillChar);
		static wstring dataPadding(wstring data, int width, string align, bool display = true);
};
