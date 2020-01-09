#pragma once
#include <iostream>
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#include "Graph.h"

using namespace std;

class Menu
{
private:
	Graph* g;
	TabuSearch *t;
	SimulatedAnnealing *s;

	int block, aspiracja, seconds;
	float chlodzenie, wspolczynnik;
public:
	Menu();
	~Menu() = default;

	void print();
	void Tabu();
	void Annealing();
};

