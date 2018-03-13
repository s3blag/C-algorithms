#include "stdafx.h"
#include "GraphAdjacencyMatrix.h"
using namespace std;

//destruktor grafu
GraphAdjacencyMatrix::~GraphAdjacencyMatrix()
{
	for (int i = 0; i < numberOfNodes; ++i) 
		delete[] adjacencyMatrix[i];
}

//Generowanie grafow spojnych - analogicznie do reprezentacji listowej
bool GraphAdjacencyMatrix::createUndirectedGraph(int numbOfNodes, int density)
{
	int randomWeight,numberOfEdgesToGenerate = float(numbOfNodes*(numbOfNodes - 1))*((float)density / 100.0) / 2,
		currentNumberOfEdges = 0, randomNode1 = -1, randomNode2 = -1;

	if (numberOfEdgesToGenerate >= numbOfNodes - 1)
	{
		currentNumberOfEdges+=initializeUndirectedAdjacencyMatrix(numbOfNodes);
		while (currentNumberOfEdges < numberOfEdgesToGenerate)
		{
			randomNode1 = rand() % numbOfNodes;
			randomNode2 = rand() % numbOfNodes;
			if (adjacencyMatrix[randomNode1][randomNode2] == INF && randomNode1 != randomNode2)
			{
				randomWeight = rand() % (2 * numbOfNodes);
				adjacencyMatrix[randomNode1][randomNode2] = randomWeight;
				adjacencyMatrix[randomNode2][randomNode1] = randomWeight;
				currentNumberOfEdges++;
			}
		}
		this->numberOfEdges = numberOfEdgesToGenerate;
		this->numberOfNodes = numbOfNodes;
		//showGraph();
		return true;
	}
	else
	{
		cout << endl << "Zbyt mala wartosc dla grafu spojnego" << endl;
		return false;
	}
}

bool GraphAdjacencyMatrix::createDirectedGraph(int numbOfNodes, int density)
{

	int randomWeight, numberOfEdgesToGenerate = float(numbOfNodes*(numbOfNodes - 1))*((float)density / 100.0) ,
		currentNumberOfEdges = 0, randomNode1 = -1, randomNode2 = -1;

	if (numberOfEdgesToGenerate >= numbOfNodes - 1)
	{
		currentNumberOfEdges += initializeDirectedAdjacencyMatrix(numbOfNodes);
		while (currentNumberOfEdges < numberOfEdgesToGenerate)
		{
			randomNode1 = rand() % numbOfNodes;
			randomNode2 = rand() % numbOfNodes;
			if (adjacencyMatrix[randomNode1][randomNode2] == INF && randomNode1 != randomNode2)
			{
				randomWeight = rand() % (2 * numbOfNodes);
				adjacencyMatrix[randomNode1][randomNode2] = randomWeight;
				currentNumberOfEdges++;
			}
		}
		this->numberOfEdges = numberOfEdgesToGenerate;
		this->numberOfNodes = numbOfNodes;
		//showGraph();

		return true;
	}
	else
	{
		cout << endl << "Zbyt mala wartosc dla grafu spojnego" << endl;
		return false;
	}


}


// Inicjalizacja grafu nieskierowanego->tworzenie najprostszego grafu spojnego
//poprzez laczenie wierzcholka i z i+1 ... wagi dla tych krawedzi sa znacznie
//wieksze niz dla pozostalych, by algorytm znajdowania najkrotszej drogi mial
//trudniejsze zadanie ...
int GraphAdjacencyMatrix::initializeUndirectedAdjacencyMatrix(int numberOfNodes)
{
	adjacencyMatrix = new int* [numberOfNodes];
	int randomWeight, numbrOfEdges=0;
	//wypelnienie tablicy inf
	for (int i = 0; i < numberOfNodes; i++)
	{
		adjacencyMatrix[i] = new int[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++)
		{
			adjacencyMatrix[i][j] = INF;
		}
	}

	for (int node = 0; node < numberOfNodes - 1; node++)
	{	
		randomWeight = rand() % (20 * numberOfNodes);
		adjacencyMatrix[node][node + 1]=randomWeight;
		adjacencyMatrix[node+1][node] = randomWeight;
		numbrOfEdges++;
	}
	return numbrOfEdges;
}
//Inicjalizacja dla grafu skierowanego
int GraphAdjacencyMatrix::initializeDirectedAdjacencyMatrix(int numberOfNodes)
{
	adjacencyMatrix = new int*[numberOfNodes];
	int randomWeight, numbrOfEdges = 0;
	for (int i = 0; i < numberOfNodes; i++)
	{
		adjacencyMatrix[i] = new int[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++)
		{
			adjacencyMatrix[i][j] = INF;
		}
	}

	for (int node = 0; node < numberOfNodes - 1; node++)
	{
		randomWeight = rand() % (20 * numberOfNodes);
		adjacencyMatrix[node][node + 1] = randomWeight;
		numbrOfEdges++;
	}
	return numbrOfEdges;
}

//wczytywanie z pliku
bool GraphAdjacencyMatrix::loadDataFromFile(string name)
{
	ifstream file;
	int node1, node2, weight,unused;
	
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci elementów i wierzch. pocz.
	file >> numberOfEdges;
	file >> numberOfNodes;
	file >> startingVertex;
	file >> unused;

	// Utworzenie nowej tablicy
	adjacencyMatrix = new int*[numberOfNodes];
	
	// Zapelnienie za pomoca wartosci nieskonczonosci 
	for (int i = 0; i < numberOfNodes; i++)
	{
		adjacencyMatrix[i] = new int[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++)
		{
			adjacencyMatrix[i][j] = INF;
		}
	}
	
	// Pêtla wczytuj¹ca wartoœci 
		while (file.good())
		{
			file >> node1;
			file >> node2;
			file >> weight;
			adjacencyMatrix[node1][node2] = weight;
		}
	return true;

}

//wczytywanie z pliku
bool GraphAdjacencyMatrix::loadDirectedFromFile(string name)
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

	// Utworzenie nowej tablicy
	adjacencyMatrix = new int*[numberOfNodes];

	// Zapelnienie za pomoca wartosci nieskonczonosci 
	for (int i = 0; i < numberOfNodes; i++)
	{
		adjacencyMatrix[i] = new int[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++)
		{
			adjacencyMatrix[i][j] = INF;
		}
	}

	// Pêtla wczytuj¹ca wartoœci 
	while (file.good())
	{
		file >> node1;
		file >> node2;
		file >> weight;
		adjacencyMatrix[node1][node2] = weight;
	}
	return true;

}

//wczytywanie z pliku
bool GraphAdjacencyMatrix::loadUndirectedFromFile(string name)
{
	ifstream file;
	int node1, node2, weight,unused;

	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci elementów i wierzch. pocz.
	file >> numberOfEdges;
	file >> numberOfNodes;
	file >> startingVertex;
	file >> unused;

	// Utworzenie nowej tablicy
	adjacencyMatrix = new int*[numberOfNodes];

	// Zapelnienie za pomoca wartosci nieskonczonosci 
	for (int i = 0; i < numberOfNodes; i++)
	{
		adjacencyMatrix[i] = new int[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++)
		{
			adjacencyMatrix[i][j] = INF;
		}
	}

	// Pêtla wczytuj¹ca wartoœci 
	while (file.good())
	{
		file >> node1;
		file >> node2;
		file >> weight;
		adjacencyMatrix[node1][node2] = weight;
		adjacencyMatrix[node2][node1] = weight;
	}

	return true;

}




// --- GETTERY ---

int GraphAdjacencyMatrix::getNumberOfNodes()
{
	return numberOfNodes;
}

int GraphAdjacencyMatrix::getStartingVertex()
{
	return startingVertex;
}

int** GraphAdjacencyMatrix::getAdjacencyMatrix()
{
	return adjacencyMatrix;
}

//Wyswietlenie grafu
void GraphAdjacencyMatrix::showGraph()
{
	for (int col = 0; col < numberOfNodes; col++)
	{
		cout.width(7);
		cout << " " << col;
	}
	for (int row = 0; row < numberOfNodes; row++)
	{

		cout << endl << row << "   ";
		for (int column = 0; column < numberOfNodes; column++)
		{
			cout.width(5);
			cout << ((adjacencyMatrix[row][column] == INF) ? "inf" : to_string(adjacencyMatrix[row][column])) << "   ";
		}
	}
}
