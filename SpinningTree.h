#ifndef SpinningTree_h
#define SpinningTree_h

#include "ListElement.h"
#include "Edge.h"
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

class SpinningTree
{
private:
	ListElement ** T;
	Edge *kk;
	int sizeT;
	int weight, edges;
	int a;

public:
	SpinningTree(int tops, int e);
	
	~SpinningTree();

	void addEdge(Edge k);

	void show();
};
#endif // !SpinningTree_h