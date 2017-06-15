#ifndef BellmanFord_h
#define BellmanFord_h

#include "ListElement.h"

using namespace std;

class BellmanFord
{
public:
	int m, n;                          
	ListElement ** A;                     
	long long * d;                    
	int * p;
	int i, v, x, y, w, sptr, *S;
	ListElement *rv, *pv;
//	int i, x;
	bool test;
	ListElement * pv2;

private:

public:
	BellmanFord();
	~BellmanFord();
	bool BF(int v);
	void make(int n, int m);
};

#endif // !BellmanFord_h