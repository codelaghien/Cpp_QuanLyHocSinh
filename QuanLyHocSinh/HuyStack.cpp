#include "HuyStack.h"
#include <iostream>
#include <conio.h> 
#include <string>
using namespace std;

HuyStack::HuyStack()
{
	_AvailableIndex = 0;
	_HuyStack = new HuyStudent[MAX_SIZE];
}
HuyStack::~HuyStack()
{
	delete[] _HuyStack;
}
void HuyStack::push(HuyStudent student)  
{
	if (isFull()) return;
	_HuyStack[_AvailableIndex] = student;
	_AvailableIndex++;
	_Size++;
}
HuyStudent HuyStack::pop()
{
	_AvailableIndex--;
	return _HuyStack[_AvailableIndex];
}
HuyStudent HuyStack::peek()
{
	return _HuyStack[_AvailableIndex - 1];
}
bool HuyStack::isEmpty()
{
	return (_AvailableIndex == 0);
}
bool HuyStack::isFull()
{
	return (_AvailableIndex >= MAX_SIZE) ;
}

HuyStudent HuyStack::getNextData() {
	return _HuyStack[_CurrentIndex++];
}