#pragma once
#include "Cities.h"
#include <vector>
#include <list>

#define INF INT_MAX

class GreedySalesman
{
public:
	void static salesmanProblem(Cities * cities);	
private:
	int static findShortestRoute(int currentCity, int ** adjacencyMatrix, int numberOfCities, std::vector<bool> &visited);
	void static GreedySalesman::showResults(std::list<int> &shortestPath, int distance);
};

