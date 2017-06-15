#ifndef Show_h
#define Show_h

#include "ListElement.h"
#include "Edge.h"
#include "Stack.h"
#include "SpinningTree.h"
#include "Time.h"
#include "Graph.h"
#include "Test.h"
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

using namespace std;

class Show
{
public:
	bool goToBegin;
	int choice, w, g, b;
	Graph *graph;
private:
	int quantity;
	int value;
	int key;
	string name;
	Time timeOfOperation;
public:
	Show();
	~Show();
	void switchChoice();
	void menu();
	void loadFromFile();
	void randomGraph();
	void graphMenu();
};

#endif // !Show_h
