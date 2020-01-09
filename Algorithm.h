#pragma once

#include "Graph.h"
#include <vector>

using namespace std;

class Algorithm
{
protected:
	Graph* graph;
	string algorytmName;
	int maxTime;

	vector<int> najlepszaTrasa;
	int bestResult;
	int funkcjaCelu(vector<int> path);
	void setNajlepszaTrasa(bool losowe);  // algorytm zachlanny
	double getTime(double a, double b);
public:
	Algorithm(Graph* graph) : graph(graph) {
		maxTime = 30;   // sekundy
	};
	~Algorithm() = default;

	void set_maxTime(int seconds);

	virtual void run() = 0;
	virtual void DisplayProperties() = 0;

	void getTime();
	void printPath();
	void test();
	int getBestResult();
};

