#ifndef Queue_h
#define Queue_h

#include "Edge.h"

class Queue
{
private:
	Edge * Heap;
	int hpos;
public:
	Queue(int n);
	~Queue();
	Edge front();
	void push(Edge e);
	void pop();
};

#endif // !Queue_h