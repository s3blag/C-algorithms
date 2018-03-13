#pragma once
#include "Items.h"
#include "KnapSack.h"
#include <vector>
#include <iostream>
class BruteKnapSack
{
public:
	void static knapSackProblem(Items * items, KnapSack * knapSack);
private:
	void static showResults(bool * bestOption, int N, Items * items);
};

