#include "SimulatedAnnealing.h"
#include <chrono>
#include <cmath>

void SimulatedAnnealing::run()
{
	clock_t start, end;
	setNajlepszaTrasa(false);

	start = clock();
	// obliczamy poczatkowa temperature
	// poczatkowa temperatura to 
	// wartosc bezwgledna (maxDistance - minDistance * liczba miast);
	float temperature = calculateTemperature();
	bestResult = funkcjaCelu(najlepszaTrasa);

	do {
		for (int i = 0; i < graph->getnumberOfCities(); i++)
		{
			// zamieniamy ze soba losowo 2 miasta w sciezce, czyli bierzemy jakies losowe sasiedztwo
			vector<int> shuffled = shuffledVec(najlepszaTrasa);

			// obliczamy funkcje celu dla sasiedztwa
			int currentCost = funkcjaCelu(shuffled);

			// jezeli jest lepsze rowiazanie to podmieniamy, jezeli nie to decydujemy czy je chcemy
			if (currentCost < bestResult)
			{
				najlepszaTrasa = shuffled;
				bestResult = currentCost;

			}	// static_cast<float> wymusza konwersje na float, rand_max to wartosc maksymalna jaka moze byc przyjeta przez rand()
			else if ((static_cast<float>(rand()) / RAND_MAX) < calculateProbability(currentCost, bestResult,  temperature))
			{
				// jezeli wylosowana wartosc jest mniejsza od wyliczonego prawdopodobienstwa to bierzemy rozw
				// prawdopodobienstwo zalezy m.in. od temperatury
				najlepszaTrasa = shuffled;
				bestResult = currentCost;
			}
		}

		if(schemat == "geometryczny")
		static_cast<float>(temperature = temperature * coolingCoefficient);  // schemat geometryczny
		else
		{
			static_cast<float>(temperature = temperature / (coolingCoefficient + k));  // schemat logarytmiczny
			k += 0.2;
		}
		end = clock();

	} while (getTime(end, start) <= maxTime);
}

float SimulatedAnnealing::calculateTemperature()
{

	// min i max odleglosc pomiedzy dwoma miastami w grafie
	int minDistance = INT_MAX;
	int maxDistance = 0;

	for (int i = 0; i < graph->getnumberOfCities(); i++)
	{
		for (int j = 0; j < graph->getnumberOfCities(); j++)
		{
			if (i != j)
			{
				if (graph->getWeight(i, j) < minDistance)
					minDistance = graph->getWeight(i, j);

				if (graph->getWeight(i, j) > maxDistance)
					maxDistance = graph->getWeight(i, j);
			}
		}
	}

	return abs(maxDistance - minDistance * graph->getnumberOfCities());
}

vector<int> SimulatedAnnealing::shuffledVec(vector<int> v)
{
	vector<int> temp = v;
	int x, y;

	temp.pop_back(); // do zamiany moze sie wylosowac wierzcholek poczatkowy, dlatego zabieramy powrot do niego

	do {
		x = rand() % graph->getnumberOfCities();
		y = rand() % graph->getnumberOfCities();
	} while (x == y);

	swap(temp.at(x), temp.at(y));

	temp.push_back(temp[0]);  // przywracamy powrot do miasta poczatkowego

	return temp;
}

float SimulatedAnnealing::calculateProbability(int newCost, int oldCost, float temperature)
{
	float result;
	result = (exp(-(static_cast<float>(abs(newCost - oldCost) / temperature))));

	return result;
}

void SimulatedAnnealing::DisplayProperties()
{
	cout << "Czas dzialania algorytmu: " << endl;
	cout << maxTime << endl;

	cout << "Parametr do schematu liniowego: " << endl;
	cout << k << endl;

	cout << "Wspolczynnik chlodzenia: " << endl;
	cout << static_cast<float>(coolingCoefficient) << endl;

	cout << fixed;
	cout << "Temperatura poczatkowa: " << endl;
	cout << calculateTemperature() << endl;
}

void SimulatedAnnealing::setCooling(float cooling)
{
	coolingCoefficient = cooling;
}

void SimulatedAnnealing::setLineK(float parametr)
{
	k = parametr;
}

void SimulatedAnnealing::setSchemat(string schemat)
{
	this->schemat = schemat;
}