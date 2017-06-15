#ifndef Stack_h
#define Stack_h

#include "ListElement.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <math.h>
#include <string>
#include <iomanip>
#include <queue>
#include <vector>

class Stack
{
private:
	ListElement * s;
public:
	Stack();

	~Stack();

	bool empty();

	int top();

	void pop();

	void push(int w);
};

#endif // !Stack_h

