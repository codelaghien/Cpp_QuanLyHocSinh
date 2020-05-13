#pragma once
#include <string>
#include "HuyStudent.h"
using namespace std;

class HuyStack
{
	private:
		const int MAX_SIZE = 1000;
		int _AvailableIndex = 0;
		HuyStudent* _HuyStack;
		int _CurrentIndex = 0;
		int _Size = 0;

	public:
		HuyStack();
		~HuyStack();

		void push(HuyStudent student);
		HuyStudent pop();
		HuyStudent peek();
		bool isEmpty();
		bool isFull();

		int size() { return _Size;  }
		void resetCurrentIndex() { _CurrentIndex = 0;  }
		HuyStudent getNextData();
};

