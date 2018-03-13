// ------------------------------------------------ METODY TESTUJ¥CE ------------------------------------------------ 

void greedySalesmanTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Cities *cities;
	for (int numberOfCities = 25000; numberOfCities <= 30000; numberOfCities += 5000)
	{
			cout<< " numberOfCities = " << numberOfCities <<"-----------------"<< endl;
			string fileName = "greedySailsman.txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 100; j++)
			{
				cout << "  j = " << j << endl;
				cities = new Cities();
				cities->generateCities(numberOfCities);
				cout << endl << "START! " << endl;
				startCounter();
				GreedySalesman::salesmanProblem(cities);
				tmp = getCounter();
				cout << endl << "STOP! " <<tmp<<" ms"<< endl;
				elapsed += tmp;

				delete cities;
			}

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed / 100  << endl;
			}
			elapsed = 0;
			file.close();
		
	}
}

void bruteSalesmanTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Cities *cities;
	for (int numberOfCities = 10; numberOfCities <= 15; numberOfCities++)
	{
		cout << " numberOfCities = " << numberOfCities << "-----------------" << endl;
		string fileName = "bruteSailsman.txt";
		file.open(fileName, ios::out | ios::app);
		for (int j = 0; j < 100; j++)
		{
			cout << "  j = " << j << endl;
			cities = new Cities();
			cities->generateCities(numberOfCities);
			cout << endl << "START! " << endl;
			startCounter();
			BruteSalesman::salesmanProblem(cities);
			tmp = getCounter();
			cout << endl << "STOP! " << tmp << " ms" << endl;
			elapsed += tmp;

			delete cities;
		}

		if (file.good() == true)
		{
			
			file << setprecision(0) << elapsed / 100 << endl;
		}
		elapsed = 0;
		file.close();

	}
}


void bruteKnapSackTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Items * items;
	KnapSack *knapSack = new KnapSack(1000);
	for (int numberOfItems = 20; numberOfItems <= 28; numberOfItems +=2)
	{
		cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
		string fileName = "bruteKnapsack.txt";
		file.open(fileName, ios::out | ios::app);
		for (int j = 0; j < 100; j++)
		{
			cout << "  j = " << j << endl;
			items = new Items();
			items->generateItems(numberOfItems, knapSack->getCapacity());
			cout << endl << "START! " << endl;
			startCounter();
			BruteKnapSack::knapSackProblem(items,knapSack);
			tmp = getCounter();
			cout << endl << "STOP! " << tmp << " ms" << endl;
			elapsed += tmp;

			delete items;
			
		}

		if (file.good() == true)
		{

			file << setprecision(0) << elapsed / 100 << endl;
		}
		elapsed = 0;
		file.close();

	}
	delete knapSack;
}

void greedyKnapSackTest()
{
	double tmp = 0, elapsed = 0;
	fstream file;
	Items * items;
	
	
	for (int sackSize = 100000; sackSize <300001;sackSize+=100000 )
	{
		KnapSack *knapSack = new KnapSack(sackSize);
		for (int numberOfItems = 200000; numberOfItems <= 1000001; numberOfItems += 200000)
		{

			cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
			string fileName = "greedyKnapsackByValue"+to_string(sackSize)+".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 100; j++)
			{
				cout << "  j = " << j << endl;
				items = new Items();
				items->generateItems(numberOfItems, knapSack->getCapacity());
				cout << endl << "START! " << endl;
				startCounter();
				GreedyKnapSack::knapSackProblem(items, knapSack, true);
				tmp = getCounter();
				cout << endl << "STOP! " << tmp << " ms" << endl;
				elapsed += tmp;

				delete items;

			}

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed / 100 << endl;
			}
			elapsed = 0;
			file.close();

		}

		tmp = 0;
		elapsed = 0;
		for (int numberOfItems = 200000; numberOfItems <= 1000001; numberOfItems += 200000)
		{
			cout << " numberOfItems = " << numberOfItems << "-----------------" << endl;
			string fileName = "greedyKnapsackByFactor" + to_string(sackSize) + ".txt";
			file.open(fileName, ios::out | ios::app);
			for (int j = 0; j < 100; j++)
			{
				cout << "  j = " << j << endl;
				items = new Items();
				items->generateItems(numberOfItems, knapSack->getCapacity());
				cout << endl << "START! " << endl;
				startCounter();
				GreedyKnapSack::knapSackProblem(items, knapSack, false);
				tmp = getCounter();
				cout << endl << "STOP! " << tmp << " ms" << endl;
				elapsed += tmp;

				delete items;

			}

			if (file.good() == true)
			{

				file << setprecision(0) << elapsed / 100 << endl;
			}
			elapsed = 0;
			file.close();

		}
		delete knapSack;
	}
}

void GreedySalesman::salesmanProblem(Cities *cities)
{
	int **adjacencyMatrix = cities->getCities(),numberOfCities = cities->getNumberOfCities(),
		currentCity = 0, nextCity, currentDistance = 0, bestDistance = INF;
	vector<bool> visited (numberOfCities, false);
	list<int> bestPath;
	list<int> currentPath;

	int startingCity = 0;

	//for (int startingCity = 0; startingCity < numberOfCities; startingCity++)
	//{
	visited[startingCity] = true;
	currentCity = startingCity;
	//koniec pêtli jeœli przejdziemy przez wszystkie miasta
	for (int i = 0; i < numberOfCities; i++)
	{
		//jeœli dotarliœmy do ostatniego miasta, to dodajemy drogê z miasta koñcowego do pocz¹tkowego
		if (i == numberOfCities-1)
		{	
			currentPath.push_back(currentCity);
			nextCity = startingCity;
			currentPath.push_back(startingCity);
			currentDistance += adjacencyMatrix[currentCity][nextCity];
		}
		else
		{	
			currentPath.push_back(currentCity);
			//znajdujemy drogê najkrótsz¹ z obecnego miasta do miasta jeszcze nierozpatrzonego
			nextCity = findShortestRoute(currentCity, adjacencyMatrix, numberOfCities, visited);
			//oznaczamy znalezione miasto jako rozpatrzone
			visited[nextCity] = true;
			//zwiêkszamy przebyty dystans o d³ugoœæ drogi do znalezionego miasta
			currentDistance += adjacencyMatrix[currentCity][nextCity];
			currentCity = nextCity;
		}
	}
		
	/*	if (currentDistance < bestDistance)
		{
			bestDistance = currentDistance;
			bestPath.swap(currentPath);
		}
	
		for (int i = 0; i < numberOfCities; i++)
		{
			visited[i] = false;
		}
		currentPath.clear();
		currentDistance = 0;
		
	}
	showResults(bestPath, bestDistance);*/
	
	
	//showResults(currentPath, currentDistance);
}