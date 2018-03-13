#include "stdafx.h"
#include "Cities.h"
using namespace std;


Cities::~Cities()
{
	for (int i = 0; i < numberOfCities; ++i)
		delete[] adjacencyMatrix[i];
}

//Generacja miast (grafu pe³nego skierowanego, bez pêtli)
bool Cities::generateCities(int numberOfCities )
{	
	int randomDistance;
	adjacencyMatrix = new int*[numberOfCities];
	
	//dopoki ilosc obecnych drog jest mniejsza od zadanej wielkosci grafu to generujemy kolejne drogi
	for (int i = 0; i < numberOfCities; i++)
	{
		adjacencyMatrix[i] = new int[numberOfCities];
	
		for (int j = 0; j < numberOfCities; j++)
		{
			//sprawdzenie czy droga istnieje juz w grafie oraz czy losowa droga nie jest petla
			if (i!=j)
			{	//dodanie drogi
				randomDistance = 1 + rand() % (2 * numberOfCities);
				adjacencyMatrix[i][j] = randomDistance;
			}
			else
			{
				adjacencyMatrix[i][j] = INF;
			}

		}

	}
	//aktualizacja pól charakteryzuj¹cych symulacj¹ sieci miast
	
	this->numberOfCities = numberOfCities;
	return true;
	}

bool Cities::loadCitiesFromFile(string name)
{
	ifstream file;
	int  weight;

	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci miast
	file >> numberOfCities;

	// Utworzenie nowej tablicy
	adjacencyMatrix = new int*[numberOfCities];

	// Pêtla wczytuj¹ca wartoœci 
	
	for (int i = 0; i < numberOfCities; i++)
	{
		adjacencyMatrix[i] = new int[numberOfCities];

		for (int j = 0; j < numberOfCities; j++)
		{
			file >> weight;
			if (weight == 0)
				weight = INF;
			adjacencyMatrix[i][j] = weight;
		}
	}
	
	return true;
}


//Wyswietlenie grafu
void Cities::showCities()
{
	for (int col = 0; col < numberOfCities; col++)
	{
		cout.width(7);
		cout << " " << col;
	}
	for (int row = 0; row < numberOfCities; row++)
	{

		cout << endl << row << "   ";
		for (int column = 0; column < numberOfCities; column++)
		{
			cout.width(5);
			cout << ((adjacencyMatrix[row][column] == INF) ? "inf" : to_string(adjacencyMatrix[row][column])) << "   ";
		}
	}
	cout << endl;
}

//Gettery

int** Cities::getCities()
{
	return adjacencyMatrix;
}

int Cities::getNumberOfCities()
{
	return numberOfCities;
}

