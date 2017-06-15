#include "Edge.h"

bool Edge::operator () (const Edge & e1, const Edge & e2)
{
	if (e1.weight > e2.weight) return true;
	if (e1.weight < e2.weight) return false;
	return false;
}