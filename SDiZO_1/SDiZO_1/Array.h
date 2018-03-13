#pragma once
#include <string>
using namespace std;
class Array
{
public:
	Array();
	Array(int size);
	~Array();
	void addElementsE(int value);
	void addElementsM(int value, int position);
	void addElementsB(int value);
	string showArray();

	void deleteElements(int position);

	void deleteElementsM(int position);

	void deleteElementsB();

	void deleteElementsE();

	bool searchElements(int value);

	bool loadDataFromFile(string name);

	int getSize();

	void generateRandomArray(int size);

	int getElement(int index);

	void saveDataToFile(string name, string population);



};

