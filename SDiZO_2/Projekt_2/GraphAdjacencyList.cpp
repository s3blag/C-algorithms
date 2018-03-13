#include "stdafx.h"
#include "GraphAdjacencyList.h"
using namespace std;

GraphAdjacencyList::~GraphAdjacencyList()
{
	delete[] arrayOfLists;
}

//Inicjalizacja grafu nieskierowanego -> tworzenie najprostszego grafu spojnego
//poprzez laczenie wierzcholka i z i+1 ... wagi dla tych krawedzi sa znacznie
//wieksze niz dla pozostalych, by algorytm znajdowania najkrotszej drogi mial
//trudniejsze zadanie ...
int GraphAdjacencyList::initializeUndirectedGraph(int numbOfNodes)
{	
	int randomWeight, numbrOfEdges=0;
	for (int node = 0; node < numbOfNodes - 1; node++)
	{
		randomWeight = rand() % (20 * numbOfNodes);
		arrayOfLists[node].push_front(Edge{ node + 1, randomWeight });
		arrayOfLists[node + 1].push_front(Edge{ node, randomWeight });
		numbrOfEdges++;
	}
	return numbrOfEdges;
}

//Inicjalizacja dla grafu skierowanego
int GraphAdjacencyList::initializeDirectedGraph(int numbOfNodes)
{
	int randomWeight, numbrOfEdges = 0;
	for (int node = 0; node < numbOfNodes - 1; node++)
	{
		randomWeight = rand() % (20 * numbOfNodes);
		arrayOfLists[node].push_front(Edge{ node + 1, randomWeight });
		numbrOfEdges++;
	}
	return numbrOfEdges;
}

//Generowanie grafu nieskierowanego spojnego
bool GraphAdjacencyList::createUndirectedGraph(int numbOfNodes, int density)
{	
	//Ilosc krawedzi do wygenerowania to ilosc wszystkich krawedzi w grafie nieskierowanym(n*(n-1)/2) * podana gestosc(%)
	int numberOfEdgesToGenerate = float(numbOfNodes*(numbOfNodes - 1))*((float)density / 100.0) / 2,
		currentNumberOfEdges = 0, randomWeight, randomNode1 = -1, randomNode2 = -1;
	//Jesli ilosc wierzcholkow do wygenerowania jest >= min. ilosc krawedzi dla grafu spojnego to generujemy krawedzie
	if (numberOfEdgesToGenerate >= numbOfNodes - 1)
	{
		arrayOfLists = new forward_list<Edge>[numbOfNodes];
		//tworzenie prymitywnego grafu spojnego
		currentNumberOfEdges += initializeUndirectedGraph(numbOfNodes);

		//dopoki ilosc obecnych krawedzi jest mniejsza od zadanej wielkosci grafu to generujemy kolejne krawedzie
		while (currentNumberOfEdges < numberOfEdgesToGenerate)
		{
			randomNode1 = rand() % numbOfNodes;
			randomNode2 = rand() % numbOfNodes;

			//sprawdzenie czy krawedz istnieje juz w grafie oraz czy losowa krawedz nie jest petla
			if (searchNodeInList(randomNode2, arrayOfLists[randomNode1]) == true && randomNode1 != randomNode2)
			{	//dodanie krawedzi do grafu
				randomWeight = rand() % (2 * numbOfNodes);
				arrayOfLists[randomNode2].push_front(Edge{ randomNode1, randomWeight });
				arrayOfLists[randomNode1].push_front(Edge{ randomNode2, randomWeight });
				currentNumberOfEdges++;
			}
		}
		//aktualizacja pol grafu
		this->numberOfEdges = numberOfEdgesToGenerate;
		this->numberOfNodes = numbOfNodes;
		//wyswietlenie
		//showGraph();
		
		return true;
	}
	//Gestosc za mala do wygenerowania grafu spojnego:
	else
	{
		cout << endl << "Zbyt mala wartosc dla grafu spojnego" << endl;
		return false;
	}
}

//analogicznie do grafu nieskierowanego
bool GraphAdjacencyList::createDirectedGraph(int numbOfNodes, int density)
{	
	//Ilosc krawedzi do wygenerowania to ilosc wszystkich krawedzi w grafie skierowanym(n*(n-1)) * podana gestosc(%)
	int randomWeight, numberOfEdgesToGenerate = float(numbOfNodes*(numbOfNodes - 1))*((float)density / 100.0),
		currentNumberOfEdges = 0, randomNode1 = -1, randomNode2 = -1;

	if (numberOfEdgesToGenerate >= numbOfNodes - 1)
	{
		arrayOfLists = new forward_list<Edge>[numbOfNodes];
		currentNumberOfEdges += initializeDirectedGraph(numbOfNodes);

		while (currentNumberOfEdges < numberOfEdgesToGenerate)
		{
			randomNode1 = rand() % numbOfNodes;
			randomNode2 = rand() % numbOfNodes;
			if (searchNodeInList(randomNode2, arrayOfLists[randomNode1]) == true && randomNode1 != randomNode2)
			{
				randomWeight = rand() % (2 * numbOfNodes);
				arrayOfLists[randomNode1].push_front(Edge{ randomNode2, randomWeight });
				currentNumberOfEdges++;
			}
		}

		this->numberOfEdges = numberOfEdgesToGenerate;
		this->numberOfNodes = numbOfNodes;
		showGraph();

		return true;
	}
	//Gestosc za mala do wygenerowania grafu spojnego:
	else
	{
		cout << endl << "Zbyt mala wartosc dla grafu spojnego" << endl;
		return false;
	}
}

//Metoda przeszukiwania list w celu odnalezienia okreslonego wierzcholka
bool GraphAdjacencyList::searchNodeInList(int value, forward_list<Edge> list)
{
	bool isUnique = true;

	for (forward_list<Edge>::const_iterator iterator = list.begin(), end = list.end(); iterator != end; ++iterator) {
		if (iterator->node == value)
			return false;
	}
	return isUnique;	
}

//Wyswietlanie grafu
void GraphAdjacencyList::showGraph()
{
	cout << endl << "Wierzcholek  -  Wierzcholek  Waga" << endl;
	for (int row = 0; row < numberOfNodes; row++)
	{
		for (Edge e : arrayOfLists[row])
			cout << "     " << row << "       -       " << e.node << "        " << e.weight << endl;
	}
}


// --- GETTERY ---

forward_list< GraphAdjacencyList::Edge>* GraphAdjacencyList::getAdjacencyLists()
{
	return arrayOfLists;
}

int GraphAdjacencyList::getNumberOfNodes()
{
	return numberOfNodes;
}

int GraphAdjacencyList::getStartingVertex()
{
	return startingVertex;
}

// Wczytywanie grafu z pliku
bool GraphAdjacencyList::loadDataFromFile(string name)
{
	ifstream file;
	int node1, node2, weight, unused;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci elementów i wierzch. pocz.
	file >> numberOfEdges;
	file >> numberOfNodes;
	file >> startingVertex;
	file >> unused;

	arrayOfLists = new forward_list<Edge>[numberOfNodes];
	// Pêtla wczytuj¹ca wartoœci 
	while (file.good())
	{
		file >> node1;
		file >> node2;
		file >> weight;
		arrayOfLists[node1].push_front(Edge{ node2,weight });
	}	
	return true;
}

bool GraphAdjacencyList::loadDirectedFromFile(string name)
{
	ifstream file;
	int node1, node2, weight, unused;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci elementów i wierzch. pocz.
	file >> numberOfEdges;
	file >> numberOfNodes;
	file >> startingVertex;
	file >> unused;

	arrayOfLists = new forward_list<Edge>[numberOfNodes];
	// Pêtla wczytuj¹ca wartoœci 
	while (file.good())
	{
		file >> node1;
		file >> node2;
		file >> weight;
		arrayOfLists[node1].push_front(Edge{ node2,weight });
	}
	return true;
}


bool GraphAdjacencyList::loadUndirectedFromFile(string name)
{
	ifstream file;
	int node1, node2, weight, unused;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci elementów i wierzch. pocz.
	file >> numberOfEdges;
	file >> numberOfNodes;
	file >> startingVertex;
	file >> unused;

	arrayOfLists = new forward_list<Edge>[numberOfNodes];
	// Pêtla wczytuj¹ca wartoœci 
	while (file.good())
	{
		file >> node1;
		file >> node2;
		file >> weight;
		arrayOfLists[node1].push_front(Edge{ node2,weight });
		arrayOfLists[node2].push_front(Edge{ node1,weight });
	}
	return true;
}

