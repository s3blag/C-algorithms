#include <string>
#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
//tablica dynamiczna z danymi
int * arrayObj ;
//ilosc elementow tablicy
int numberOfElements;
int happened=0;


//konstruktor
Array::Array()
{
	numberOfElements = 0;
	arrayObj = new int[0];
}

//destruktor
Array::~Array()
{
	numberOfElements = 0;
	delete[] arrayObj;
}

//metoda odpowiedzialna za dodawanie elementu na koncu tablicy
void Array::addElementsE(int value)
{	
	int *arrayObj2 = new int[numberOfElements];
	memcpy(arrayObj2, arrayObj, numberOfElements * 4);
	delete[] arrayObj;
	numberOfElements++;
	arrayObj = new int[numberOfElements];
	memcpy(arrayObj, arrayObj2, (numberOfElements - 1) * 4);
	delete[] arrayObj2;
	*(arrayObj+numberOfElements - 1) = value;
}
//metoda odpowiedzialna za dodawanie elementu po œrodku tablicy
void Array::addElementsM( int value, int position)
{
	if (position >0 && position < numberOfElements - 1) 
	{
		int *arrayObj2 = new int[numberOfElements];
		memcpy(arrayObj2, arrayObj, numberOfElements * 4);
		delete[] arrayObj;
		numberOfElements++;
		arrayObj = new int[numberOfElements];
		memcpy(arrayObj, arrayObj2, position * 4);
		*(arrayObj + position) = value;
		memcpy(arrayObj + position + 1, arrayObj2 + position, (numberOfElements - 1 - position) * 4);
		delete[] arrayObj2;
	}
}

//metoda odpowiedzialna za dodawanie elementu na pocz¹tku tablicy
void Array::addElementsB(int value)
{	//tablica pomocnicza
	int *arrayObj2 = new int[numberOfElements];
	memcpy(arrayObj2, arrayObj, numberOfElements * 4);
	delete[] arrayObj;
	numberOfElements++;
	arrayObj = new int[numberOfElements];
	memcpy(arrayObj+1, arrayObj2, (numberOfElements - 1) * 4);
	delete[] arrayObj2;
	*(arrayObj) = value;
}

//metoda odpowiedzialna za wyœwietlanie tablicy
string Array::showArray()
{	
	string description = "";
	for (int i = 0; i < numberOfElements; i++)
	{
		description += to_string(arrayObj[i]) + "	";
	}
	return description;
}

//metoda odpowiedzialna za usuwanie elementu ze srodkowej czesci tablicy
void Array::deleteElementsM(int position)
{
	if (numberOfElements > 0 && position>0 && position<numberOfElements-1)
	{	//tablica pomocnicza
		int *arrayObj2 = new int[numberOfElements];
		memcpy(arrayObj2, arrayObj, numberOfElements * 4);
		delete[] arrayObj;
		numberOfElements--;
		arrayObj = new int[numberOfElements];
		memcpy(arrayObj, arrayObj2, position * 4);
		memcpy(arrayObj + position, arrayObj2 + position + 1, (numberOfElements - position) * 4);
		delete[] arrayObj2;
	}
}
//metoda odpowiedzialna za usuwanie elementu z poczatku tablicy
void Array::deleteElementsB()
{
	if (numberOfElements > 0)
	{
		int *arrayObj2 = new int[numberOfElements];
		memcpy(arrayObj2, arrayObj + 1, (numberOfElements - 1) * 4);
		delete[] arrayObj;
		arrayObj = new int[numberOfElements - 1];
		memcpy(arrayObj, arrayObj2, (numberOfElements - 1) * 4);
		delete[] arrayObj2;
		numberOfElements--;
	}
}

//metoda odpowiedzialna za usuwanie elementu z konca tablicy
void Array::deleteElementsE()
{
	if (numberOfElements > 0)
	{
		int *arrayObj2 = new int[numberOfElements - 1];
		memcpy(arrayObj2, arrayObj, (numberOfElements - 1) * 4);
		delete[] arrayObj;
		arrayObj = new int[numberOfElements - 1];
		memcpy(arrayObj, arrayObj2, (numberOfElements - 1) * 4);
		delete[] arrayObj2;
		numberOfElements--;
	}
}

//metoda odpowiedzialna za przeszukiwanie tablicy
bool Array::searchElements(int value)
{
	bool wasFound = false;
	for (int i = 0; i < numberOfElements; i++)
	{
		if (arrayObj[i] == value)
		{
			wasFound = true;
			break;
		}
	}
	return wasFound;
}


//metoda odpowiedzialna za wczytanie tablicy z pliku
bool Array::loadDataFromFile(string name)
{
	
	// Otwarcie pliku
	ifstream file;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
		// Pobranie informacji o iloœci elementów
		file >> numberOfElements;
	
		// Utworzenie nowej tablicy

	arrayObj = new int[numberOfElements];

	// Pêtla wczytuj¹ca wartoœci 
	for (int i = 0; i < numberOfElements; i++)
	{
		if (file.good())
			file >> *(arrayObj + i);
	}

	return true;

}

//getter rozmiaru tablicy
int Array::getSize()
{
	return numberOfElements;
}

//generowanie tablicy z losowymi danymi
void Array::generateRandomArray(int size)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(1, 1000 + 2*size); // distribute results between
												 // 1 and 1000000 inclusive
	arrayObj = new int[size];
	for (int i = 0; i < size; i++)
	{
		arrayObj[i] = dist(gen);
	}
	numberOfElements = size;

}

//metoda zwraca element pod indexem
int Array::getElement(int index)
{
	return arrayObj[index];
}
//metoda zapisu tablicy do pliku
/*
void Array::saveDataToFile(string name, string population)
{
	string fileName = "GeneratedArray_" + population + ".txt";
		
	fstream file;
	file.open(fileName, ios::out | ios::app);

	if (file.good() == true)
	{
		file << numberOfElements << endl;
	}

	for (int i = 0; i < numberOfElements; i++)
	{
		if (file.good())
			file << *(arrayObj + i);
	}

	file.close();


}
*/