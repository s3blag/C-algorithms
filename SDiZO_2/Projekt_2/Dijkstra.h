#pragma once
#include "GraphAdjacencyMatrix.h"
#include "GraphAdjacencyList.h"
#include <vector>
#include <queue>

class Dijkstra
{

public:
	void createShortestPath(GraphAdjacencyList * graph, int startingNode);
	int findMin(int numberOfVertexes, int * distance, bool * visited);
	void createShortestPath(GraphAdjacencyMatrix * graph, int startingNode);
	void showShortestPath(int * distance, int * parent, int startingVertex, int numberOfNodes);
	void getPath(int vertex, int startingVertex, int * parent);

};

