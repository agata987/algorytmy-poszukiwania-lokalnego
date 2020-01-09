#include "Algorithm.h"
#include <iostream>
#include <iomanip>

using namespace std;

int Algorithm::funkcjaCelu(vector<int> path)
{
	int sum = 0;
	for (vector<int>::iterator it = path.begin(); it != prev(path.end()); it++)
		sum += graph->getWeight(*it, *(next(it, 1)));

	return sum;
}

void Algorithm::setNajlepszaTrasa(bool losowe)
{
	if (losowe)
	{
		graph->randomPath();
		najlepszaTrasa = graph->getPath();
	}
	else {   // algorytm zachlanny
		najlepszaTrasa.clear();

		// 0 jako startowy wierzcholek
		najlepszaTrasa.push_back(0);

		bool* odwiedzone = new bool[graph->getnumberOfCities()];
		odwiedzone[0] = true;

		for (int i = 0; i < graph->getnumberOfCities(); i++)
			odwiedzone[i] = false;

		odwiedzone[0] = true;

		for (int i = 0; i < graph->getnumberOfCities() - 1; i++)
		{
			int min = INT_MAX;
			int nast = -1;

			for (int j = 0; j < graph->getnumberOfCities(); j++)
			{
				if (graph->getWeight(najlepszaTrasa[i], j) < min && !odwiedzone[j])
				{
					min = graph->getWeight(najlepszaTrasa[i], j);
					nast = j;
				}
			}

			odwiedzone[nast] = true;
			najlepszaTrasa.push_back(nast);
		}
		najlepszaTrasa.push_back(najlepszaTrasa[0]);
		bestResult = funkcjaCelu(najlepszaTrasa);
	}
}

void Algorithm::printPath()
{
	vector<int>::iterator it;
	for (it = najlepszaTrasa.begin(); it != najlepszaTrasa.end(); it++)
	{
		cout << *it << " ";
	}

	cout << "	koszt drogi: " << bestResult << endl;
}

double Algorithm::getTime(double a, double b)
{
	return (double(a - b) / CLOCKS_PER_SEC);
}

void Algorithm::set_maxTime(int seconds)
{
	maxTime = seconds;
}

void Algorithm::getTime()
{
	cout << "Czas wykonania algorytmu: " << maxTime << " sekund" << endl;
}

void Algorithm::test()
{
	// ???
}

int Algorithm::getBestResult()
{
	return bestResult;
}
