#ifndef Test_h
#define Test_h

#include "ListElement.h"
#include "Edge.h"
#include "Stack.h"
#include "SpinningTree.h"
#include "Graph.h"
#include "Time.h"
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

class Test
{
public:
	Time timeOfOperation;
	
	double tmpTime;
private:
	int numberOfOperation;
	int operationCounter;
	int numberOfElement;

public:
	Test();
	~Test();

};

#endif // !Test_h

