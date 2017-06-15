#ifndef Kruskal_h
#define Kruskal_h

#include "Edge.h"
#include "Queue.h"

using namespace std;

struct DSNode
{
	int up, rank;
};

class DSStruct
{
private:
	DSNode * Z;
public:
	DSStruct(int n);
	~DSStruct();
	void MakeSet(int v);
	int FindSet(int v);
	void UnionSets(Edge e);
};

struct TNode
{
	TNode * next;
	int v, weight;
};

class MSTree
{
private:
	TNode ** A;                   
	int Alen;                   
	int weight;                
public:
	MSTree(int n);
	~MSTree();
	void addEdge(Edge e);
	void print();
};

class Kruskal 
{
public:
	int n, m;               
	Edge e;
	int i;
private:

public:
	Kruskal();
	~Kruskal();
	void make(int n, int m);
};

#endif // !Kruskal_h