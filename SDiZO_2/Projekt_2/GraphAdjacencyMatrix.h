#pragma once
#include <limits>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>

#define INF INT_MAX

class GraphAdjacencyMatrix
{
public:
	~GraphAdjacencyMatrix();
	bool createUndirectedGraph(int numberOfNodes, int density);
	bool createDirectedGraph(int numbOfNodes, int density);
	int initializeUndirectedAdjacencyMatrix(int numberOfNodes);
	int initializeDirectedAdjacencyMatrix(int numberOfNodes);
	bool loadDataFromFile(std::string name);
	bool loadDirectedFromFile(std::string name);
	bool loadUndirectedFromFile(std::string name);
	void showGraph();
	int getNumberOfNodes();
	int** getAdjacencyMatrix();
	int getStartingVertex();
private:
	int **adjacencyMatrix;
	int numberOfNodes;
	int numberOfEdges;
	int startingVertex;
};


