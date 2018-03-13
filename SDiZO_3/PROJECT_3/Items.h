#pragma once
#include <vector>
#include <iostream>

class Items
{

public:
	Items(int N, int knapsackSize);
	Items();
	~Items();

	struct Item
	{
		int size;
		int value;
		//metoda zwracaj¹cy wspó³czynnik v/s danego przedmiotu
		float getFactor() const
		{
			return (float)value / (float)size;
		}
	};
	
	std::vector<Item>* generateItems(int N, int knapsackSize);
	void loadItemsFromFile(std::vector<Items::Item>* itemsFromFile, int numberOfItems);
	
	std::vector<Item>* getItems();
	void show();
	int getN();
private:
	std::vector<Item> *items;
	int N;
};

