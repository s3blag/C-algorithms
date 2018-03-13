#pragma once
#include <string>
using namespace std;
class BinaryHeap
{
public:
	BinaryHeap();
	~BinaryHeap();
	void addElements(int value);
	void showBinaryHeap(string text1, string text2, int nodeNumber);
	int getSize();
	bool search(int value);
	void deleteElement();
	bool loadDataFromFile(string name);
	bool loadAndBuildDataFromFile(string name);
	void generateRandomBinaryHeap(int size);
	void saveDataToFile(string population);

	int getElement(int index);

};

