#pragma once
#include <forward_list>
#include <iostream>
#include <windows.h>
#include <iterator>
#include <fstream>

class GraphAdjacencyList
{
public:
	~GraphAdjacencyList();
	struct Edge
	{
		int node;
		int weight;
	};
	std::forward_list<GraphAdjacencyList::Edge>* getAdjacencyLists();
	bool searchNodeInList(int value, std::forward_list <GraphAdjacencyList::Edge> list);
	int initializeUndirectedGraph(int numbOfNodes);
	int initializeDirectedGraph(int numbOfNodes);
	bool createUndirectedGraph(int numberOfNodes, int density);
	bool createDirectedGraph(int numbOfNodes, int density);
	int getNumberOfNodes();
	int getStartingVertex();
	bool loadDataFromFile(std::string name);
	bool loadDirectedFromFile(std::string name);
	bool loadUndirectedFromFile(std::string name);
	void showGraph();
private:
	std::forward_list<Edge> *arrayOfLists;
	int numberOfNodes;
	int numberOfEdges;
	int startingVertex;
};

