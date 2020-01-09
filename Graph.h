#pragma once
#include <string>
#include <vector>

using namespace std;

class Graph
{
private:
	int** matrix;
	int numberOfCities;
	string name = "brak";
	vector<int> path;
	void addEdge(int city1, int city2, int distance);
public:
	bool graf_ = false;
	bool sciezka_ = false;

	Graph(int numberOfCities)
	{
		this->numberOfCities = numberOfCities;
		matrix = new int* [numberOfCities];

		for (int i = 0; i < numberOfCities; i++)
			matrix[i] = new int[numberOfCities];
	};
	~Graph() = default;

	void readFromFile();
	
	void reGenerate(int newSize);
	void generateRandom();
	void randomPath();
	int funkcjaCelu();

	// get
	int getWeight(int city1, int city2);
	int getnumberOfCities();
	vector<int> getPath();

	// print
	void printPath();
	void display();
};

