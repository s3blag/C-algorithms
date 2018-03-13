#include "stdafx.h"
#include "GreedyKnapSack.h"

using namespace std;

void GreedyKnapSack::knapSackProblem(Items *items, KnapSack *knapSack, bool sortByValue)
{
	vector<Items::Item> *vectorOfItems = items->getItems();
	int N = items->getN(), size = knapSack->getCapacity(), tmpSize = 0;
	bool *bestOption = new bool[N];
	string info = "Sortowanie po v";
	
	//wybor metody sortuj¹cej w zale¿noœci od parametru sortByValue
	function<bool(indexedItem &a, indexedItem &b)> comp;
	if(sortByValue)
		comp = [](indexedItem &a, indexedItem &b) { return a.second.value < b.second.value; };
	else
	{
		comp = [](indexedItem &a, indexedItem &b) { return a.second.getFactor() < b.second.getFactor(); };
		info = "Sortowanie po v/s";
	}
	//kolejka priorytetowa zindeksowanych przedmiotów
	priority_queue<indexedItem, vector<indexedItem>, decltype(comp)> sortedItems(comp);
	//przenoszenie przedmiotow do kolejki
	for (int i = 0; i < N; i++)
		sortedItems.push(make_pair(i, (*vectorOfItems)[i]));

	for (int i = 0; i < N; i++)
		bestOption[i] = false;
	
	//Pobieranie przedmiotu o najwiêkszej wartoœci/wspó³czynniku
	for (int i = 0; i < N; i++)
	{
		indexedItem item = sortedItems.top();
		sortedItems.pop();
		if (tmpSize + item.second.size <= size)
		{
			tmpSize += item.second.size;
			bestOption[item.first] = true;
		}

	}
	//showResults(bestOption, N, vectorOfItems, info);

	delete[] bestOption;
}

//wyswietlanie wynikow
void GreedyKnapSack::showResults(bool *bestOption, int N, vector<Items::Item> *vectorOfItems, string info)
{
	int value = 0, size = 0;
	cout << endl << "       ALG. ZACHLANNY - " + info << endl;
	cout << endl << "ROZWIAZANIE : " << endl;
	for (int i = 0; i < N; i++)
	{
		if (bestOption[i] == true)
		{
			cout << "[ " << i << " ] ";

			cout << "Waga: " << (*vectorOfItems)[i].size;
			size += (*vectorOfItems)[i].size;

			cout << " Wartosc: " << (*vectorOfItems)[i].value << endl;
			value += (*vectorOfItems)[i].value;
		}
	}
	cout << "Laczna waga: " << size << " Laczna wartosc: " << value << endl << endl;
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
}

