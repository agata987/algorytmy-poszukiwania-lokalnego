#pragma once
#include "Algorithm.h"
#include <iostream>

class TabuSearch :
	public Algorithm
{
private:
	vector<int> najlepszaLokalna;
	// parametry
	int tabuBlock, aspirationValue;
public:
	TabuSearch(Graph* graph) :Algorithm(graph) {
		algorytmName = "Tabu Search";

		tabuBlock = 12;
		aspirationValue = -12;
	}
	~TabuSearch() = default;

	void DisplayProperties() override;
	void run() override;

	void set_tabuBlock(int block);
	void set_aspirationValue(int value);
};

