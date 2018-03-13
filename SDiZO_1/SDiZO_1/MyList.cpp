#include <string>
#include "stdafx.h"
#include "MyList.h"
#include <iostream>
#include "SDiZO_1.h"
#include <fstream>
#include <random>
using namespace std;
//klasa elementow listy
class ListElement
{
public:
	//wskazniki na poprzedni i nastepny element
	ListElement * previous, *next;
	//wartosc elementu
	int value;
	ListElement();
	
};

ListElement::ListElement()
{
	previous = NULL;
	next = NULL;
}

//wskazniki na glowe i ogon listy
ListElement * head;
ListElement * tail;
int amountOfElements;


MyList::MyList()
{
	head = tail = NULL;
	amountOfElements = 0;
}


MyList::~MyList()
{
	ListElement *currentElement;
	while (head)
	{
		currentElement = head->next;
		delete head;
		head = currentElement;
	}
	amountOfElements = 0;
}


//dodawanie elementu na poczatek listy
void MyList::addElementsB(int value)
{
	ListElement *newElement = new ListElement;
	
	if (head == NULL && amountOfElements == 0)
	{
		newElement->value = value;
		head = newElement;
		tail = newElement;
	}
	else
	{
		newElement->value = value;
		newElement->previous = NULL;
		newElement->next =head;
		head->previous = newElement;
		head = newElement;
	}
	amountOfElements++;
}

//dodawanie elementu do srodkowej czesci listy
void MyList::addElementsM(int value, int position)
{	
	if (position > 0 && position <= amountOfElements - 1)
	{
		ListElement *newElement = new ListElement;
		newElement->value = value;
		if (head == NULL && amountOfElements == 0)
		{
			head = newElement;
			tail = newElement;
		}
		else
		{
			ListElement *currentElement = head;
			for (int i = 0; i < position - 1; i++)
				currentElement = currentElement->next;
			newElement->next = currentElement->next;
			currentElement->next = newElement;
			newElement->previous = currentElement;
		}
		amountOfElements++;
	}
}

//dodawanie elementu na koniec listy
void MyList::addElementsE(int value)
{
	ListElement *newElem = new ListElement;
	
	if (tail != NULL && amountOfElements > 0)
	{
		newElem->value = value;
		newElem->previous = tail;
		newElem->next = NULL;
		tail->next = newElem;
		tail = newElem;
	}
	else
	{
		newElem->value = value;
		tail = newElem;
		head = newElem;
	}
	amountOfElements++;
}
//usuwanie elementu z poczatku listy
void MyList::deleteElementsB()
{
	if (head->next != NULL)
	{
		ListElement *newHead;
		newHead = head->next;
		newHead->previous = NULL;
		delete head;
		head = newHead;
	}
	else
	{
		delete head;
		head = NULL;
	}
	amountOfElements--;
}

//usuwanie elementu ze srodkowej czesci listy
void MyList::deleteElementsM(int position)
{
	if (amountOfElements > 0 && position > 0 && position < amountOfElements - 1)
	{
		ListElement *_previous, *_next, *_currentElement = head;
		for (int i = 0; i < position; i++)
			_currentElement = _currentElement->next;

		_previous = _currentElement->previous;
		_next = _currentElement->next;

		_previous->next = _next;
		_next->previous = _previous;

		delete _currentElement;
		amountOfElements--;
	}
}

//usuwanie elementu z konca listy
void MyList::deleteElementsE()
{
	ListElement *newTail;
	newTail= tail->previous;
	newTail->next = NULL;
	delete tail;
	tail = newTail;
	amountOfElements--;
}

//wyswietlanie listy
string MyList::showMyList()
{
	string description = "";
	ListElement *currentElement = head;
	while (currentElement != NULL && amountOfElements>0)
	{
		description += to_string(currentElement->value) + "	";
		currentElement = currentElement->next;
	}
	return description;
}

//przeszukiwanie listy
bool MyList::search(int value)
{
	ListElement *currentElement = tail;
	bool wasFound = false;
	while (currentElement != NULL)
	{
		if (currentElement->value == value)
		{
			wasFound = true;
			break;
		}
		currentElement = currentElement->previous;
	}
	return wasFound;
}

//import listy z pliku - kolejnosc odwrotna
bool MyList::loadDataFromFile(string name)
{	
	// Otwarcie pliku
	int value,amount;
	ifstream file;
	file.open(name);
	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;
	// Pobranie informacji o iloœci elementów
	
	file >> amount;

	amountOfElements = 0;
	for (int i = 0; i < amount; i++)
	{
		if (file.good()) 
		{
			file >> value;
			addElementsB(value);
		}
	}
	amountOfElements = amount;
	return true;
}

//generowanie listy z losowymi elementami
void MyList::generateRandomList(int size)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(1, 1000+2 * size); // distribute results between
												  // 1 and 1000000 inclusive
	for (int i = 0; i < size; i++)
	{
		addElementsB(dist(gen));
	}
	amountOfElements = size;
}


//getter rozmiaru struktury
int MyList::getSize()
{
	return amountOfElements;
}

//zwracanie elemeentu listy pod podanym indexem - metoda pomocnicza w eksperymencie
int MyList::getValue(int index)
{
	int value = 0 , i=0;
	ListElement *currentElement = head;
	while (currentElement != NULL)
	{	
		if (i == index)
		{
			return currentElement->value;
		}
		currentElement = currentElement->next;
		i++;
	}
	return value;
}