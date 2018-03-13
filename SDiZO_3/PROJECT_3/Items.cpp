#include "stdafx.h"
#include "Items.h"
using namespace std;

Items::Items()
{

}


Items::Items(int N, int knapsackSize)
{
	generateItems(N, knapsackSize);
}


Items::~Items()
{
	delete items;
}


vector<Items::Item>* Items::generateItems(int N, int knapsackSize) 
{
	items = new vector<Item>();
	this->N = N;
	int weight, value;
	for (int i = 0; i < N; i++)
	{
		weight = 1 + knapsackSize / N + rand() % (knapsackSize - knapsackSize / (2*N));
		value = 1 + rand() % (2 * N);
		items->push_back(Item{ weight, value });
	}
	
	//show();
	return items;

}

void Items::show()
{	
	cout << endl << " # PRZEDMIOTY # "<< endl;

	for (int i = 0; i < N; i++)
	{
		cout<<"["<<i<<"]  Waga: "<<(*items)[i].size<<" Wartosc: "<< (*items)[i].value <<endl;
	}
}


int Items::getN()
{
	return N;
}

vector<Items::Item>* Items::getItems()
{
	return items;
}

//przypisanie wartoœci po odczycie z pliku
void Items::loadItemsFromFile(vector<Items::Item>* itemsFromFile ,int numberOfItems)
{
	items = itemsFromFile;
	N = numberOfItems;
}