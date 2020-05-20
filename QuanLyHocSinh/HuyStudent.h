#pragma once
#include <windows.h>
#include <locale> 
#include <vector>
#include <iostream>

using namespace std; 

class HuyStudent
{
    private: 
        vector<wstring> _Data;
        int _CurrentColumn = 0;

    public: 
        HuyStudent(); 
        HuyStudent(vector<wstring> data);
        ~HuyStudent();

        void resetCurrentColumn() { _CurrentColumn = 0; }
        wstring getNextColumnData();

        static int HeaderCount;
        static vector<wstring> Header;
        static vector<int> HeaderWidth;
        static vector<string> HeaderAlign;
        static vector<string> StudentTypes;
};

