#include "stdafx.h"
#include "GreedySalesman.h"

using namespace std;

void GreedySalesman::salesmanProblem(Cities *cities)
{
	int **adjacencyMatrix = cities->getCities(),numberOfCities = cities->getNumberOfCities(),
		currentCity = 0, nextCity, currentDistance = 0, bestDistance = INF;
	vector<bool> visited (numberOfCities, false);
	list<int> bestPath;
	list<int> currentPath;

	int startingCity = 0;
	visited[startingCity] = true;
	currentCity = startingCity;
	//koniec p�tli je�li przejdziemy przez wszystkie miasta
	for (int i = 0; i < numberOfCities; i++)
	{
		//je�li dotarli�my do ostatniego miasta, to dodajemy drog� z miasta ko�cowego do pocz�tkowego
		if (i == numberOfCities-1)
		{	
			currentPath.push_back(currentCity);
			nextCity = startingCity;
			currentPath.push_back(startingCity);
			currentDistance += adjacencyMatrix[currentCity][nextCity];
		}
		else
		{	
			currentPath.push_back(currentCity);
			//znajdujemy drog� najkr�tsz� z obecnego miasta do miasta jeszcze nierozpatrzonego
			nextCity = findShortestRoute(currentCity, adjacencyMatrix, numberOfCities, visited);
			//oznaczamy znalezione miasto jako rozpatrzone
			visited[nextCity] = true;
			//zwi�kszamy przebyty dystans o d�ugo�� drogi do znalezionego miasta
			currentDistance += adjacencyMatrix[currentCity][nextCity];
			currentCity = nextCity;
		}
	}
	
	showResults(currentPath, currentDistance);
}

//Znajdowanie drogi najkr�tszej z danego miasta do miasta jeszcze nierozpatrzonego
int GreedySalesman::findShortestRoute(int currentCity, int **adjacencyMatrix, int numberOfCities, vector<bool> &visited)
{
	int index = 0, min = INF;
	for (int i = 0; i < numberOfCities; i++)
	{
		if (adjacencyMatrix[currentCity][i]<min && !visited[i])
		{
			index = i;
			min = adjacencyMatrix[currentCity][i];
		}
	}
	return index;
}

void GreedySalesman::showResults(list<int> &bestPath, int distance)
{
	cout << endl << " - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << endl << "       ALGORYTM ZACHLANNY " << endl;
	cout << endl << " Rozwiazanie: " << endl;

	for (int city : bestPath)
		cout << city << "  ";
	cout << endl;
	cout << " Dystans: " << distance << endl;

}