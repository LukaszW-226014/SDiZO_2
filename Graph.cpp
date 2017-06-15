#include "Graph.h"

Graph::Graph(int w, int m)
{
	edges = m;
	tops = w;
	incidenceMatrix = new int *[tops];
	nondirectedGraphM = new int *[tops];
	adjacencyLists = new ListElement *[tops];
	nondirectedGraphL = new ListElement *[tops];
	K = new Edge[edges];
	KO = new Edge[edges];
	reverseEdges = 0;
}
Graph::~Graph()
{
	int i;
	for (int i = 0; i < tops; i++)
	{
		e1 = adjacencyLists[i];
		while (e1)
		{
			e2 = e1;
			e1 = e1->next;
			delete e2;
		}
	}
	delete[] adjacencyLists;


	for (i = 0; i < tops; i++) delete[] incidenceMatrix[i];
	delete[] incidenceMatrix;


}
void Graph::nondirectedGraph()
{
	int i, j;
	for (i = 0; i < tops; i++)
		nondirectedGraphM[i] = new int[edges];
	for (i = 0; i < tops; i++)
		for (j = 0; j < edges; j++)
		{
			nondirectedGraphM[i][j] = 0;
		}

	for (i = 0; i < tops; i++)
		nondirectedGraphL[i] = NULL;

	for (i = 0; i < edges; i++)
	{
		j = 0;
		while (j < reverseEdges)
		{

			if (KO[j].wp == K[i].wp && KO[j].wk == K[i].wk)
			{
				break;
			}
			else j++;
		}
		if (j == reverseEdges)
		{
			KO[reverseEdges].wp = K[i].wk;
			KO[reverseEdges].wk = K[i].wp;
			KO[reverseEdges].weight = K[i].weight;
			reverseEdges++;
		}
	}

	int wp, wk, weight;
	for (int i = 0; i < reverseEdges; i++)
	{
		wp = KO[i].wp;
		wk = KO[i].wk;
		weight = KO[i].weight;
		e1 = new ListElement;
		e1->w = wk;
		e1->weight = weight;
		e1->next = nondirectedGraphL[wp];
		nondirectedGraphL[wp] = e1;
		e2 = new ListElement;
		wp = KO[i].wk;
		wk = KO[i].wp;
		weight = KO[i].weight;
		e2->w = wk;
		e2->weight = weight;
		e2->next = nondirectedGraphL[wp];
		nondirectedGraphL[wp] = e2;

		nondirectedGraphM[KO[i].wp][i] = 1;
		nondirectedGraphM[KO[i].wk][i] = 1;
	}

}
void Graph::randomEdges()
{
	int c = 0;
	int * T;
	int b, toAdd1, toAdd2, a, i, j;
	int countDegree = 0;
	int * inTree;
	int * notInTree;
	a = tops;
	notInTree = new int[a];
	for (i = 0; i < a; i++)
	{
		notInTree[i] = i;
	}
	inTree = new int[a];
	b = rand() % a;
	toAdd1 = notInTree[b];
	notInTree[b] = notInTree[a - 1];
	a--;
	inTree[c] = toAdd1;
	c++;

	for (i = 0; i < (tops - 1); i++)
	{
		b = rand() % c;
		toAdd1 = inTree[b];

		b = rand() % a;
		toAdd2 = notInTree[b];
		notInTree[b] = notInTree[a - 1];
		a--;
		inTree[c] = toAdd2;
		c++;
		K[i].wp = toAdd1;
		K[i].wk = toAdd2;
	}
	for (i = 0; i < (tops - 1); i++)
	{

		b = rand() % tops;
		swap(K[b].wk, K[b].wp);

	}

	for (i = tops - 1; i < edges; i++)
	{
		a = tops;
		T = new int[a];
		for (int k = 0; k < a; k++)
		{
			T[k] = k;
		}

		b = rand() % a;
		toAdd1 = T[b];
		T[b] = T[a - 1];
		a--;
		while (true)
		{

			countDegree = 0;
			for (j = 0; j < i; j++)
			{
				if (K[j].wp == toAdd1)
					countDegree++;
				if (countDegree == tops - 1) break;
			}

			if (countDegree == tops - 1)
			{
				b = rand() % a;
				toAdd1 = T[b];
				T[b] = T[a - 1];
				a--;
			}

			else break;
		}

		a = tops;
		for (int k = 0; k < a; k++)
		{
			T[k] = k;
		}

		T[toAdd1] = T[a - 1];
		a--;

		b = rand() % a;
		toAdd2 = T[b];
		T[b] = T[a - 1];
		a--;

		for (j = 0; j < i; j++)
		{
			while (toAdd1 == K[j].wp && toAdd2 == K[j].wk)
			{
				b = rand() % a;
				toAdd2 = T[b];
				T[b] = T[a - 1];
				a--;
				j = 0;
			}
		}
		K[i].wp = toAdd1;
		K[i].wk = toAdd2;
		delete[]T;
	}

	for (i = 0; i < edges; i++)
		K[i].weight = (rand() % 9) + 1;

	delete[] notInTree;
	delete[] inTree;
}
void Graph::randomGraph()
{
	int i, j;
	for (i = 0; i < tops; i++)
		incidenceMatrix[i] = new int[edges];
	for (i = 0; i < tops; i++)
		for (j = 0; j < edges; j++)
		{
			incidenceMatrix[i][j] = 0;
		}

	for (i = 0; i < tops; i++)
		adjacencyLists[i] = NULL;

	randomEdges();
	nondirectedGraph();
	for (i = 0; i < edges; i++)
	{
		int wp = K[i].wp;
		int wk = K[i].wk;
		int weight = K[i].weight;
		e1 = new ListElement;
		e1->w = wk;
		e1->weight = weight;
		e1->next = adjacencyLists[wp];
		adjacencyLists[wp] = e1;

		incidenceMatrix[wp][i] = 1;
		incidenceMatrix[wk][i] = -1;
	}

}
int Graph::getTops()
{
	return tops;
}
int Graph::getEdges()
{
	return edges;
}
bool Graph::isConsistent()
{
	Stack stack;
	int w, u, i;
	int count = 0;

	visited = new bool[tops];
	for (i = 0; i < tops; i++)
	{
		visited[i] = false;
	}

	stack.push(0);
	visited[0] = true;

	while (!stack.empty())
	{
		w = stack.top();
		stack.pop();
		count++;
		for (e1 = nondirectedGraphL[w]; e1; e1 = e1->next)
		{
			u = e1->w;
			if (!visited[u])
			{
				visited[u] = true;
				stack.push(u);
			}
		}
	}
	delete[]visited;
	if (count == tops)
		return true;

	else return false;
}


void Graph::matrixDijkstry(int w)
{
	int root, node, heapSize, parent, leftSon, rightSon, costMin, minSon, son, *costs, *predecessors, *heap, *heapPosition;
	Stack stack;
	int width, i, j, l;
	costs = new int[tops];
	predecessors = new int[tops];
	visited = new bool[tops];
	heap = new int[tops];
	heapPosition = new int[tops];

	for (i = 0; i < tops; i++)
	{
		costs[i] = MAXINT;
		predecessors[i] = -1;
		visited[i] = false;
		heap[i] = heapPosition[i] = i;
	}


	timeOfOperation.timeStart();
	heapSize = tops;

	costs[w] = 0;
	node = heap[0];
	heap[0] = heap[w];
	heap[w] = node;
	heapPosition[w] = 0;
	heapPosition[0] = w;

	for (i = 0; i < tops; i++)
	{
		root = heap[0];

		heap[0] = heap[--heapSize];
		heapPosition[heap[0]] = parent = 0;
		while (true)
		{
			leftSon = parent + parent + 1;
			rightSon = leftSon + 1;
			if (leftSon >= heapSize) break;
			costMin = costs[heap[leftSon]];
			minSon = leftSon;
			if ((rightSon < heapSize) && (costMin > costs[heap[rightSon]]))
			{
				costMin = costs[heap[rightSon]];
				minSon = rightSon;
			}
			if (costs[heap[parent]] <= costMin)
				break;
			node = heap[parent];
			heap[parent] = heap[minSon];
			heap[minSon] = node;
			heapPosition[heap[parent]] = parent;
			heapPosition[heap[minSon]] = minSon;
			parent = minSon;
		}

		visited[root] = true;

		for (l = 0; l < edges; l++)
		{
			if (incidenceMatrix[root][l] != 0)
				for (j = 0; j < tops; j++)
					if (j != root && incidenceMatrix[j][l] == -1 && !visited[j] && (costs[j] > costs[root] + K[l].weight))
					{
						costs[j] = costs[root] + K[l].weight;
						predecessors[j] = root;

						for (son = heapPosition[j]; son; son = parent)
						{
							parent = son / 2;
							if (costs[heap[parent]] <= costs[heap[son]])
								break;
							node = heap[parent];
							heap[parent] = heap[son];
							heap[son] = node;
							heapPosition[heap[parent]] = parent;
							heapPosition[heap[son]] = son;
						}
					}
		}
	}
	timeOfOperation.timeTake();
	cout << endl;

	cout << "Najkrotsza droga z wierzcholka nr " << w << " do wierzcholka nr: " << endl << endl;
	for (i = 0; i < tops; i++)
	{
		width = -2;

		cout << i << ": ";


		if (costs[i] == MAXINT || costs[i]<0)
			cout << "Brak sciezki" << endl;
		else

		{
			for (j = i; j > -1; j = predecessors[j])
			{
				stack.push(j);
				width = width + 2;
			}

			while (!stack.empty())
			{
				cout << stack.top() << " ";
				stack.pop();
			}
			for (j = 0; j < tops - width; j++)
				cout << " ";
			cout << setw(5) << "(" << costs[i] << ")" << endl;
		}
	}
	cout << endl << endl;
}

void Graph::listDijkstry(int w)
{
	int root, node, heapSize, parent, leftSon, rightSon, costMin, minSon, son, *costs, *predecessors, *heap, *heapPosition;
	Stack stack;
	int width, i, j;
	costs = new int[tops];
	predecessors = new int[tops];
	visited = new bool[tops];
	heap = new int[tops];
	heapPosition = new int[tops];

	for (i = 0; i < tops; i++)
	{
		costs[i] = MAXINT;
		predecessors[i] = -1;
		visited[i] = false;
		heap[i] = heapPosition[i] = i;
	}
	timeOfOperation.timeStart();
	heapSize = tops;

	costs[w] = 0;
	node = heap[0];
	heap[0] = heap[w];
	heap[w] = node;
	heapPosition[w] = 0;
	heapPosition[0] = w;

	for (i = 0; i < tops; i++)
	{
		root = heap[0];

		heap[0] = heap[--heapSize];
		heapPosition[heap[0]] = parent = 0;
		while (true)
		{
			leftSon = parent + parent + 1;
			rightSon = leftSon + 1;
			if (leftSon >= heapSize) break;
			costMin = costs[heap[leftSon]];
			minSon = leftSon;
			if ((rightSon < heapSize) && (costMin > costs[heap[rightSon]]))
			{
				costMin = costs[heap[rightSon]];
				minSon = rightSon;
			}
			if (costs[heap[parent]] <= costMin)
				break;
			node = heap[parent];
			heap[parent] = heap[minSon];
			heap[minSon] = node;
			heapPosition[heap[parent]] = parent;
			heapPosition[heap[minSon]] = minSon;
			parent = minSon;
		}

		visited[root] = true;

		if (adjacencyLists[root] != NULL)
			for (e1 = adjacencyLists[root]; e1; e1 = e1->next)
				if (!visited[e1->w] && (costs[e1->w] > costs[root] + e1->weight))
				{
					costs[e1->w] = costs[root] + e1->weight;
					predecessors[e1->w] = root;

					for (son = heapPosition[e1->w]; son; son = parent)
					{
						parent = son / 2;
						if (costs[heap[parent]] <= costs[heap[son]])
							break;
						node = heap[parent];
						heap[parent] = heap[son];
						heap[son] = node;
						heapPosition[heap[parent]] = parent;
						heapPosition[heap[son]] = son;
					}
				}
	}
	timeOfOperation.timeTake();
	cout << endl;

	cout << "Najkrotsza droga z wierzcholka nr " << w << " do wierzcholka nr: " << endl << endl;
	for (i = 0; i < tops; i++)
	{
		width = -2;

		cout << i << ": ";


		if (costs[i] == MAXINT || costs[i]<0)
			cout << "Brak sciezki" << endl;
		else

		{
			for (j = i; j > -1; j = predecessors[j])
			{
				stack.push(j);
				width = width + 2;
			}

			while (!stack.empty())
			{
				cout << stack.top() << " ";
				stack.pop();
			}
			for (j = 0; j < tops - width; j++)
				cout << " ";
			cout << setw(5) << "(" << costs[i] << ")" << endl;
		}
	}
	cout << endl << endl;
}

void Graph::matrixBellmanFord(int w)
{
	int root, node, heapSize, parent, leftSon, rightSon, costMin, minSon, son, *costs, *predecessors, *heap, *heapPosition;
	Stack stack;
	int width, i, j, l;
	costs = new int[tops];
	predecessors = new int[tops];
	visited = new bool[tops];
	heap = new int[tops];
	heapPosition = new int[tops];

	for (i = 0; i < tops; i++)
	{
		costs[i] = MAXINT;
		predecessors[i] = -1;
		visited[i] = false;
		heap[i] = heapPosition[i] = i;
	}

	timeOfOperation.bel = true;
	timeOfOperation.timeStart();
	heapSize = tops;

	costs[w] = 0;
	node = heap[0];
	heap[0] = heap[w];
	heap[w] = node;
	heapPosition[w] = 0;
	heapPosition[0] = w;

	for (i = 0; i < tops; i++)
	{
		root = heap[0];

		heap[0] = heap[--heapSize];
		heapPosition[heap[0]] = parent = 0;
		while (true)
		{
			leftSon = parent + parent + 1;
			rightSon = leftSon + 1;
			if (leftSon >= heapSize) break;
			costMin = costs[heap[leftSon]];
			minSon = leftSon;
			if ((rightSon < heapSize) && (costMin > costs[heap[rightSon]]))
			{
				costMin = costs[heap[rightSon]];
				minSon = rightSon;
			}
			if (costs[heap[parent]] <= costMin)
				break;
			node = heap[parent];
			heap[parent] = heap[minSon];
			heap[minSon] = node;
			heapPosition[heap[parent]] = parent;
			heapPosition[heap[minSon]] = minSon;
			parent = minSon;
		}

		visited[root] = true;

		for (l = 0; l < edges; l++)
		{
			if (incidenceMatrix[root][l] != 0)
				for (j = 0; j < tops; j++)
					if (j != root && incidenceMatrix[j][l] == -1 && !visited[j] && (costs[j] > costs[root] + K[l].weight))
					{
						costs[j] = costs[root] + K[l].weight;
						predecessors[j] = root;

						for (son = heapPosition[j]; son; son = parent)
						{
							parent = son / 2;
							if (costs[heap[parent]] <= costs[heap[son]])
								break;
							node = heap[parent];
							heap[parent] = heap[son];
							heap[son] = node;
							heapPosition[heap[parent]] = parent;
							heapPosition[heap[son]] = son;
						}
					}
		}
	}
	timeOfOperation.timeTake();
	timeOfOperation.bel = false;
	cout << endl;

	cout << "Najkrotsza droga z wierzcholka nr " << w << " do wierzcholka nr: " << endl << endl;
	for (i = 0; i < tops; i++)
	{
		width = -2;

		cout << i << ": ";


		if (costs[i] == MAXINT || costs[i]<0)
			cout << "Brak sciezki" << endl;
		else

		{
			for (j = i; j > -1; j = predecessors[j])
			{
				stack.push(j);
				width = width + 2;
			}

			while (!stack.empty())
			{
				cout << stack.top() << " ";
				stack.pop();
			}
			for (j = 0; j < tops - width; j++)
				cout << " ";
			cout << setw(5) << "(" << costs[i] << ")" << endl;
		}
	}
	cout << endl << endl;

}

void Graph::listBellmanFord(int w)
{
	int root, node, heapSize, parent, leftSon, rightSon, costMin, minSon, son, *costs, *predecessors, *heap, *heapPosition;
	Stack stack;
	int width, i, j;
	costs = new int[tops];
	predecessors = new int[tops];
	visited = new bool[tops];
	heap = new int[tops];
	heapPosition = new int[tops];

	for (i = 0; i < tops; i++)
	{
		costs[i] = MAXINT;
		predecessors[i] = -1;
		visited[i] = false;
		heap[i] = heapPosition[i] = i;
	}
	//timeOfOperation.bel = true;
	timeOfOperation.timeStart();
	heapSize = tops;

	costs[w] = 0;
	node = heap[0];
	heap[0] = heap[w];
	heap[w] = node;
	heapPosition[w] = 0;
	heapPosition[0] = w;

	for (i = 0; i < tops; i++)
	{
		root = heap[0];

		heap[0] = heap[--heapSize];
		heapPosition[heap[0]] = parent = 0;
		while (true)
		{
			leftSon = parent + parent + 1;
			rightSon = leftSon + 1;
			if (leftSon >= heapSize) break;
			costMin = costs[heap[leftSon]];
			minSon = leftSon;
			if ((rightSon < heapSize) && (costMin > costs[heap[rightSon]]))
			{
				costMin = costs[heap[rightSon]];
				minSon = rightSon;
			}
			if (costs[heap[parent]] <= costMin)
				break;
			node = heap[parent];
			heap[parent] = heap[minSon];
			heap[minSon] = node;
			heapPosition[heap[parent]] = parent;
			heapPosition[heap[minSon]] = minSon;
			parent = minSon;
		}

		visited[root] = true;

		if (adjacencyLists[root] != NULL)
			for (e1 = adjacencyLists[root]; e1; e1 = e1->next)
				if (!visited[e1->w] && (costs[e1->w] > costs[root] + e1->weight))
				{
					costs[e1->w] = costs[root] + e1->weight;
					predecessors[e1->w] = root;

					for (son = heapPosition[e1->w]; son; son = parent)
					{
						parent = son / 2;
						if (costs[heap[parent]] <= costs[heap[son]])
							break;
						node = heap[parent];
						heap[parent] = heap[son];
						heap[son] = node;
						heapPosition[heap[parent]] = parent;
						heapPosition[heap[son]] = son;
					}
				}
	}
	timeOfOperation.timeTake();
	//timeOfOperation.bel = false;
	cout << endl;

	cout << "Najkrotsza droga z wierzcholka nr " << w << " do wierzcholka nr: " << endl << endl;
	for (i = 0; i < tops; i++)
	{
		width = -2;

		cout << i << ": ";


		if (costs[i] == MAXINT || costs[i]<0)
			cout << "Brak sciezki" << endl;
		else

		{
			for (j = i; j > -1; j = predecessors[j])
			{
				stack.push(j);
				width = width + 2;
			}

			while (!stack.empty())
			{
				cout << stack.top() << " ";
				stack.pop();
			}
			for (j = 0; j < tops - width; j++)
				cout << " ";
			cout << setw(5) << "(" << costs[i] << ")" << endl;
		}
	}
	cout << endl << endl;

}

void Graph::matrixPrim()
{

	int w, i, j, g;
	Edge edge;
	priority_queue <Edge, vector<Edge>, Edge> queue;
	SpinningTree *tree = new SpinningTree(tops, edges);
	visited = new bool[tops];
	for (i = 0; i < tops; i++)
	{
		visited[i] = false;
	}

	cout << "Graf nieskierowany na podstawie ktorego budowano drzewo: " << endl << endl;
	cout << "   ";
	for (i = 0; i < reverseEdges; i++)
	{
		cout << setw(3) << i;

	}
	cout << endl << endl;
	for (i = 0; i < tops; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < reverseEdges; j++)
			cout << setw(3) << nondirectedGraphM[i][j];
		cout << endl;
	}
	cout << endl;
	cout << "   ";
	for (i = 0; i < reverseEdges; i++)
	{
		cout << setw(3) << KO[i].weight;
	}
	cout << " " << "<- wagi";
	cout << endl;

	timeOfOperation.timeStart();

	w = 0;
	visited[w] = true;
	for (i = 1; i < tops; i++)
	{
		for (g = 0; g < reverseEdges; g++)
		{

			if (nondirectedGraphM[w][g] != 0)
				for (j = 0; j < tops; j++)
					if (j != w && nondirectedGraphM[j][g] != 0 && !visited[j])
					{
						edge.wp = w;
						edge.wk = j;
						edge.weight = KO[g].weight;
						queue.push(edge);

					}
		}
		do
		{
			edge = queue.top();
			queue.pop();

		} while (visited[edge.wk]);

		tree->addEdge(edge);
		visited[edge.wk] = true;
		w = edge.wk;

	}
	timeOfOperation.timeTake();
	cout << endl << endl;
	cout << "MST:";
	tree->show();
	delete tree;
}

void Graph::listPrim()
{
	int w, i;
	Edge k;
	priority_queue <Edge, vector<Edge>, Edge> queue;
	SpinningTree *tree = new SpinningTree(tops, edges);
	visited = new bool[tops];
	for (i = 0; i < tops; i++)
	{
		visited[i] = false;
	}
	cout << endl << "Graf nieskierowany na podstawie ktorego zbudowano drzewo: " << endl << endl;
	for (i = 0; i < tops; i++)
	{
		cout << "L[" << i << "] =";
		e1 = nondirectedGraphL[i];
		while (e1)
		{
			cout << setw(3) << e1->w << "(" << e1->weight << ") ";
			e1 = e1->next;
		}
		cout << endl;
	}
	cout << endl;
	timeOfOperation.timeStart();
	w = 0;
	visited[w] = true;

	for (i = 1; i < tops; i++)
	{

		for (e1 = nondirectedGraphL[w]; e1; e1 = e1->next)
		{
			if (!visited[e1->w])
			{
				k.wp = w;
				k.wk = e1->w;
				k.weight = e1->weight;
				queue.push(k);
			}
		}
		do
		{
			k = queue.top();
			queue.pop();

		} while (visited[k.wk]);

		tree->addEdge(k);
		visited[k.wk] = true;
		w = k.wk;

	}

	timeOfOperation.timeTake();
	cout << endl;
	cout << "MST:";
	tree->show();
	delete tree;
}

void Graph::matrixKruskal()
{
	int w, i, j, g;
	Edge edge;
	priority_queue <Edge, vector<Edge>, Edge> queue;
	SpinningTree *tree = new SpinningTree(tops, edges);
	visited = new bool[tops];
	for (i = 0; i < tops; i++)
	{
		visited[i] = false;
	}

	cout << "Graf nieskierowany na podstawie ktorego budowano drzewo: " << endl << endl;
	cout << "   ";
	for (i = 0; i < reverseEdges; i++)
	{
		cout << setw(3) << i;

	}
	cout << endl << endl;
	for (i = 0; i < tops; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < reverseEdges; j++)
			cout << setw(3) << nondirectedGraphM[i][j];
		cout << endl;
	}
	cout << endl;
	cout << "   ";
	for (i = 0; i < reverseEdges; i++)
	{
		cout << setw(3) << KO[i].weight;
	}
	cout << " " << "<- wagi";
	cout << endl;
	timeOfOperation.kru = true;
	timeOfOperation.timeStart();

	w = 0;
	visited[w] = true;
	for (i = 1; i < tops; i++)
	{
		for (g = 0; g < reverseEdges; g++)
		{

			if (nondirectedGraphM[w][g] != 0)
				for (j = 0; j < tops; j++)
					if (j != w && nondirectedGraphM[j][g] != 0 && !visited[j])
					{
						edge.wp = w;
						edge.wk = j;
						edge.weight = KO[g].weight;
						queue.push(edge);

					}
		}
		do
		{
			edge = queue.top();
			queue.pop();

		} while (visited[edge.wk]);

		tree->addEdge(edge);
		visited[edge.wk] = true;
		w = edge.wk;

	}
	timeOfOperation.timeTake();
	timeOfOperation.kru = false;
	cout << endl << endl;
	cout << "MST:";
	tree->show();
	delete tree;
}

void Graph::listKruskal()
{
	int w, i;
	Edge k;
	priority_queue <Edge, vector<Edge>, Edge> queue;
	SpinningTree *tree = new SpinningTree(tops, edges);
	visited = new bool[tops];
	for (i = 0; i < tops; i++)
	{
		visited[i] = false;
	}
	cout << endl << "Graf nieskierowany na podstawie ktorego zbudowano drzewo: " << endl << endl;
	for (i = 0; i < tops; i++)
	{
		cout << "L[" << i << "] =";
		e1 = nondirectedGraphL[i];
		while (e1)
		{
			cout << setw(3) << e1->w << "(" << e1->weight << ") ";
			e1 = e1->next;
		}
		cout << endl;
	}
	cout << endl;
	timeOfOperation.kru = true;
	timeOfOperation.timeStart();
	w = 0;
	visited[w] = true;

	for (i = 1; i < tops; i++)
	{

		for (e1 = nondirectedGraphL[w]; e1; e1 = e1->next)
		{
			if (!visited[e1->w])
			{
				k.wp = w;
				k.wk = e1->w;
				k.weight = e1->weight;
				queue.push(k);
			}
		}
		do
		{
			k = queue.top();
			queue.pop();

		} while (visited[k.wk]);

		tree->addEdge(k);
		visited[k.wk] = true;
		w = k.wk;

	}

	timeOfOperation.timeTake();
	timeOfOperation.kru = false;
	cout << endl;
	cout << "MST:";
	tree->show();
	delete tree;
}

void Graph::show()
{
	int i;
	cout << "   ";
	for (i = 0; i < edges; i++)
	{
		cout << setw(3) << i;

	}
	cout << endl << endl;
	for (i = 0; i < tops; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < edges; j++)
			cout << setw(3) << incidenceMatrix[i][j];
		cout << endl;
	}
	cout << endl;
	cout << "   ";
	for (i = 0; i < edges; i++)
	{
		cout << setw(3) << K[i].weight;
	}

	cout << " " << "<- wagi";
	cout << endl << endl << endl;
	for (i = 0; i < tops; i++)
	{
		cout << "L[" << i << "] =";
		e1 = adjacencyLists[i];
		while (e1)
		{
			cout << setw(3) << e1->w << "(" << e1->weight << ") ";
			e1 = e1->next;
		}
		cout << endl;
	}
}