#include "Graph.h"
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void Graph::addEdge(int city1, int city2, int distance)
{
	matrix[city1][city2] = distance;
}

int Graph::getWeight(int city1, int city2)
{
	return matrix[city1][city2];
}

void Graph::display()
{
	std::cout << " " << "\t";
	for (int i = 0; i < numberOfCities; i++)
	{
		std::cout << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < numberOfCities; i++)
	{
		std::cout << i << "\t";
		for (int j = 0; j < numberOfCities; j++)
			std::cout << matrix[i][j] << "\t";

		std::cout << std::endl;
	}
}

int Graph::getnumberOfCities()
{
	return numberOfCities;
}

void Graph::generateRandom()
{
	srand(time(NULL));

	for (int i = 0; i < numberOfCities; i++)
		for (int j = 0; j < numberOfCities; j++)
		{
			if (i != j)
				addEdge(i, j, rand() % 101 + 1);
			else
				addEdge(i, j, -1);
		}
	graf_ = true;
}

void Graph::reGenerate(int newSize)
{
	for (int i = 0; i < numberOfCities; i++)
		delete[] matrix[i];

	delete[] matrix;

	this->numberOfCities = newSize;
	matrix = new int* [numberOfCities];

	for (int i = 0; i < numberOfCities; i++)
		matrix[i] = new int[numberOfCities];
}

void Graph::readFromFile()
{
	string sciezka;
	cout << "Podaj sciezke do pliku: ";
	cin >> sciezka;

	fstream plik;
	plik.open(sciezka, ios::in);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku." << endl;
	}
	else
	{

		int newSize;

		plik >> name;
		plik >> newSize;

		reGenerate(newSize);

		// tworzenie grafu
		int  value;
		for (int i = 0; i < numberOfCities; i++)
		{
			for (int j = 0; j < numberOfCities; j++)
			{
				plik >> value;
				addEdge(i, j, value);
			}
		}

		graf_ = true;
		sciezka_ = false;
	}
	plik.close();
}

int Graph::funkcjaCelu()
{
	int sum = 0;
	for (vector<int>::iterator it = path.begin(); it != prev(path.end()); it++)
	{
		sum += getWeight(*it, *(next(it, 1)));
	}
	return sum;
}

void Graph::randomPath()
{
	srand(time(NULL));

	if (path.empty())
		for (int i = 0; i < numberOfCities; i++)
			path.push_back(i);

	random_shuffle(path.begin(), path.end());
	path.push_back(path.front());

	sciezka_ = true;
}

void Graph::printPath()
{
	cout << endl;
	cout << "sciezka: ";
	for (vector<int>::iterator it = path.begin(); it != path.end(); it++)
		cout << *it << " ";
	cout << endl;
}

vector<int> Graph::getPath()
{
	return path;
}
