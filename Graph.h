#ifndef Graph_h
#define Graph_h

#include "ListElement.h"
#include "Edge.h"
#include "Stack.h"
#include "SpinningTree.h"
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

class Graph
{
public:
	Edge * K, *KO;
	int ** incidenceMatrix, ** nondirectedGraphM;
	ListElement ** adjacencyLists, ** nondirectedGraphL;
	bool * visited;
	Time timeOfOperation;
private:
	int tops, edges, density, reverseEdges;
	ListElement *e1, *e2;
public:
	Graph(int w, int m);
	
	~Graph();
	
	void nondirectedGraph();
	
	void randomEdges();

	void randomGraph();

	int getTops();

	int getEdges();

	bool isConsistent();

	void matrixDijkstry(int w);

	void listDijkstry(int w);

	void matrixBellmanFord(int w);
	
	void listBellmanFord(int w);

	void matrixPrim();

	void listPrim();

	void matrixKruskal();

	void listKruskal();

	void show();
};

#endif // !Graph_h

