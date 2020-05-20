#pragma once
using namespace std;
#include "HuyCommon.h"
#include "HuyStack.h"

class HuyConfig
{
	public:
		HuyConfig();
		~HuyConfig();
	 
		static bool loadConfig();
		static void loadData(HuyStack& students);
};

