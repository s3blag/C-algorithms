#pragma once
#include <string>
using namespace std;
class MyList
{
public:
	MyList();
	~MyList();
	void addElementsM(int value, int position);
	void addElementsB(int value);
	void addElementsE(int value);
	void deleteElementsB();
	void deleteElementsM(int position);
	void deleteElementsE();
	void addElements(int value, int position);
	string showMyList();

	bool search(int value);

	bool loadDataFromFile(string name);

	void generateRandomList(int size);

	int getSize();

	int getValue(int index);

	

};

