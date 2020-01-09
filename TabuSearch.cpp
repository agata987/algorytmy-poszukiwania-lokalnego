#include "TabuSearch.h"
#include <chrono>
#include <cmath>

void TabuSearch::run()
{
	clock_t start, end;

	// algorytm zachlanny wybiera sciezke
	setNajlepszaTrasa(false);

	// okresla czy znaleziono sasiada lepszego o pewna ustalona wartosc (aspiration value)
	bool aspirationPlus = false;  

	// dzieki aspiracji nie musimy przegladac calego sasiedztwa <- algorytm dziala szybciej
	// ale musimy sprawdzic 10 sasiadow
	int aspirationCounter = 0;
	int maxAspirationCount = 10; 

	// inicjaliacja tablicy tabu
	int** tabu = new int* [graph->getnumberOfCities()];
	for (int i = 0; i < graph->getnumberOfCities(); i++)
	{
		tabu[i] = new int[graph->getnumberOfCities()];
		for (int j = 0; j < graph->getnumberOfCities(); j++)
			tabu[i][j] = 0;
	}

	// na poczatku jako najlepsza trase dajemy ta wyliczona algorytmem zachlannym
	najlepszaLokalna = najlepszaTrasa;

	// zeby znalezc najlepsza lokalna tymczasowe trasy do obliczania funkcji celu przechowujemy w tempRoute
	vector<int> tempRoute;

	int bestSwapFrom, bestSwapTo, bestSwapValue;

	start = clock();
	do
	{
		// szukamy najlepszego sasiada
		bestSwapValue = INT_MAX;

		// nie znaleziono sasiedztwa, ktore spelnia warunek aspiracji
		// (po jego zamianie poprawa wartosci funkcji celu o aspirationValue)
		aspirationPlus = false;

		// node startowy to 0, dlatego petla idzie od 1, nie dochodzimy do ostatniej wartosci w sciezce (powrotu)
		for (int i = 1; i < graph->getnumberOfCities(); i++)
		{
			for (int j = i + 1; j < graph->getnumberOfCities(); j++)
			{
				tempRoute = najlepszaLokalna;
				swap(tempRoute[i], tempRoute[j]);
				int diff = funkcjaCelu(tempRoute) - funkcjaCelu(najlepszaLokalna);

				// jezeli znalazl nowa najlepsza wartosc i nie ma jej na liscie tabu || spelnienie kryterium aspiracji
				if (((diff < bestSwapValue) && (tabu[i][j] == 0)) || (diff < aspirationValue))
				{
					bestSwapValue = diff;
					bestSwapFrom = i;
					bestSwapTo = j;

					if (diff < aspirationValue)
					{
						aspirationPlus = true;  // znalezlismy sasiedztwo spelniajace wartosc aspiracji
						aspirationCounter = 0;
					}
				}
				aspirationCounter++;

				// jezeli przejrzelismy odpowiednia liczbe sasiadow i znalezlismy sasiedztwo
				if (aspirationCounter == maxAspirationCount && aspirationPlus)
				{
					goto aspHappend;
				}
			}
		}

	aspHappend:

		// decrement tabu list
		for (int i = 0; i < graph->getnumberOfCities(); i++)
		{
			for (int j = 0; j < graph->getnumberOfCities(); j++)
			{
				if (tabu[i][j] > 0)
					tabu[i][j]--;
			}
		}
		
		// set best neighbour as current road and add swap to tabu
		swap(najlepszaLokalna[bestSwapFrom], najlepszaLokalna[bestSwapTo]);


			tabu[bestSwapFrom][bestSwapTo] = tabuBlock;
			tabu[bestSwapTo][bestSwapFrom] = tabuBlock;

			// set new best value if one's found
			if (funkcjaCelu(najlepszaLokalna) < funkcjaCelu(najlepszaTrasa)) {
				najlepszaTrasa = najlepszaLokalna;
				bestResult = funkcjaCelu(najlepszaTrasa);
			}

		end = clock();
	} while (getTime(end, start) <= maxTime);



	// CleanUp tabuList
	for (int i = 0; i < graph->getnumberOfCities(); i++) {
		delete[] tabu[i];
	}
	delete[] tabu;
	najlepszaLokalna.clear();
	tempRoute.clear();
}

void TabuSearch::DisplayProperties()
{
	cout << "Czas dzialania algorytmu: " << endl;
	cout << maxTime << endl;

	cout << "Wartosc blokowania w tablicy Tabu: " << endl;
	cout << tabuBlock << endl;

	cout << "Wartosc wspolczynnika aspiracji: " << endl;
	cout << aspirationValue << endl;
}

void TabuSearch::set_aspirationValue(int value)
{
	aspirationValue = value;
}

void TabuSearch::set_tabuBlock(int block)
{
	tabuBlock = block;
}