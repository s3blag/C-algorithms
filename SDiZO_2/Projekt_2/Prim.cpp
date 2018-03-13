#include "stdafx.h"
#include "Prim.h"

using namespace std;

void Prim::createMST(GraphAdjacencyList *graph)
{
	int node, mstSize = 0, numberOfNodes = graph->getNumberOfNodes();
	bool *visited = new bool[numberOfNodes];
	//kolejka priorytetowa uzyta w algorytmie
	priority_queue < MstEdge, std::vector <MstEdge>, CompareEdge > queue;
	//graf
	forward_list<GraphAdjacencyList::Edge> *adjacencyLists = graph->getAdjacencyLists();
	//drzewo MST
	forward_list<MstEdge> *mst = new forward_list<MstEdge>[numberOfNodes];
	MstEdge edge;

	//Ustawienie wszystkich wierzcholkow na nieodwiedzone
	for (int i = 0; i < numberOfNodes; i++)
	{
		visited[i] = false;
	}

	//wybieramy losowo jeden wierzcholek
	node = rand() % numberOfNodes;
	visited[node] = true;

	//dopokie nie odwiedzilismy wszystkich wierzcholkow to wykonujemy petle
	while (mstSize < numberOfNodes - 1)
	{
		//przeszukujemy sasiadow w celu znalezienia tych nieodwiedzonych (by nie powstal cykl)
		for (forward_list<GraphAdjacencyList::Edge>::const_iterator iterator = adjacencyLists[node].begin(), end = adjacencyLists[node].end(); iterator != end; ++iterator) 
		{
			if (visited[iterator->node] != true)
				queue.push(MstEdge{ node,iterator->node,iterator->weight });
		}
		//pobieramy nieodwiedzona krawedz o najmniejszej wadze z kolejki
		edge = queue.top();
		queue.pop();
		while (visited[edge.node2])
		{
			edge = queue.top();
			queue.pop();
		}
		//dodajemy do MST
		mst[edge.node1].push_front(edge);
		mstSize++;
		node = edge.node2;
		visited[node] = true;
	}

	showMst(mst, numberOfNodes);

	//zwalnianie pamieci
	delete[] mst;
	delete[] visited;
	queue = priority_queue < MstEdge, std::vector <MstEdge>, CompareEdge >();
}


void Prim::createMST(GraphAdjacencyMatrix *graph)
{
	int node, mstSize=0, **adjacencyMatrix = graph->getAdjacencyMatrix();
	int numberOfNodes = graph->getNumberOfNodes();
	bool *visited = new bool[numberOfNodes];
	priority_queue < MstEdge, std::vector <MstEdge>, CompareEdge > queue;
	forward_list<MstEdge> *mst = new forward_list<MstEdge>[numberOfNodes];
	MstEdge edge;

	for (int i = 0; i < numberOfNodes; i++)
	{
		visited[i] = false;
	}
	
	node = rand() % numberOfNodes;
	visited[node] = true;
	
	while (mstSize < numberOfNodes - 1)
	{
		for (int i = 0; i < numberOfNodes; i++)
		{		//jesli krawedz nie zostala juz odwiedzona i istnieje to dodajemy do kolejki
				if (visited[i]!=true && adjacencyMatrix[node][i]!=INF) 
					queue.push(MstEdge{ node,i,adjacencyMatrix[node][i] });					
		}

		edge = queue.top();
		queue.pop();
		while (visited[edge.node2])
		{
			edge = queue.top();
			queue.pop();
		}
		mst[edge.node1].push_front(edge);
		mstSize++;
		node = edge.node2;
		visited[node] = true;
	}
	
	showMst(mst, numberOfNodes);

	delete[] mst;
	delete[] visited;	
	queue = priority_queue < MstEdge, std::vector <MstEdge>, CompareEdge >();
}

//Wyswietlanie MST
void Prim::showMst(forward_list<MstEdge> *mst, int numberOfNodes)
{	
	int value=0;
	cout << endl << endl << " -------------   PRIM  ------------------";
	cout << endl << "Wierzcholek  -  Wierzcholek  Waga" << endl;
	for (int row = 0; row < numberOfNodes; row++)
	{
		for (MstEdge e : mst[row])
		{
			cout << "     " << e.node1 << "       -       " << e.node2 << "        " << e.weight << endl;
			value += e.weight;
		}
	}
	cout << "MST = " << value << endl << endl;
}




