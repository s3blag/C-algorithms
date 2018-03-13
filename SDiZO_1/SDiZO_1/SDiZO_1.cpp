// SDiZO_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SDiZO_1.h"
#include "Array.h"
#include "MyList.h"
#include "BinaryHeap.h"
#include <string>
#include <ctime>
#include <windows.h>
#include <random>
#include <conio.h>
#include <fstream>
#include <iomanip> 


using namespace std;


double PCFreq = 0.0;
__int64 CounterStart = 0;

Array *_array;
MyList *_list;
BinaryHeap *_binHeap;
void startCounter();
double getCounter();
void arrayMenu();
void listMenu();
void binaryHeapMenu();
void showMenu(string info);
int generateRandomValue(int range);
int generateRandomIndex(int range);
void testTable_addAtTheEnd(int howManyTimes);
void testTable_addAtTheBeginning(int howManyTimes);
void testTable_addInTheRandomPlace(int howManyTimes);
void testTable_deleteFromTheEnd(int howManyTimes);
void testTable_deleteFromTheBeginning(int howManyTimes);
void testTable_deleteFromRandomPlace(int howManyTimes);
void testTable_search(int howManyTimes);
void testList_addAtTheEnd(int howManyTimes);
void testList_addAtTheBeginning(int howManyTimes);
void testList_addInTheRandomPlace(int howManyTimes);
void testList_deleteFromTheBeginning(int howManyTimes);
void testList_deleteFromTheEnd(int howManyTimes);
void testList_deleteFromRandomPlace(int howManyTimes);
void testlist_search(int howManyTimes);
void testHeap_add(int howManyTimes);
void testHeap_delete(int howManyTimes);
void testHeap_search(int howManyTimes);
int generateRandomValue(int rangeMin, int rangeMax);
int generateRandomIndex(int rangeMin, int rangeMax);


int main()
{
//	if (binHeap->loadDataFromFile("file.txt"))
//		binHeap->showBinaryHeap("  ", " ", 1);

	//Menu powitalne
	char option;
	do {
		cout << endl;
		cout << "############	MENU	 ############" << endl;
		cout << "1.Tablica" << endl;
		cout << "2.Lista" << endl;
		cout << "3.Kopiec" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;
		switch (option) {
		case '1':
			_array = new Array();
			arrayMenu();
			break;

		case '2':
			_list = new MyList();
			listMenu();
			break;

		case '3':
			_binHeap = new BinaryHeap();
			binaryHeapMenu();
			break;
		}

	} while (option != '0');

    return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------		
//---------------------------------------------------------   TABLICA  ---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void arrayMenu()
{	
	
	char opt;
	string fileName;
	int index, value;

	do {
		showMenu("--- TABLICA ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytytwanie  tablicy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			if (_array->loadDataFromFile(fileName))
				cout << endl << _array->showArray() << endl;
			else
				cout << "\nNIE znaleziono pliku!\n";
			break;

		case '2': //usuwanie elemenu z tablicy
			cout << " podaj index:";
			cin >> index;
			if (index >= _array->getSize())
				cout << "\nNie ma obiektu o takim indeksie";
			else
			{
				if (index == _array->getSize() - 1)
					_array->deleteElementsE();
				else

					if (index == 0)
						_array->deleteElementsB();
					else
						_array->deleteElementsM(index);
			}
			cout << endl << _array->showArray() << endl;
			break;

		case '3': //dodawanie elemetu do tablicy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartoœæ:";
			cin >> value;
			if (index > _array->getSize())
				cout << "\nNie ma obiektu o takim indeksie";
			else
			{
				if (index == _array->getSize())
					_array->addElementsE(value);
				else
					if (index == 0)
						_array->addElementsB(value);
					else
						_array->addElementsM(value,index);
				cout << endl << _array->showArray() << endl;
			}
			
			break;

		case '4': //znajdowanie elementu w tablicy
			cout << " podaj wartosc:";
			cin >> value;
			if (_array->searchElements(value))
				cout << "\npodana wartosc jest w tablicy\n";
			else
				cout << "\npodanej wartosci NIE ma w tablicy\n";
			break;

		case '5':  //generowanie  tablicy z losowymi danymi
			cout << "Podaj ilosc elementow tablicy:";
			cin >> value;
			if (value <= 0)
				cout << "\n bledna wartosc!\n";
			else
			{
				delete _array;
				_array = new Array();
				_array->generateRandomArray(value);
				cout << endl << _array->showArray() << endl;
			}
			break;

		case '6':  //wyœwietlanie tablicy
			cout<<endl<<_array->showArray()<<endl;
			break;

		case '7': //funkcja do eksperymentów
			int howManyTimes;
			cout << "\nIle powtorzen?\n";
			cin >> howManyTimes;
			/*
			delete _array;
			_array = new Array();
			testTable_addAtTheEnd(howManyTimes);
			
			delete _array;
			_array = new Array();
			testTable_addAtTheBeginning(howManyTimes);
			
			delete _array;
			_array = new Array();
			testTable_addInTheRandomPlace(howManyTimes);
			
			
			delete _array;
			_array = new Array();
			testTable_deleteFromTheEnd(howManyTimes);
			
			delete _array;
			_array = new Array();
			testTable_deleteFromTheBeginning(howManyTimes);
			
			delete _array;
			_array = new Array();
			testTable_deleteFromRandomPlace(howManyTimes);
				*/
			
			delete _array;
			_array = new Array();
			testTable_search(howManyTimes);
		

			break;
		}

	} while (opt != '0');
	delete _array;
}


//test dodawania na koniec tablicy
void testTable_addAtTheEnd(int howManyTimes)
{
	int populationSize;
	int newElement;
	double tmp=0;
	double  elapsed=0;
	string fileName = "table_ADDAtTheEND_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (int j = 0; j < howManyTimes; j++)
		{
			_array->generateRandomArray(populationSize);
			newElement = generateRandomValue(populationSize);

			startCounter();
			_array->addElementsE(newElement);
			tmp= getCounter();
			elapsed += tmp;
			delete _array;
			_array = new Array();
		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}
		
		elapsed = 0;
	
	}
	file.close();
}

//test dodawania na pocz¹tek tablicy
void testTable_addAtTheBeginning(int howManyTimes)
{
	int populationSize;
	int newElement;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "table_ADDAtTheBeginning_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (int j = 0; j < howManyTimes; j++)
		{
			_array->generateRandomArray(populationSize);
			newElement = generateRandomValue(populationSize);

			startCounter();
			_array->addElementsB(newElement);
			tmp = getCounter();
			elapsed += tmp;
			delete _array;
			_array = new Array();

		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;


	}
	file.close();
}

//test dodawania w losowe miejsce tablicy
void testTable_addInTheRandomPlace(int howManyTimes)
{
	int populationSize, newElement, index;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "table_ADDintheRANDOMplace.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{
		for (int j = 0; j < howManyTimes; j++)
		{
			_array->generateRandomArray(populationSize);
			newElement = generateRandomValue(populationSize);
			index = generateRandomIndex(populationSize);
		
			if (index == _array->getSize())
			{	
				startCounter();
				_array->addElementsE(newElement);
				tmp = getCounter();
			}	
			else
			{
				if (index == 0)
				{
					startCounter();
					_array->addElementsB(newElement);
					tmp = getCounter();
				}
				else
				{
					startCounter();
					_array->addElementsM(newElement, index);
					tmp = getCounter();
				}
			}
			elapsed += tmp;
			delete _array;
			_array = new Array();
		}
		
		if (file.good() == true)
			file << setprecision(0) << elapsed / howManyTimes << endl;
		elapsed = 0;
	
	}
	file.close();
}

//----------------------------------------------------------------------------------------------------------------------------------

//test usuwania z koñca tablicy
void testTable_deleteFromTheEnd(int howManyTimes)
{
	int populationSize;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "table_DELETEfromTheEND_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (int j = 0; j < howManyTimes; j++)
		{
			_array->generateRandomArray(populationSize);

			startCounter();
			_array->deleteElementsE();
			tmp = getCounter();
			elapsed += tmp;
			delete _array;
			_array = new Array();
		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;
		
	}
	file.close();
}

//test usuwania z pocz¹tku tablicy
void testTable_deleteFromTheBeginning(int howManyTimes)
{
	int populationSize;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "table_DELETEfromtheBeginning_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (int j = 0; j < howManyTimes; j++)
		{
			_array->generateRandomArray(populationSize);

			startCounter();
			_array->deleteElementsB();
			tmp = getCounter();
			elapsed += tmp;

		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;
		delete _array;
		_array = new Array();

	}
	file.close();
}

//test usuwania z losowego miejsca w tablicy
void testTable_deleteFromRandomPlace(int howManyTimes)
{
	int populationSize, newElement, index;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "table_DELETEfromtheRANDOMplace.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{
		for (int j = 0; j < howManyTimes; j++)
		{
			_array->generateRandomArray(populationSize);
			newElement = generateRandomValue(populationSize);
			index = generateRandomIndex(populationSize - 1);

			if (index == _array->getSize()-1)
			{
				startCounter();
				_array->deleteElementsE();
				tmp = getCounter();
			}
			else
			{
				if (index == 0)
				{
					startCounter();
					_array->deleteElementsB();
					tmp = getCounter();
				}
				else
				{
					startCounter();
					_array->deleteElementsM(index);
					tmp = getCounter();
				}
			}
			elapsed += tmp;
			delete _array;
			_array = new Array();
		}

		if (file.good() == true)
			file << setprecision(0) << elapsed / howManyTimes << endl;
		elapsed = 0;

	}
	file.close();
}

//-----------------------------------------------------------------------------------------------------------------------------------


//test wyszukiwania w tablicy
void testTable_search(int howManyTimes)
{
	int populationSize, newElement,j,index,i=1,value;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "table_search.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	

	for (populationSize = 20000; populationSize < 201001; populationSize += 20000,++i)
	{	//tworze nowa tablice dla nowej populacji
		
		string fileName = "GeneratedHeap_" + to_string(populationSize) + ".txt";
		if(_array->loadDataFromFile(fileName)==false)
			cout << "ehh";

			for (j = 0; j < i*howManyTimes; j++)
			{
				if (generateRandomIndex(0, 10) >= 5)
					index = generateRandomIndex(0, populationSize- 1);
				else
					index = populationSize-1;

				value = _array->getElement(index);
				startCounter();//czas start
				_array->searchElements(value);
				tmp = getCounter();//koniec mierzenia

				elapsed += tmp;    //dodajê czas do sumy czasów wszystkich przejœæ
				
			}


		if (file.good() == true)
		{	//wrzucam do pliku srednia czasow
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}
		
		//zeruje czas
		elapsed = 0;

		delete _array;
		_array = new Array();
	}

	//zamykam plik na koncu
	file.close();
}



//------------------------------------------------------------------------------------------------------------------------------------		
//---------------------------------------------------------   LISTA    ---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------



void listMenu()
{
	char opt;
	string fileName;
	int index, value;

	do {
		showMenu("--- LISTA ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytytwanie  listy z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			if (_list->loadDataFromFile(fileName))
				cout << endl << _list->showMyList() << endl;
			else
				cout << "\nNIE znaleziono pliku!\n";
			break;

		case '2': //usuwanie elemenu z listy o podanym indeksie
			cout << " podaj index:";
			cin >> index;
			if (index >= _list->getSize() || index<0)
				cout << "\nNie ma obiektu o takim indeksie";
			else
			{
				if (index == 0)
					_list->deleteElementsB();
				else
					if (index == _list->getSize() - 1)
						_list->deleteElementsE();
					else
						_list->deleteElementsM(index);
			}
			cout << endl << _list->showMyList() << endl;
			break;

		case '3': //dodawanie elementu do listy
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartoœæ:";
			cin >> value;
			if (index > _list->getSize() || index<0)
				cout << "\nNie ma obiektu o takim indeksie";
			else
			{
				if (index == 0)
					_list->addElementsB(value);
				else
					if (index > _list->getSize() - 1)
						_list->addElementsE(value);
					else
						_list->addElementsM(value, index);
				cout << endl << _list->showMyList() << endl;
			}

			break;

		case '4': //znajdowanie elementu w liscie
			cout << " podaj wartosc:";
			cin >> value;
			if (_list->search(value))
				cout << "\npodana wartosc jest w liscie\n";
			else
				cout << "\npodanej wartosci NIE ma w liscie\n";
			break;

		case '5':  //generowanie  listy
			cout << "Podaj ilosc elementow listy:";
			cin >> value;
			if (value <= 0)
				cout << "\n bledna wartosc!\n";
			else
			{
				delete _list;
				_list = new MyList;
				_list->generateRandomList(value);
				cout << endl << _list->showMyList() << endl;
			}
			break;

		case '6':  //wyœwietlanie listy
			cout << endl << _list->showMyList() << endl;
			break;

		case '7': //funkcja do eksperymentów
			int howManyTimes;
			cout << "\nIle powtorzen?\n";
			cin >> howManyTimes;
			
			delete _list;
			_list = new MyList();
			
			//testList_addAtTheEnd(howManyTimes);


			//testList_addAtTheBeginning(howManyTimes);
			
			//testLi0st_addInTheRandomPlace(howManyTimes);

			//testList_deleteFromTheBeginning(howManyTimes);

			//testList_deleteFromTheEnd(howManyTimes);

			//testList_deleteFromRandomPlace(howManyTimes);

			testlist_search(howManyTimes);
			break;
		}

	} while (opt != '0');
	delete _list;
}



//test dodawania na koniec listy
void testList_addAtTheEnd(int howManyTimes)
{
	int populationSize , j;
	int newElement;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "list_ADDAtTheEND_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (j = 0; j < howManyTimes; j++)
		{
			_list->generateRandomList(populationSize);
			newElement = generateRandomValue(populationSize);

			startCounter();
			_list->addElementsE(newElement);
			tmp = getCounter();
			elapsed += tmp;
			delete _list;
			_list = new MyList();
		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;
		
	}
	file.close();
}

// test dodawania na poczatek listy
void testList_addAtTheBeginning(int howManyTimes)
{
	int populationSize,j;
	int newElement;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "list_ADDAtTheBeginning_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (j = 0; j < howManyTimes; j++)
		{
			_list->generateRandomList(populationSize);
			newElement = generateRandomValue(populationSize);

			startCounter();
			_list->addElementsB(newElement);
			tmp = getCounter();
			elapsed += tmp;
			delete _list;
			_list = new MyList();

		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;

	}
	file.close();
}
//test dodawania do listy w losowe miejsce
void testList_addInTheRandomPlace(int howManyTimes)
{
	int populationSize, newElement, index;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "list_ADDintheRANDOMplace.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{
		for (int j = 0; j < howManyTimes; j++)
		{
			_list->generateRandomList(populationSize);
			newElement = generateRandomValue(populationSize);
			index = generateRandomIndex(populationSize);

			if (index == _list->getSize())
			{
				startCounter();
				_list->addElementsE(newElement);
				tmp = getCounter();
			}
			else
			{
				if (index == 0)
				{
					startCounter();
					_list->addElementsB(newElement);
					tmp = getCounter();
				}
				else
				{
					startCounter();
					_list->addElementsM(newElement, index);
					tmp = getCounter();
				}
			}
			elapsed += tmp;
			delete _list;
			_list = new MyList();
		}

		if (file.good() == true)
			file << setprecision(0) << elapsed / howManyTimes << endl;
		elapsed = 0;
		
	}
	file.close();
}


//-------------------------------------------------------------------------------------------------------------------------------------


//test usuwania z pocz¹tku listy
void testList_deleteFromTheBeginning(int howManyTimes)
{
	int populationSize,j;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "list_DELETEfromtheBeginning_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (j = 0; j < howManyTimes; j++)
		{
			_list->generateRandomList(populationSize);

			startCounter();
			_list->deleteElementsB();
			tmp = getCounter();
			elapsed += tmp;
			delete _list;
			_list = new MyList();

		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}
		
		elapsed = 0;
		

	}
	file.close();
}

//test usuwania z koñca listy

void testList_deleteFromTheEnd(int howManyTimes)
{
	int populationSize, j;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "list_DELETEfromTheEND_.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{

		for (j = 0; j < howManyTimes; j++)
		{
			_list->generateRandomList(populationSize);

			startCounter();
			_list->deleteElementsE();
			tmp = getCounter();
			elapsed += tmp;
			delete _list;
			_list = new MyList();
		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;
	
	}
	file.close();
}

//test usuwania losowego elementu listy
void testList_deleteFromRandomPlace(int howManyTimes)
{
	int populationSize, newElement, index,j;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "list_DELETEfromtheRANDOMplace.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 10000)
	{
		for (j = 0; j < howManyTimes; j++)
		{
			_list->generateRandomList(populationSize);
			newElement = generateRandomValue(populationSize);
			index = generateRandomIndex(populationSize - 1);
			if (index == _list->getSize() - 1)
			{
				startCounter();
				_list->deleteElementsE();
				tmp = getCounter();
			}
			else
			{
				if (index == 0)
				{
					startCounter();
					_list->deleteElementsB();
					tmp = getCounter();
				}
				else
				{
					startCounter();
					_list->deleteElementsM(index);
					tmp = getCounter();
				}
			}
			elapsed += tmp;
			delete _list;
			_list = new MyList();
		}

		if (file.good() == true)
			file << setprecision(0) << elapsed / howManyTimes << endl;
		elapsed = 0;
		
	}
	file.close();
}


//test wyszukiwania w liscie
void testlist_search(int howManyTimes)
{
	//cout << howManyTimes;
	int populationSize, newElement, j,index, value,i=1;
	double tmp = 0;
	double result = 0;
	double  elapsed = 0;
	string fileName = "list_search.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);

	for (populationSize = 20000; populationSize < 210001; populationSize += 20000,++i)
	{	//tworze nowa tablice dla nowej populacji
		//_list->generateRandomList(populationSize);
		
		string fileName = "GeneratedHeap_" + to_string(populationSize) + ".txt";
		if (_list->loadDataFromFile(fileName) == false)
			cout << "Blad!";
		_list->loadDataFromFile(fileName);
		for (j = 0; j <  i*howManyTimes; j++)
		{
			if(generateRandomIndex(0,10)>=5)
			index = generateRandomIndex(0,populationSize/2-1);
			else
				index = generateRandomIndex(populationSize / 2, populationSize -1 );
			
			value = _list->getValue(index);
			startCounter();//czas start
			_list->search(value);
			tmp = getCounter();//koniec mierzenia

			elapsed += tmp;    //dodajê czas do sumy czasów wszystkich przejœæ
		}
		
		
		
		if (file.good() == true)
		{	//wrzucam do pliku srednia czasow
			file << setprecision(0) << elapsed /howManyTimes << endl;
		}

		//zeruje czas
		elapsed = 0;
		delete _list;
		_list = new MyList();
	}

	//zamykam plik na koncu
	file.close();
}


//------------------------------------------------------------------------------------------------------------------------------------		
//---------------------------------------------------------   KOPIEC   ---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
void binaryHeapMenu()
{


	char opt;
	string fileName;
	int index, value;

	do {
		showMenu("--- KOPIEC BINARNY ---");
		opt = _getche();
		cout << endl;
		switch (opt) {
		case '1': //wczytytwanie kopca z pliku
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			if (_binHeap->loadAndBuildDataFromFile(fileName))
			{
				cout << endl;
				_binHeap->showBinaryHeap("  ", " ", 1);
				cout << endl;
			}
			else
				cout << "\nNIE znaleziono pliku!\n";
			break;

		case '2': //usuwanie elemenu z kopca
			if (_binHeap->getSize() > 0)
			{
				_binHeap->deleteElement();
				_binHeap->showBinaryHeap("", "", 1);
			}
			else
				cout << "\nKopiec jest pusty\n";
			break;

		case '3': //dodawanie elemetu do kopca
			cout << " podaj wartoœæ:";
			cin >> value;
			_binHeap->addElements(value);
			_binHeap->showBinaryHeap("  ", " ", 1);
			break;

		case '4': //znajdowanie elementu w kopcu
			cout << " podaj wartosc:";
			cin >> value;
			if (_binHeap->search(value))
				cout << "\npodana wartosc jest w kopcu\n";
			else
				cout << "\npodanej wartosci NIE ma w kopcu\n";
			break;

		case '5':  //generowanie  kopca z losowymi danymi
			cout << "Podaj ilosc elementow kopca:";
			cin >> value;
			if (value <= 0)
				cout << "\n bledna wartosc!\n";
			else
			{
				delete _binHeap;
				_binHeap = new BinaryHeap();
				_binHeap->generateRandomBinaryHeap(value);
				_binHeap->showBinaryHeap("  ", " ", 1);
			}
			break;

		case '6':  //wyœwietlanie kopca
			_binHeap->showBinaryHeap("  ", " ", 1);
			break;

		case '7': //funkcja do eksperymentów
			int howManyTimes;
			cout << "\nIle powtorzen?\n";
			cin >> howManyTimes;
			
			delete _binHeap;
			_binHeap = new BinaryHeap;
			//testHeap_delete(howManyTimes);
			testHeap_search(howManyTimes);
			
			
			break;
		}

	} while (opt != '0');
	delete _binHeap;
}


//--------------------------------------------------------------------------------------------------------------------------------


//test dodawanie elementu do kopca
void testHeap_add(int howManyTimes)
{
	int populationSize,newElement, j;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "HEAP_ADD.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 40000)
	{

		for (j = 0; j < howManyTimes; j++)
		{
			_binHeap->generateRandomBinaryHeap(populationSize);
			newElement = generateRandomValue(populationSize);
			startCounter();
			_binHeap ->addElements(newElement);
			tmp = getCounter();
			elapsed += tmp;
			delete _binHeap;
			_binHeap = new BinaryHeap();
		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;
		

	}
	file.close();
}


//--------------------------------------------------------------------------------------------------------------------

//test usuwanie korzenia z kopca
void testHeap_delete(int howManyTimes)
{
	int populationSize, newElement, j;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "HEAP_DELETE.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	for (populationSize = 1000; populationSize < 201001; populationSize += 40000)
	{

		for (j = 0; j < howManyTimes; j++)
		{
			_binHeap->generateRandomBinaryHeap(populationSize);
			startCounter();
			_binHeap->deleteElement();
			tmp = getCounter();
			elapsed += tmp;
			delete _binHeap;
			_binHeap = new BinaryHeap();
		}
		if (file.good() == true)
		{
			file << setprecision(0) << elapsed / howManyTimes << endl;
		}

		elapsed = 0;


	}
	file.close();
}

//test przeszukiwanie kopca
void testHeap_search(int howManyTimes)
{
	int populationSize, newElement, j, index, i = 1, value;
	double tmp = 0;
	double  elapsed = 0;
	string fileName = "heap_search.txt";
	fstream file;
	file.open(fileName, ios::out | ios::app);
	string fileToLoadDataFrom;

	for (populationSize = 20000; populationSize < 201001; populationSize += 20000, ++i)
	{		
		string fileName = "GeneratedHeap_" + to_string(populationSize) + ".txt";
		if (_binHeap->loadDataFromFile(fileName) == false)
			cout << "ehh";
		//_binHeap->generateRandomBinaryHeap(populationSize);
		//_binHeap->saveDataToFile(to_string(populationSize));




		for (j = 0; j < i*howManyTimes; j++)
		{
			if (generateRandomIndex(0, 10) >= 5)
				index = generateRandomIndex(0, populationSize / 2 - 1);
			else
				index = generateRandomIndex(populationSize / 2, populationSize - 1);

			value = _binHeap->getElement(index);
			startCounter();//czas start
			_binHeap->search(value);
			tmp = getCounter();//koniec mierzenia

			elapsed += tmp;    //dodajê czas do sumy czasów wszystkich przejœæ
		}


		if (file.good() == true)
		{	//wrzucam do pliku srednia czasow
			file << setprecision(0) << elapsed /howManyTimes << endl;
		}

		//zeruje czas
		elapsed = 0;

		delete _binHeap;
		_binHeap = new BinaryHeap();
	}

	//zamykam plik na koncu
	file.close();
}


//------------------------------------------------------------------------------------------------------------------------------------		
//----------------------------------------------   METODY POMOCNICZE   ---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//menu wyboru opcji dla struktur
void showMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

// Ustawia odliczanie na zero
void startCounter()		
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

// Zwraca czas od ostatniego wywolania startCounter(); 
double getCounter()		
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}



//generator liczb losowych
int generateRandomValue(int range)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	
	uniform_int_distribution<> dist(1,1000+ 4*range); // distribute results between
	return dist(gen);							 // 1 and 2*range inclusive
}

//generator liczb losowych
int generateRandomValue(int rangeMin, int rangeMax)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()

	uniform_int_distribution<> dist(2*rangeMin, 2*rangeMax); // distribute results between
	return dist(gen);							 // 1 and 2*range inclusive
}



//przeci¹¿ony generator losowego indeksu
int generateRandomIndex(int range)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()

	uniform_int_distribution<> dist(0, range); // distribute results between
	return dist(gen);							 // 0 and range inclusive
}

//przeci¹¿ony generator losowego indeksu
int generateRandomIndex(int rangeMin,int rangeMax)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()

	uniform_int_distribution<> dist(rangeMin, rangeMax); // distribute results between
	return dist(gen);						
}