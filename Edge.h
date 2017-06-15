#ifndef Edge_h
#define Edge_h

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

class Edge
{
public: 
	int wp, wk, weight;
	bool operator () (const Edge & e1, const Edge & e2);
};

#endif