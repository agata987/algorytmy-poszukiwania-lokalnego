#pragma once
#include "Algorithm.h"
#include <iostream>

class SimulatedAnnealing :
	public Algorithm
{
private:
	vector<int> shuffledVec(vector<int> vector);
	float calculateProbability(int newCost, int oldCost, float temperature);
	// parametr chlodzenie
	float coolingCoefficient;
	string schemat;
	float k;
public:
	SimulatedAnnealing(Graph* graph) :Algorithm(graph) {
		algorytmName = "Simulated Annealing";
		coolingCoefficient = 0.89;
		schemat = "geometryczny";
		k = 0.2;
	}
	~SimulatedAnnealing() = default;

	float calculateTemperature();

	void DisplayProperties() override;
	void run() override;

	void setSchemat(string schemat);
	void setCooling(float cooling);
	void setLineK(float parametr);
};

