/*
	Sebastian £¹giewski
	nr. indeksu 226173
*/

#include "stdafx.h"
#include "Projekt_2.h"
#include <iostream>
#include <conio.h>
#include "GraphAdjacencyMatrix.h"
#include "GraphAdjacencyList.h"
#include <time.h>
#include "Prim.h"
#include "Dijkstra.h"
#include <fstream>
#include <iomanip>
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void startCounter();
double getCounter();
void generateGraphMenu();

template < typename T >
bool generateUndirectedGraph(T *graphObject);
template < typename T >
bool generateDirectedGraph(T *graphObject);

void primTestMatrix();
void primTestList();
void dijkstraTestMatrix();
void dijkstraTestList();

void loadFromFile();

// ------------------------------------------------ MENU ------------------------------------------------ 

int main()
{
	srand((unsigned int)time(NULL));

	char option;
	do 
	{
		cout << endl;
		cout << "############	MENU	 ############" << endl;
		cout << "1.Generuj graf" << endl;
		cout << "2.Wczytaj z pliku" << endl;
		cout << "3.Badaj" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;
		switch (option)
		{	
			//Menu generacji losowego grafu
			case '1':
				generateGraphMenu();
				break;
			//Menu wczytywania grafu z pliku
			case '2':
				loadFromFile();
				break;
			//Pomiary
			case '3':
				//dijkstraTestList();
				//dijkstraTestMatrix();
				primTestMatrix();
				//primTestList();
				break;
		}

	} while (option != '0');

	return 0;
}

//Menu generowania losowych grafów
void generateGraphMenu()
{
	char option;
	do {
		cout << endl;
		cout << "############	GENEROWANIE GRAFU	 ############" << endl << endl;
		cout << "Graf nieskierowany: " << endl;
		cout << "1.Macierz sasiedztw" << endl;
		cout << "2.Lista sasiedztw" << endl << endl;
		cout  << "Graf skierowany: " << endl;
		cout << "3.Macierz sasiedztw" << endl;
		cout << "4.Lista sasiedztw" << endl << endl;
		cout << "0.Wyjscie" << endl << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) 
		{
			case '1':
			{
				GraphAdjacencyMatrix *graphAdjMat = new GraphAdjacencyMatrix();
			
				if (generateUndirectedGraph<GraphAdjacencyMatrix>(graphAdjMat))
				{
					graphAdjMat->showGraph();
					Prim *prim = new Prim();
					prim->createMST(graphAdjMat);
					delete graphAdjMat;
					delete prim;
				}
			}
				break;

			case '2':
			{
				GraphAdjacencyList *graphAdjList = new GraphAdjacencyList();
				if (generateUndirectedGraph<GraphAdjacencyList>(graphAdjList))
				{	
					graphAdjList->showGraph();
					Prim *prim = new Prim();
					prim->createMST(graphAdjList);
					delete graphAdjList;
					delete prim;
				}
			}
				break;
			case '3':
			{
				GraphAdjacencyMatrix *graphAdjMatrix = new GraphAdjacencyMatrix();
				if (generateDirectedGraph<GraphAdjacencyMatrix>(graphAdjMatrix))
				{
					graphAdjMatrix->showGraph();
					Dijkstra *dijkstra = new Dijkstra();
					dijkstra->createShortestPath(graphAdjMatrix, rand() % graphAdjMatrix->getNumberOfNodes());
					delete dijkstra;
					delete graphAdjMatrix;
				}
			}
				break;
			case '4':
			{
				GraphAdjacencyList *graphAdjList = new GraphAdjacencyList();
				if (generateDirectedGraph<GraphAdjacencyList>(graphAdjList))
				{
					graphAdjList->showGraph();
					Dijkstra *dijkstra = new Dijkstra();
					dijkstra->createShortestPath(graphAdjList, rand() % graphAdjList->getNumberOfNodes());
					delete dijkstra;
					delete graphAdjList;
				}
			}
				break;
		}
	} while (option != '0');
}

//Menu wczytywania grafu z pliku
void loadFromFile()
{
	GraphAdjacencyMatrix *graphMatrix = new GraphAdjacencyMatrix();
	GraphAdjacencyList *graphList = new GraphAdjacencyList();
	string filename;

	cout << "Podaj pelna nazwe pliku: " << endl;	
	cin >> filename;
	if (!graphList->loadDataFromFile(filename))
		cout << "nie znaleziono pliku";
	else
		graphMatrix->loadDataFromFile(filename);
	
	char option;
	do {
		cout << endl;
		cout << "############	OPCJE	 ############" << endl;
		cout << "1.Wyswietl w obu reprezentacjach" << endl;
		cout << "2.Prim" << endl;
		cout << "3.Dijkstra" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;
		switch (option) {
			case '1':
			{	graphMatrix = new GraphAdjacencyMatrix();
				graphList = new GraphAdjacencyList();

				if (!graphList->loadDataFromFile(filename))
					cout << "nie znaleziono pliku";
				else
				{
					graphMatrix->loadDataFromFile(filename);
					cout << endl << "----- MACIERZOWO -----" << endl << endl;
					graphMatrix->showGraph();
					cout << endl << endl << "----- LISTOWO -----" << endl << endl;
					graphList->showGraph();

					delete graphList;
					delete graphMatrix;
				}
			}
				break;
			case '2':
			{	
				cout << endl << "----- LISTOWO -----" << endl;
				graphList= new GraphAdjacencyList();
				graphList->loadUndirectedFromFile(filename);
				graphList->showGraph();
				Prim *prim2 = new Prim();
				prim2->createMST(graphList);
				delete prim2;
				delete graphList;
				
				cout << endl << "----- MACIERZOWO -----" << endl;
				graphMatrix = new GraphAdjacencyMatrix();
				graphMatrix->loadUndirectedFromFile(filename);
				graphMatrix->showGraph();
				Prim *prim1 = new Prim();
				prim1->createMST(graphMatrix);
				delete prim1;
				delete graphMatrix;

			}
				break;
			case '3':
			{	
				graphMatrix = new GraphAdjacencyMatrix();
				graphMatrix->loadDirectedFromFile(filename);
				graphMatrix->showGraph();
				graphList = new GraphAdjacencyList();
				graphList->loadDirectedFromFile(filename);
				graphList->showGraph();

				int startingVertex = graphMatrix->getStartingVertex();
				cout << endl << "----- LISTOWO -----" << endl;
				Dijkstra *dijkstra = new Dijkstra();
				dijkstra->createShortestPath(graphList, startingVertex);
				delete dijkstra;
				delete graphList;

				cout << endl << "----- MACIERZOWO -----" << endl;
				dijkstra = new Dijkstra();
				dijkstra->createShortestPath(graphMatrix, startingVertex);
				delete dijkstra;		
				delete graphMatrix;
			}
				break;
		}

	} while (option != '0');
}

// ------------------------------------------------ POMIARY ------------------------------------------------ 

void primTestMatrix()
{
	double tmp = 0;
	double  elapsed = 0;
	fstream file;
	Prim *prim;
	GraphAdjacencyMatrix *graph;
	for (int density = 25; density < 101; density += 25)
	{
		if (density == 100)
			density = 99;
		for (int numberOfNodes = 40; numberOfNodes < 201; numberOfNodes += 40)
		{
			string fileName = "PRIM_" + to_string(numberOfNodes) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 100; j++)
			{
				graph = new GraphAdjacencyMatrix();
				graph->createUndirectedGraph(numberOfNodes, density);
				prim = new Prim();
				
				startCounter();
				prim->createMST(graph);
				tmp = getCounter();
				elapsed += tmp;

				delete prim;
				delete graph;
			}

			if (file.good() == true)
			{	if(density==25)
					file << "---- MACIERZ ----" << endl;
				file << setprecision(0) << elapsed / 100 <<"  "<<density<<endl;
			}
			elapsed = 0;
			file.close();
		}
	}
}



void primTestList()
{
	double tmp = 0;
	double  elapsed = 0;
	fstream file;
	Prim *prim;
	GraphAdjacencyList *graph;

	for (int density = 25; density < 101; density += 25)
	{
		if (density == 100)
			density = 99;
		for (int numberOfNodes = 40; numberOfNodes < 201; numberOfNodes += 40)
		{
			string fileName = "PRIM_" + to_string(numberOfNodes) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 100; j++)
			{
				graph = new GraphAdjacencyList();
				graph->createUndirectedGraph(numberOfNodes, density);
				prim = new Prim();
				
				startCounter();
				prim->createMST(graph);
				tmp = getCounter();
				elapsed += tmp;

				delete prim;
				delete graph;
			}

			if (file.good() == true)
			{	if (density == 25)
					file << "---- LISTA ----" << endl;
				file << setprecision(0) << elapsed / 100 << "  " << density<< endl;
			}

			elapsed = 0;

			file.close();
		}
	}
	
}

void dijkstraTestList()
{
	double  elapsed = 0, tmp = 0;
	fstream file;
	Dijkstra *dijkstra;
	GraphAdjacencyList *graph;

	for (int density = 25; density < 101; density += 25)
	{
		if (density == 100)
			density = 99;

		for (int numberOfNodes = 400; numberOfNodes < 2001; numberOfNodes += 400)
		{
			string fileName = "Dijkstra_" + to_string(numberOfNodes) + ".txt";
			file.open(fileName, ios::out | ios::app);

			for (int j = 0; j < 100; j++)
			{
				graph = new GraphAdjacencyList();
				graph->createDirectedGraph(numberOfNodes, density);
				dijkstra = new Dijkstra();

				startCounter();
				dijkstra->createShortestPath(graph, rand() % numberOfNodes);
				tmp = getCounter();
				elapsed += tmp;

				delete dijkstra;
				delete graph;
			}

			if (file.good() == true)
			{
				if (density == 25)
					file << "---- LISTA ----" << endl;
				file << fixed << setprecision(5) << elapsed / 100 << "   " << density << endl;
			}
			elapsed = 0;
			file.close();
		}
	}
}


void dijkstraTestMatrix()
{
	double tmp = 0;
	double  elapsed = 0;
	fstream file;
	Dijkstra *dijkstra;
	GraphAdjacencyMatrix *graph;
	for (int density = 25; density < 101; density += 25)
	{
		if (density == 100)
			density = 99;
		for (int numberOfNodes = 400; numberOfNodes < 2001; numberOfNodes += 400)
		{
			string fileName = "Dijkstra_" + to_string(numberOfNodes) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 100; j++)
			{
				graph = new GraphAdjacencyMatrix();
				graph->createDirectedGraph(numberOfNodes, density);
				dijkstra = new Dijkstra();

				startCounter();
				dijkstra->createShortestPath(graph, rand() % numberOfNodes);
				tmp = getCounter();
				elapsed += tmp;

				delete dijkstra;
				delete graph;
			}
			
			if (file.good() == true)
			{	
				if(density==25)
					file << "---- MACIERZ ----" << endl;
				file << setprecision(0) << elapsed / 100 <<"   "<<density<<endl;
			}
			
			elapsed = 0;
			file.close();
		}
	}
}

// ------------------------------------------------ GENEROWANIE WYBRANEGO RODZAJU GRAFÓW ------------------------------------------------ 

template < typename T >
bool generateUndirectedGraph(T *graphObject)
{
	int numberOfNodes = 0, density = 0;
	cout << "Podaj ilosc wierzcholkow:" << endl;
	while (numberOfNodes<1)
		cin >> numberOfNodes;
	cout << "Podaj gestosc grafu(%):" << endl;
	while (density<1 || density>100)
		cin >> density;
	return graphObject->createUndirectedGraph(numberOfNodes, density);
}

template < typename T >
bool generateDirectedGraph(T *graphObject)
{
	int numberOfNodes = 0, density = 0;
	cout << "Podaj ilosc wierzcholkow:" << endl;
	while (numberOfNodes<1)
		cin >> numberOfNodes;
	cout << "Podaj gestosc grafu(%):" << endl;
	while (density<1 || density>100)
		cin >> density;
	return graphObject->createDirectedGraph(numberOfNodes, density);
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