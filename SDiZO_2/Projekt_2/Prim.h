#pragma once
#include <queue>
#include <vector>
#include "GraphAdjacencyMatrix.h"
#include "GraphAdjacencyList.h"
#include <iostream>
#include <iomanip>
class Prim
{
private:
	//struktura krawedzi w drzewie MST i kolejce priorytetowej
	struct MstEdge
	{
		int node1;
		int node2;
		int	weight;
	};
	//Sortowanie wg. wag znajdujacych sie w strukturze umieszczonej w kolejce
	struct CompareEdge
	{
		bool operator ()(const MstEdge &A, const MstEdge &B)
		{
			return A.weight > B.weight;
		}
	};
	
public:
	void createMST(GraphAdjacencyMatrix * graph);
	void showMst(std::forward_list<Prim::MstEdge> *mst, int numberOfNodes);
	void createMST(GraphAdjacencyList * graph);
	};
	

