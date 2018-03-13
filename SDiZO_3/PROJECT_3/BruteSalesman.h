#pragma once
#include "Cities.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class BruteSalesman
{
public:
	void static salesmanProblem(Cities * cities);	
private:
	void static showResults(std::vector<int>& shortestPath, int distance);
};

