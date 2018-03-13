#pragma once
#include <limits>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>

#define INF INT_MAX

class Cities
{
public:
	~Cities();
	bool generateCities(int numberOfCities);
	void showCities();
	bool loadCitiesFromFile(std::string name);
	int ** getCities();
	int getNumberOfCities();
private:
	int **adjacencyMatrix;
	int numberOfCities;
};

