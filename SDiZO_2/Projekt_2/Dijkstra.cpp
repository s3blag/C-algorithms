#include "stdafx.h"
#include "Dijkstra.h"

using namespace std;

void Dijkstra::createShortestPath(GraphAdjacencyList *graph, int startingNode)
{	//graf
	forward_list<GraphAdjacencyList::Edge> *adjacencyLists = graph->getAdjacencyLists();
	int numberOfNodes = graph->getNumberOfNodes(), *distance = new int[numberOfNodes], 
		*parent = new int[numberOfNodes], u;
	bool *visited = new bool[numberOfNodes];

	//inicjalizacja algorytmu
	for (int i = 0; i < numberOfNodes; i++)
	{
		distance[i] = INF;
		parent[i] = -1;
		visited[i] = false;
	}
	distance[startingNode] = 0;
	
	// dopoki nie odwiedzimy wszystkich wierzcholkow wykonujemy petle
	for (int n = 0; n < numberOfNodes; n++)
	{	
		//prymitywny zamiennik kolejki priorytetowej, wychodzimy  jesli wszystkie wierzcholki zostaly odwiedzone, lub nie ma do nich dostepu
		if ((u = findMin(numberOfNodes, distance, visited)) == -1)
			break;
		// badamy sasiadow pobranego elementu
		for (forward_list<GraphAdjacencyList::Edge>::const_iterator iterator = adjacencyLists[u].begin(), end = adjacencyLists[u].end(); iterator != end; ++iterator)
		{	//Jesli nie zostal odwiedzony i nastapila poprawa dl. drogi to dokonujemy relaksacji
			if (!visited[iterator->node])
			{
				if (distance[iterator->node] > (distance[u] + iterator->weight))
				{
					distance[iterator->node] = distance[u] + iterator->weight;
					parent[iterator->node] = u;
				}
			}
		}
		visited[u] = true;
	}
	
	//wyswietlanie wyniku
	showShortestPath(distance, parent, startingNode, numberOfNodes);
	
	//czyszczenie pamieci
	delete[] distance;
	delete[] parent;
	delete[] visited;
	}

// "kolejka priorytetowa"
int Dijkstra::findMin(int numberOfVertexes, int * distance, bool *visited)
{
	int index = -1;
	int max = INF;
	for (int i = 0; i < numberOfVertexes; i++)
	{
		if (distance[i] < max && !visited[i])
		{
			index = i;
			max = distance[i];
		}
	}
	return index;
}

//Analogicznie do reprezentacji listowej
void Dijkstra::createShortestPath(GraphAdjacencyMatrix *graph, int startingNode)
{	
	int ** adjacencyMatrix = graph->getAdjacencyMatrix(), numberOfNodes = graph->getNumberOfNodes(), u,
		*distance = new int[numberOfNodes], *parent = new int[numberOfNodes];
	bool *visited = new bool[numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		distance[i] = INF;
		parent[i] = -1;
		visited[i] = false;
	}

	distance[startingNode] = 0;

	for (int n = 0; n < numberOfNodes; n++)
	{
		if ((u = findMin(numberOfNodes, distance, visited)) == -1)
			break;
		for (int i = 0; i<numberOfNodes;i++)
		{
			//dodatkowo sprawdzamy czy krawedz istnieje
			if (!visited[i] && adjacencyMatrix[u][i]!=INF)
			{
				if (distance[i] >(distance[u] + adjacencyMatrix[u][i]))
				{
					distance[i] = distance[u] + adjacencyMatrix[u][i];
					parent[i] = u;
				}
			}
		}
		visited[u] = true;
	}

	showShortestPath(distance, parent, startingNode, numberOfNodes);

	delete[] distance;
	delete[] parent;
	delete[] visited;
}
//wyswietlanie wyniku algorytmu
void Dijkstra::showShortestPath(int *distance, int *parent, int startingVertex, int numberOfNodes)
{
	cout << endl<< "------ DIJKSTRA ------" << endl;
	cout << "START = " << startingVertex << endl;
	cout << "END	DISTANCE	PATH"<<endl;
		
	for (int i = 0; i < numberOfNodes; i++)
	{
		cout.width(4);
		cout << i;
		cout.width(10);
		cout << ((distance[i]==INF)?"inf":to_string(distance[i])); 
		cout << "	";
		getPath(i, startingVertex, parent);
		cout << endl;
	}
}
// rekurencyjne wyswietlanie sciezki
void Dijkstra::getPath(int vertex, int startingVertex, int *parent)
{	
	if (vertex == -1)
		return;
	getPath(parent[vertex], startingVertex, parent);
	cout.width(5);
	cout<< vertex<<" ";	
}