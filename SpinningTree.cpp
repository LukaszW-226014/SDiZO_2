#include "SpinningTree.h"

SpinningTree::SpinningTree(int tops, int e)
{
	T = new ListElement *[tops];
	for (int i = 0; i < tops; i++)
	{
		T[i] = NULL;
	}
	sizeT = tops - 1;
	weight = 0;
	e = e;
	kk = new Edge[e];
	a = 0;
}

SpinningTree::~SpinningTree()
{
	ListElement *e1, *e2;
	for (int i = 0; i <= sizeT; i++)
	{
		e1 = T[i];
		while (e1)
		{
			e2 = e1;
			e1 = e1->next;
			delete e2;
		}
	}

	delete[]T;
}

void SpinningTree::addEdge(Edge k)
{
	ListElement *e;

	weight += k.weight;
	e = new ListElement;
	e->w = k.wk;
	e->weight = k.weight;
	e->next = T[k.wp];
	T[k.wp] = e;

	e = new ListElement;
	e->w = k.wp;
	e->weight = k.weight;
	e->next = T[k.wk];
	T[k.wk] = e;

	kk[a] = k;
	a++;
}

void SpinningTree::show()
{
	cout << endl;
	for (int i = 0; i < a; i++)
	{

		cout << "Krawedz " << i + 1 << ": ";

		cout << kk[i].wp << "<-->" << kk[i].wk << " [" << kk[i].weight << "] ";

		cout << endl;
	}
	cout << endl << endl << "Waga minimalnego drzewa rozpinajacego = " << weight << endl << endl;
}