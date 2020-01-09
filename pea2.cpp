#include <iostream>
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#include "Graph.h"
#include "Menu.h"
#include <fstream>

using namespace std;

int main()
{
	//fstream plik;
	//plik.open("geometryczny_ten.txt",ios::out);
	Menu* m = new Menu();
	m->print();
	
	//// TESTY
	//Graph* g = new Graph(5);
	//g->readFromFile();
	//g->randomPath();

	//TabuSearch t(g);
	//SimulatedAnnealing s(g);

	//t.set_maxTime(90);

	//for (int i = -8; i > -22; i = i - 2)
	//{
	//	t.set_aspirationValue(i);
	//	cout << "wartosc aspiracji: " << i << endl;
	//	t.run();
	//	t.printPath();
	//}
}

