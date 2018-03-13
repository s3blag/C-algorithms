#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <iomanip>
#include <vector>

#include "KnapSack.h"
#include "Items.h"
#include "GreedyKnapSack.h"
#include "BruteKnapSack.h"


#include "Cities.h"
#include "BruteSalesman.h"
#include "GreedySalesman.h"

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void generateMenu();
void knapSackMenu();
void salesmanMenu();
void loadFromFile();
void knapSackFromFileMenu();
void salesmanFromFileMenu();

void bruteKnapSackTest();
void bruteKnapSackTest2();
void greedyKnapSackTest();
void greedySalesmanTest();
void bruteSalesmanTest();
int main()
{
	srand((unsigned int)time(NULL));

	char option;
	do
	{
		cout << endl;
		cout << "############	MENU	 ############" << endl;
		cout << "1.Testuj algorytmy" << endl;
		cout << "2.Wczytaj z pliku" << endl;
		cout << "3.Badaj" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;
		switch (option)
		{
			case '1':
				generateMenu();
				break;
				//Menu wczytywania problemów z pliku
			case '2':
				loadFromFile();
				break;
			case '3':
				//testy
				//greedySalesmanTest();
				//bruteSalesmanTest();
				bruteKnapSackTest2();
				//greedyKnapSackTest();
				break;
		}

	} while (option != '0');
	


    return 0;
}

void generateMenu()
{
	char option;
	do {
		cout << endl;
		cout << "############	TESTUJ ALGORYTMY	 ############" << endl << endl;
		cout << "1.Dyskretny problem plecakowy" << endl;
		cout << "2.Asymetryczny problem komiwojazera" << endl << endl;
		cout << "0.Wyjscie" << endl << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option)
		{
			case '1':
			{	
				knapSackMenu();
			}
			break;
			case '2':
			{
				salesmanMenu();
			}
			break;
		}
	} while (option != '0');
}

void knapSackMenu()
{
	int N = 0, knapSackSize = 0;
	bool sortByValue;
	cout << endl <<"Podaj rozmiar plecaka:";
	while (knapSackSize<2)
		cin >> knapSackSize;
	cout << endl << "Podaj ilosc przedmiotow:";
	while (N<2)
		cin >> N;

	KnapSack *knapSack = new KnapSack(knapSackSize);
	Items *items = new Items(N, knapSackSize);

	BruteKnapSack::knapSackProblem(items, knapSack);
	GreedyKnapSack::knapSackProblem(items, knapSack, sortByValue = false);
	GreedyKnapSack::knapSackProblem(items, knapSack, sortByValue = true);

	delete knapSack;
	delete items;
}

void salesmanMenu()
{	
	int numberOfCities = 0, density = 0;
	cout << "Podaj ilosc miast:" << endl;
	while (numberOfCities<1)
		cin >> numberOfCities;
	
	Cities *cities = new Cities();
	cities->generateCities(numberOfCities);
	cities->showCities();

	BruteSalesman::salesmanProblem(cities);
	GreedySalesman::salesmanProblem(cities);

	delete cities;

}

void loadFromFile()
{	
	char option;
	do {
		cout << endl;
		cout << "############	WCZYTAJ Z PLIKU	 ############" << endl << endl;
		cout << "1.Dyskretny problem plecakowy" << endl;
		cout << "2.Asymetryczny problem komiwojazera" << endl << endl;
		cout << "0.Wyjscie" << endl << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option)
		{
			case '1':
			{
				knapSackFromFileMenu();
			}
			break;
			case '2':
			{
				salesmanFromFileMenu();
			}
			break;
		}
	} while (option != '0');
	
}

void knapSackFromFileMenu()
{
	bool sortByValue;
	string filename;
	ifstream file;
	int	knapSackSize, N;

	cout << "Podaj pelna nazwe pliku: " << endl;
	cin >> filename;

	file.open(filename);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (file.good())
	{
		int weight, value;
		file >> knapSackSize;
		KnapSack *knapSack = new KnapSack(knapSackSize);
		file >> N;
		Items *items = new Items();

		vector<Items::Item> *vectorOfItems = new vector<Items::Item>;
	
		// Pêtla wczytuj¹ca wartoœci 
		while (file.good())
		{
			file >> weight;
			file >> value;
			
			vectorOfItems->push_back(Items::Item{ weight, value });
		}
		
		items->loadItemsFromFile(vectorOfItems, N);

		BruteKnapSack::knapSackProblem(items, knapSack);
		GreedyKnapSack::knapSackProblem(items, knapSack, sortByValue = false);
		GreedyKnapSack::knapSackProblem(items, knapSack, sortByValue = true);
		
		delete knapSack;
		delete items;

	}
	else
		cout << " Nie ma takiego pliku ";
}

void salesmanFromFileMenu()
{
	Cities *cities = new Cities();
	string filename;

	cout << "Podaj pelna nazwe pliku: " << endl;
	cin >> filename;
	if (cities->loadCitiesFromFile(filename))
	{
		cities->showCities();
		BruteSalesman::salesmanProblem(cities);
		GreedySalesman::salesmanProblem(cities);
	}
	else
		cout << "nie znaleziono pliku";

	delete cities;
}

// ------------------------------------------------ METODY POMIARU CZASU ------------------------------------------------ 

void startCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double getCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

// ------------------------------------------------ METODY TESTUJ¥CE ------------------------------------------------ 

void greedySalesmanTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Cities *cities;
	for (int numberOfCities = 10000; numberOfCities <= 30000; numberOfCities += 5000)
	{
		cout << " numberOfCities = " << numberOfCities << "-----------------" << endl;
		string fileName = "greedySailsman.txt";
		file.open(fileName, ios::out | ios::app);
		for (int j = 0; j < 50; j++)
		{
			cout << "  j = " << j << endl;
			cities = new Cities();
			cities->generateCities(numberOfCities);
			cout << endl << "START! " << endl;
			startCounter();
			GreedySalesman::salesmanProblem(cities);
			tmp = getCounter();
			cout << endl << "STOP! " << tmp << " ms" << endl;
			elapsed += tmp;

			delete cities;
		}

		if (file.good() == true)
		{

			file << setprecision(0) << elapsed / 50 << endl;
		}
		elapsed = 0;
		file.close();

	}
}

void bruteSalesmanTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Cities *cities;
	for (int numberOfCities = 10; numberOfCities <= 15; numberOfCities++)
	{
		cout << " numberOfCities = " << numberOfCities << "-----------------" << endl;
		string fileName = "bruteSailsman.txt";
		file.open(fileName, ios::out | ios::app);
		for (int j = 0; j < 25; j++)
		{
			cout << "  j = " << j << endl;
			cities = new Cities();
			cities->generateCities(numberOfCities);
			cout << endl << "START! " << endl;
			startCounter();
			BruteSalesman::salesmanProblem(cities);
			tmp = getCounter();
			cout << endl << "STOP! " << tmp << " ms" << endl;
			elapsed += tmp;

			delete cities;
		}

		if (file.good() == true)
		{

			file << setprecision(0) << elapsed / 25 << endl;
		}
		elapsed = 0;
		file.close();

	}
}


void bruteKnapSackTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Items * items;

	for (int sackSize = 100000; sackSize < 1000001; sackSize += 400000)
	{
		if (sackSize == 900000)
			sackSize = 1000000;
		KnapSack *knapSack = new KnapSack(sackSize);
		for (int numberOfItems = 20; numberOfItems <= 28; numberOfItems += 2)
		{
			cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
			string fileName = "bruteKnapsack" + to_string(sackSize) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 50; j++)
			{
				cout << "  j = " << j << endl;
				items = new Items();
				items->generateItems(numberOfItems, knapSack->getCapacity());
				cout << endl << "START! " << endl;
				startCounter();
				BruteKnapSack::knapSackProblem(items, knapSack);
				tmp = getCounter();
				cout << endl << "STOP! " << tmp << " ms" << endl;
				elapsed += tmp;

				delete items;

			}

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed / 50 << endl;
			}
			elapsed = 0;
			file.close();

		}
		delete knapSack;
		elapsed = 0;
	}
}

void greedyKnapSackTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Items * items;


	for (int sackSize = 100000; sackSize <1000001; sackSize += 400000)
	{
		if (sackSize == 900000)
			sackSize = 1000000;
		KnapSack *knapSack = new KnapSack(sackSize);
		for (int numberOfItems = 200000; numberOfItems <= 1000001; numberOfItems += 200000)
		{

			cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
			string fileName = "greedyKnapsackByValue" + to_string(sackSize) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 50; j++)
			{
				cout << "  j = " << j << endl;
				items = new Items();
				items->generateItems(numberOfItems, knapSack->getCapacity());
				cout << endl << "START! " << endl;
				startCounter();
				GreedyKnapSack::knapSackProblem(items, knapSack, true);
				tmp = getCounter();
				cout << endl << "STOP! " << tmp << " ms" << endl;
				elapsed += tmp;

				delete items;

			}

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed / 50 << endl;
			}
			elapsed = 0;
			file.close();

		}

		tmp = 0;
		elapsed = 0;
		for (int numberOfItems = 200000; numberOfItems <= 1000001; numberOfItems += 200000)
		{
			cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
			string fileName = "greedyKnapsackByFactor" + to_string(sackSize) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 50; j++)
			{
				cout << "  j = " << j << endl;
				items = new Items();
				items->generateItems(numberOfItems, knapSack->getCapacity());
				cout << endl << "START! " << endl;
				startCounter();
				GreedyKnapSack::knapSackProblem(items, knapSack, false);
				tmp = getCounter();
				cout << endl << "STOP! " << tmp << " ms" << endl;
				elapsed += tmp;

				delete items;

			}

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed / 50 << endl;
			}
			elapsed = 0;
			file.close();

		}
		delete knapSack;
	}
}


void bruteKnapSackTest2()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Items * items;

	
		int	sackSize = 1000;
		KnapSack *knapSack = new KnapSack(sackSize);
		int numberOfItems=34;
		
			cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
			string fileName = "bruteKnapsackTEST" + to_string(sackSize) + ".txt";
			file.open(fileName, ios::out | ios::app);
			int j = 1;
				cout << "  j = " << j << endl;
				items = new Items();
				items->generateItems(numberOfItems, knapSack->getCapacity());
				cout << endl << "START! " << endl;
				startCounter();
				BruteKnapSack::knapSackProblem(items, knapSack);
				tmp = getCounter();
				cout << endl << "STOP! " << tmp << " ms" << endl;
				elapsed += tmp;

				delete items;

			

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed << endl;
			}
			elapsed = 0;
			file.close();

		
		delete knapSack;
	
	
}