#include "Queue.h"

Queue::Queue(int n)
{
	Heap = new Edge[n];            
	hpos = 0;                    
}

Queue::~Queue()
{
	delete[] Heap;
}

Edge Queue::front()
{
	return Heap[0];
}

void Queue::push(Edge e)
{
	int i, j;

	i = hpos++;                     
	j = (i - 1) >> 1;               

	while (i && (Heap[j].weight > e.weight))
	{
		Heap[i] = Heap[j];
		i = j;
		j = (i - 1) >> 1;
	}

	Heap[i] = e;                  
}

void Queue::pop()
{
	int i, j;
	Edge e;

	if (hpos)
	{
		e = Heap[--hpos];

		i = 0;
		j = 1;

		while (j < hpos)
		{
			if ((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
			if (e.weight <= Heap[j].weight) break;
			Heap[i] = Heap[j];
			i = j;
			j = (j << 1) + 1;
		}

		Heap[i] = e;
	}
}