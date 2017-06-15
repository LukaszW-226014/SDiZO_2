#include "BellmanFord.h"

BellmanFord::BellmanFord()
{
}

BellmanFord::~BellmanFord()
{
}

bool BellmanFord::BF(int v)
{
	d[v] = 0;                       
	for (i = 1; i < n; i++)          
	{
		test = true;                 
		for (x = 0; x < n; x++)        
			for (pv2 = A[x]; pv2; pv2 = pv2->next) 
				if (d[pv2->w] > d[x] + pv2->weight) 
				{
					test = false;           
					d[pv2->w] = d[x] + pv2->weight; 
					p[pv2->w] = x;           
				}
		if (test) return true;        
	}

	for (x = 0; x < n; x++)
		for (pv2 = A[x]; pv2; pv2 = pv2->next)
			if (d[pv2->w] > d[x] + pv2->weight) return false; 
	return true;
}

void BellmanFord::make(int n, int m)
{
	A = new ListElement *[n];          
	d = new long long[n];         
	p = new int[n];                
	for (i = 0; i < n; i++)         
	{
		d[i] = MAXINT;
		p[i] = -1;
		A[i] = NULL;
	}

	for (i = 0; i < m; i++)
	{
		cin >> x >> y >> w;           
		pv = new ListElement;             
		pv->w = y;                    
		pv->weight = w;
		pv->next = A[x];              
		A[x] = pv;
	}

	cout << endl;

	if (BF(v))
	{
		S = new int[n];             
		sptr = 0;

		for (i = 0; i < n; i++)
		{
			cout << i << ": ";
			for (x = i; x != -1; x = p[x])
				S[sptr++] = x;

			while (sptr)
				cout << S[--sptr] << " ";

			cout << "$" << d[i] << endl;
		}
		delete[] S;             
	}
	else cout << "Negative Cycle found!" << endl;

	for (i = 0; i < n; i++)
	{
		pv = A[i];
		while (pv)
		{
			rv = pv;
			pv = pv->next;
			delete rv;
		}
	}

	delete[] A;
	delete[] d;
	delete[] p;
}