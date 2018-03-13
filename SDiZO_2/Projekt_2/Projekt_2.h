/*#pragma once
#include "GraphAdjacencyMatrix.h"
class Projekt_2
{
public:
	template < typename T >
	void generateAdjMatGraph(T *graphObject)
	{
		int numberOfNodes = 0;
		cout << "Podaj ilosc wierzcholkow:" << endl;
		while (numberOfNodes<1)
			cin >> numberOfNodes;
		graphObject->createGraph(numberOfNodes);
		graphObject->showGraph();
	}
};
*/