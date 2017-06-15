#include "Show.h"

Show::Show()
{
	goToBegin = true;
	choice = NULL;
	quantity = NULL;
	value = NULL;
	name = "";
	switchChoice();
}

Show::~Show() {}

void Show::switchChoice()
{
	cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl
		<< "Wybierz: " << endl
		<< "1. Glowne Menu" << endl
		<< "2. Test Jednostkowy" << endl
		<< "3. Zamknij" << endl;
	cin >> choice;
	system("cls");
	switch (choice)
	{
	case 1: {
		menu();

	}break;

	case 2: {
		new Test();
	}break;

	case 3: {
		exit(0);
	}break;
	}
}

void Show::menu()
{
	srand((unsigned int)time(NULL));
	bool goToBegin = true;
	while (goToBegin)
	{
		cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl 
			<< "Stworz graf" << endl << "1. Wczytaj z pliku" << endl << "2. Wylosuj graf" << endl << "3. Zamknij" << endl;
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1: {
			loadFromFile();
		}break;
		case 2: {
			randomGraph();
		}break;
		case 3: {
			exit(0);
		}break;
		}
	}
}

void Show::loadFromFile()
{
	goToBegin = false;
	ListElement *e1;
	string s, name;
	int a = 0;
	int edges, tops;
	cout << "Podaj nazwe pliku do wczytania grafu" << endl;
	cin >> name;
	name = name + ".txt";
	ifstream file("C:/Users/Luke/Development/VisualStudio/SDiZO/SDiZO_2/Source/test.txt");
	if (!file)
	{
		cout << "Nie mozna otworzyc pliku" << endl;
		goToBegin = true;

	}

	else

		{
			file >> edges >> tops;
			if (!file || edges < tops - 1 || tops <= 1 || edges >(tops*(tops - 1)))
			{
				cout << "Cos nie tak!" << endl << "Liczba wierzcholkow lub krawedzi nie jest prawidlowa." << endl;

				goToBegin = true;
			}

			else
			{
				graph = new Graph(tops, edges);
				while (!file.eof())
				{

					file >> graph->K[a].wp >> graph->K[a].wk >> graph->K[a].weight;
					if (graph->K[a].wp >= tops || graph->K[a].wk >= tops || graph->K[a].weight < 1)
					{
						cout << "Cos nie tak! Zle podane krawedzie!" << endl;
						goToBegin = true;
						break;
					}
					if (file)
						a++;

					else
					{
						cout << "Cos nie tak! Zle podane krawedzie!" << endl;
						goToBegin = true;
						break;
					}
				}
				if (a == edges)
				{
					for (int i = 0; i < tops; i++)
						graph->incidenceMatrix[i] = new int[edges];
					for (int i = 0; i < tops; i++)
						for (int j = 0; j < edges; j++)
						{
							graph->incidenceMatrix[i][j] = 0;
						}

					for (int i = 0; i < tops; i++)
						graph->adjacencyLists[i] = NULL;

					for (int i = 0; i < edges; i++)
					{
						int wp = graph->K[i].wp;
						int wk = graph->K[i].wk;
						e1 = new ListElement;
						e1->w = wk;
						e1->weight = graph->K[i].weight;
						e1->next = graph->adjacencyLists[wp];
						graph->adjacencyLists[wp] = e1;
						graph->incidenceMatrix[wp][i] = 1;
						graph->incidenceMatrix[wk][i] = -1;
					}
					file.close();
					graph->nondirectedGraph();
					if (!(graph->isConsistent()))
					{
						cout << "Graf, zbudowany z pliku jest niespojny, " << endl << "nie mozna kontynuowac!" << endl;
						goToBegin = true;
						delete graph;
					}
					else
					{
						system("cls");
						goToBegin = false;
						graphMenu();
					}
				}
			}
		}
	}

void Show::randomGraph()
{
	goToBegin = false;
	while (true)
	{
		cout << "Podaj liczbe wierzcholkow" << endl;
		cin >> w;
		if (w > 1) break;
		else cout << "Liczba wierzcholkow musi byc wieksza od 1!" << endl;
	}


	int maxK = w*(w - 1);
	double minG = ceil((((double)w - 1) * 100) / (double)maxK);

	while (true)
	{

		cout << "Podaj gestosc - co najmniej " << minG << " %" << endl;
		cin >> g;
		if (g < minG || g > 100) cout << "Podaj prawidlowa wartosc w %!"
			<< endl << "Aby graf byl spojny, gestosc musi wynosic przynajmniej " << minG << " %" << endl;
		else
			break;
	}
	double edges = ceil((maxK*g) / 100);
	graph = new Graph(w, edges);
	graph->randomGraph();
	system("cls");

	graphMenu();
}

void Show::graphMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!goToBegin)
	{

		cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Graf " << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Wierzcholki: " << graph->getTops() << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Krawedzie: " << graph->getEdges() << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Gestosc: " << g << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cout << "1. Wyswietl" << endl << "2. Dijkstry" << endl << "3. Bellman-Ford" << endl << "4. Prim" << endl << "5. Kruskal" << endl << "6. Wroc do tworzenia grafu" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: {
			system("cls");
			graph->show();
			cout << endl;

		}break;
		case 2:
		{
			system("cls");
			cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl;	
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Dijkstry " << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Wierzcholki: " << graph->getTops() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "Krawedzie: " << graph->getEdges() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Gestosc: " << g << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cout << "1. Reprezentacja macierzowa" << endl << "2. Reprezentacja listowa"  << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				while (true)
				{
					system("cls");
					cout << "Z ktorego wierzcholka szukac najkrotszych sciezek?" << endl;
					cin >> b;
					if (b < graph->getTops()) break;
					else cout << "Podaj prawidlowy numer wierzcholka!" << endl;
				}
				cout << endl;
				system("cls");
				graph->matrixDijkstry(b);

			}break;
			case 2: {
				while (true)
				{
					system("cls");
					cout << "Z ktorego wierzcholka szukac najkrotszych sciezek?" << endl;
					cin >> b;
					if (b < graph->getTops()) break;
					else cout << "Podaj prawidlowy numer wierzcholka!" << endl;
				}
				cout << endl;
				system("cls");
				graph->listDijkstry(b);

			}break;
			}
		}break;
		case 3:
		{
			system("cls");
			cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Bellman-Ford " << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Wierzcholki: " << graph->getTops() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "Krawedzie: " << graph->getEdges() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Gestosc: " << g << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cout << "1. Reprezentacja macierzowa" << endl << "2. Reprezentacja listowa" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				while (true)
				{
					system("cls");
					cout << "Z ktorego wierzcholka szukac najkrotszych sciezek?" << endl;
					cin >> b;
					if (b < graph->getTops()) break;
					else cout << "Podaj prawidlowy numer wierzcholka!" << endl;
				}
				cout << endl;
				system("cls");
				graph->matrixBellmanFord(b);

			}break;
			case 2: {
				while (true)
				{
					system("cls");
					cout << "Z ktorego wierzcholka szukac najkrotszych sciezek?" << endl;
					cin >> b;
					if (b < graph->getTops()) break;
					else cout << "Podaj prawidlowy numer wierzcholka!" << endl;
				}
				cout << endl;
				system("cls");
				graph->listBellmanFord(b);

			}break;
			}
		}break;
		case 4: {
			system("cls");
			cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Prim " << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Wierzcholki: " << graph->getTops() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "Krawedzie: " << graph->getEdges() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Gestosc: " << g << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cout << "1. Reprezentacja macierzowa" << endl << "2. Reprezentacja listowa" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				system("cls");
				graph->matrixPrim();
			}break;
			case 2: {
				system("cls");
				graph->listPrim();
			}break;
			}

			

		}break;
		case 5: {
			system("cls");
			cout << "+++++++++++++++++++++++++++++++++++++++++++| Lukasz Wojcik 226014 |+++++++++++++++++++++++++++++++++++++++++++" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Kruskal " << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Wierzcholki: " << graph->getTops() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "Krawedzie: " << graph->getEdges() << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Gestosc: " << g << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cout << "1. Reprezentacja macierzowa" << endl << "2. Reprezentacja listowa" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				system("cls");
				graph->matrixKruskal();
			}break;
			case 2: {
				system("cls");
				graph->listKruskal();
			}break;
			}

		}break;
		case 6: {
			delete graph;
			system("cls");
			goToBegin = true;

		}break;
		}
	}
}