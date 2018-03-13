#pragma once
#include "Items.h"
#include "KnapSack.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
class GreedyKnapSack
{
public:
	typedef std::pair<int, Items::Item> indexedItem;
	void static knapSackProblem(Items * items, KnapSack * knapSack, bool isByValue);
private:
	void static showResults(bool * bestOption, int N, std::vector<Items::Item>* vectorOfSortedItems,std::string info);
};

