#include "Kruskal.h"

DSStruct::DSStruct(int n)
{
	Z = new DSNode[n];             
}

DSStruct::~DSStruct()
{
	delete[] Z;                   
}

void DSStruct::MakeSet(int v)
{
	Z[v].up = v;
	Z[v].rank = 0;
}

int DSStruct::FindSet(int v)
{
	if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
	return Z[v].up;
}

void DSStruct::UnionSets(Edge e)
{
	int ru, rv;

	ru = FindSet(e.wp);             
	rv = FindSet(e.wk);             
	if (ru != rv)                   
	{
		if (Z[ru].rank > Z[rv].rank)   
			Z[rv].up = ru;              
		else
		{
			Z[ru].up = rv;              
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}
}

MSTree::MSTree(int n)
{
	int i;

	A = new TNode *[n];            
	for (i = 0; i < n; i++) A[i] = NULL; 
	Alen = n - 1;                   
	weight = 0;                     
}

MSTree::~MSTree()
{
	int i;
	TNode *p, *r;

	for (i = 0; i <= Alen; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;                     
			p = p->next;                
			delete r;                  
		}
	}

	delete[] A;                    
}

void MSTree::addEdge(Edge e)
{
	TNode *p;

	weight += e.weight;             
	p = new TNode;                  
	p->v = e.wk;                    
	p->weight = e.weight;           
	p->next = A[e.wp];              
	A[e.wp] = p;

	p = new TNode;                  
	p->v = e.wp;                   
	p->weight = e.weight;          
	p->next = A[e.wk];              
	A[e.wk] = p;
}

void MSTree::print()
{
	int i;
	TNode *p;

	cout << endl;
	for (i = 0; i <= Alen; i++)
	{
		cout << "Vertex " << i << " - ";
		for (p = A[i]; p; p = p->next) cout << p->v << ":" << p->weight << " ";
		cout << endl;
	}
	cout << endl << endl << "Minimal Spanning Tree Weight = " << weight << endl << endl;
}

Kruskal::Kruskal()
{
}

Kruskal::~Kruskal()
{
}

void Kruskal::make(int n, int m)
{
	DSStruct Z(n);                 
	Queue Q(m);                     
	MSTree T(n);                    

	for (i = 0; i < n; i++)
		Z.MakeSet(i);                 

	for (i = 0; i < m; i++)
	{
		cin >> e.wp >> e.wk >> e.weight; 
		Q.push(e);                    
	}

	for (i = 1; i < n; i++)          
	{
		do
		{
			e = Q.front();              
			Q.pop();                   
		} while (Z.FindSet(e.wp) == Z.FindSet(e.wk));
		T.addEdge(e);                 
		Z.UnionSets(e);              
	}

	T.print();
}