#include "stdafx.h"
#include "BruteSalesman.h"

using namespace std;

void BruteSalesman::salesmanProblem(Cities *cities)
{
	int **adjacencyMatrix = cities->getCities(), 
		numberOfCities = cities->getNumberOfCities(), 
		tempDistance = 0, j = 0, shortestDistance = INT_MAX, 
		startingCity = 0;
	vector<int> indexes(numberOfCities-1);
	vector<int> bestPath(numberOfCities);

	//inicjalizacja wektora indeksow, ktory bêdzie u¿ywany do permutowania kolejnoœci odwiedzania miast	
	for (int i = 0; i < numberOfCities-1; i++)
		indexes[i] = i+1;

	do {
		//wyznaczanie drogi dla okreœlonej kolejnoœci odwiedzania miast

		tempDistance += adjacencyMatrix[0][indexes[0]];

		for (int i = 0; i < numberOfCities-1; i++)
		{	
			if (i == numberOfCities - 2)
				tempDistance += adjacencyMatrix[indexes[i]][0];
			else
				tempDistance += adjacencyMatrix[indexes[i]][indexes[i+1]];
		}

		//sprawdzenie czy dane rozwi¹zanie jest jak dot¹d najlepsze
		if (tempDistance < shortestDistance)
		{
			bestPath = indexes;
			bestPath.push_back(0);
			shortestDistance = tempDistance;
		}
		
		tempDistance = 0;

	} while (next_permutation(indexes.begin(), indexes.end()));

	showResults(bestPath, shortestDistance);

}

void BruteSalesman::showResults(vector<int> &shortestPath, int distance)
{
	cout << endl << " - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << endl << "       PRZEGLAD ZUPELNY " << endl;
	cout << endl << " Rozwiazanie: " << endl;
	cout << 0 << "  ";
	for (size_t i = 0; i < shortestPath.size(); i++) 
		cout << shortestPath[i] << "  ";
	cout << endl;
	cout << " Dystans: " << distance << endl;

}