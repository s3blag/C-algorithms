#include "stdafx.h"
#include "BinaryHeap.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;
int currentSize;
//tablica z elementami kopca
int *binaryHeapObj;
//pola pomocnicze do wyswietlania kopca
string upperCorner, bottomCorner, vertical;


BinaryHeap::BinaryHeap()
{
	currentSize = 0;
	//Uzywane do wyswietlania kopca
	upperCorner = bottomCorner = vertical = "  ";
	upperCorner[0] = 218; upperCorner[1] = 196;
	bottomCorner[0] = 192; bottomCorner[1] = 196;
	vertical[0] = 179;
	
	currentSize= 0;
	binaryHeapObj = new int[currentSize+1];
}


BinaryHeap::~BinaryHeap()
{
	currentSize = 0;
	delete[] binaryHeapObj;
}

	
//wyswietlanie kopca
void BinaryHeap::showBinaryHeap(string text1, string text2, int nodeNumber)
{
	
	if (currentSize == 0)
			cout << "Kopiec jest pusty" << endl;
	else
	{
		string text;
	
		if (nodeNumber <= currentSize)
		{
			text = text1;
			if (text2 == upperCorner)
				text[text.length() - 2] = ' ';

			showBinaryHeap(text + vertical, upperCorner, 2 * nodeNumber +1);

			text = text.substr(0, text1.length() - 2);

			cout << text << text2 << binaryHeapObj[nodeNumber-1] << endl;

			text = text1;
			if (text2 == bottomCorner)
				text[text.length() -2 ] = ' ';
			showBinaryHeap(text + vertical, bottomCorner, 2 * nodeNumber);
		}
		
	}
}


//dodawanie elementu do kopca wraz z przebudowa kopca
void BinaryHeap::addElements(int value)
{
	int tempVar;
	currentSize++;
	binaryHeapObj[currentSize - 1] = value;


	int position = currentSize - 1;

	if (currentSize-1 > 0)
	{
		while (position > 0 && binaryHeapObj[position] > binaryHeapObj[(position - 1) / 2])
		{
			tempVar = binaryHeapObj[position];
			binaryHeapObj[position] = binaryHeapObj[(position - 1) / 2];
			binaryHeapObj[(position - 1) / 2] = tempVar;
			position = (position - 1) / 2;
		}
	}
	
	int *binaryHeapObj2 = new int[currentSize];
	memcpy(binaryHeapObj2, binaryHeapObj, (currentSize) * 4);
	delete[] binaryHeapObj;
	binaryHeapObj = new int[currentSize+1];
	memcpy(binaryHeapObj, binaryHeapObj2, (currentSize) * 4);
	delete[] binaryHeapObj2;
}


//usuwanie elementu ze szczytu kopca wraz z przebudowa kopca
void BinaryHeap::deleteElement()
{
	int i;
	binaryHeapObj[0] = binaryHeapObj[currentSize - 1];
	currentSize--;
	i = 0;
	int biggerChild;
	int temp;
	while (i * 2 + 1 <= currentSize - 1 || i * 2 + 2 <= currentSize - 1)
	{
		if (binaryHeapObj[2 * i + 1] > binaryHeapObj[2 * i + 2])
		{
			biggerChild = 2 * i + 1;
		}
		else
		{
			biggerChild = 2 * i + 2;
		}
		if (binaryHeapObj[i] <binaryHeapObj[biggerChild])
		{
			temp = binaryHeapObj[i];
			binaryHeapObj[i] = binaryHeapObj[biggerChild];
			binaryHeapObj[biggerChild] = temp;
			i = biggerChild;
		}
		else
			break;

	}
	int * binaryHeapObj2 = new int[currentSize];
	memcpy(binaryHeapObj2, binaryHeapObj, currentSize * 4);
	delete[] binaryHeapObj;
	binaryHeapObj = new int[currentSize+1];
	memcpy(binaryHeapObj, binaryHeapObj2, currentSize * 4);
	delete[] binaryHeapObj2;

}


//getter rozmiaru kopca
int BinaryHeap::getSize()
{
	return currentSize;
}


//metoda odpowiedzialna za przeszukiwanie kopca
bool BinaryHeap::search(int value)
{
	bool wasFound = false;
	for (int i = 0; i < currentSize; i++)
	{
		if (value == binaryHeapObj[i])
		{
			wasFound = true;
			break;
		}
	}
	return wasFound;
}

//metoda odpowiedzialna za wczytanie gotowego kopca z pliku
bool BinaryHeap::loadDataFromFile(string name)
{	
	// Otwarcie pliku
	ifstream file;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	int binHeapSize;
	// Pobranie informacji o iloœci elementów
	file >> binHeapSize;
	// Utworzenie nowej tablicy
	// POBRANIE WARTOŒCI Z PLIKU POWODUJE UTRATÊ OBECNEJ TABLICY!
	binaryHeapObj = new int[binHeapSize];

	// Pêtla wczytuj¹ca wartoœci z tablicy
	for (int i = 0; i < binHeapSize; i++)
	{
		if (file.good())
			file >> *(binaryHeapObj + i);
	}
	currentSize = binHeapSize;
	return true;
}


bool BinaryHeap::loadAndBuildDataFromFile(string name)
{
	// Otwarcie pliku
	ifstream file;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	int binHeapSize;
	// Pobranie informacji o iloœci elementów
	file >> binHeapSize;
	
	// Utworzenie nowej tablicy
	binaryHeapObj = new int[binHeapSize];
	int value;
	// Pêtla wczytuj¹ca wartoœci z tablicy
	for (int i = 0; i < binHeapSize; i++)
	{
		if (file.good())
			file >> value;
		addElements(value);
	}
	currentSize = binHeapSize;
	return true;
}

//generowanie kopca z losowych liczb
void BinaryHeap::generateRandomBinaryHeap(int size)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(1,1000+ 4 * size); // distribute results between
												  // 1 and 1000000 inclusive
	for (int i = 0; i < size; i++)
	{
		addElements(dist(gen));
	}
}


//zapis kopca do pliku
void BinaryHeap::saveDataToFile(string population)
{
	string fileName = "GeneratedHeap_" + population + ".txt";

	fstream file;
	file.open(fileName, ios::out | ios::app);

	if (file.good() == true)
	{
		file << currentSize << endl;
	}

	for (int i = 0; i < currentSize; i++)
	{
		if (file.good())
			file << *(binaryHeapObj + i)<<endl;
	}

	file.close();

}

//getter elementu ukrytego pod indexem
int BinaryHeap::getElement(int index)
{
	return binaryHeapObj[index];
}