#include "stdafx.h"
#include "BruteKnapSack.h"
using namespace std;

void BruteKnapSack::knapSackProblem(Items *items, KnapSack *knapSack)
{	
	vector<Items::Item> *vectorOfItems = items->getItems();
	int N = items->getN(), capacity = knapSack->getCapacity(),		
		tmpWeight, tmpValue, cursor, bestValue = 0;
	bool *visited = new bool[N], *bestOption = new bool[N];
	long long numberOfCombinations = static_cast<long long>(pow(2, N)) - 1;

	//oznaczenie wszystkich przedmiotow jako nierozpatrzonych
	for (int i = 0; i < N; i++)
		visited[i] = false;

	//rozpatrywanie wszystkich pozdbiorów zbioru przedmiotów
	for (long long i = 0; i < numberOfCombinations; i++)
	{
		//ustawienie kursora na najmlodsza pozycje tablicy(indeks o najwiekszej wartosci)
		cursor = N-1;
		tmpWeight = 0;
		tmpValue = 0;

		//binarne odliczenie od 1 do 2^N - 1; 1 na pozycji oznacza wybranie danego przedmiotu
		while (visited[cursor] != 0 && cursor > 0)
		{
			visited[cursor] = false;
			cursor--;
		}
		
		visited[cursor] = true;
		//obliczanie ³¹cznych wartoœci danego podzbioru przedmiotów
		for (int j = 0; j < N; j++)
		{
			if (visited[j] == true)
			{
				tmpWeight += (*vectorOfItems)[j].size;
				tmpValue += (*vectorOfItems)[j].value;
			}	
		}
		
		//sprawdzanie czy dany podzbiór jest rozwi¹zaniem do tej pory najlepszym
		if ((tmpValue > bestValue) && (tmpWeight <= capacity))
		{
			bestValue = tmpValue;
			for (int j = 0; j < N; j++)
				bestOption[j] = visited[j];
		}
	}
	//showResults(bestOption, N, items);

	delete[] visited;
	delete[] bestOption;
}


//Wyœwietlanie wyników
void BruteKnapSack::showResults(bool *bestOption, int N, Items *items)
{
	vector<Items::Item> *vectorOfItems = items->getItems();
	int value = 0, size = 0;
	cout << endl << " - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << endl << "       PRZEGLAD ZUPELNY " << endl;
	cout << endl << " Rozwiazanie: " << endl;
	for (int i = 0; i < N; i++)
	{
		if (bestOption[i] == 1)
		{
			cout << "[ " << i << " ] ";

			cout << "Waga: " << (*vectorOfItems)[i].size;
			size += (*vectorOfItems)[i].size;
	
			cout << " Wartosc: " << (*vectorOfItems)[i].value << endl;
			value += (*vectorOfItems)[i].value;
		}
	}
	cout << "Laczna waga: " << size << " Laczna wartosc: " << value << endl << endl;
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}