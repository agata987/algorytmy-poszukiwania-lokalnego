#include "Menu.h"

Menu::Menu()
{
	g = new Graph(5);

	block = 12;
	aspiracja = -12;
	seconds = 90;
	chlodzenie = 0.7;
	wspolczynnik = 0.2;
}

void Menu::print()
{
	char opcja;

	cout << "\n   -----MENU-----" << endl;
	cout << "1. Wczytaj graf" << endl;
	cout << "2. Wygeneruj losowo" << endl;
	cout << "3. Wyswietl graf" << endl;
	cout << "4. Ustaw czas" << endl;
	cout << "5. Tabu Search" << endl;
	cout << "6. Simulated Annealing" << endl;
	cout << "0. Wyjscie" << endl;
	cout << "m - Wyswietl Menu" << endl;

	do {
		cin.clear();
		cout << "\n>> ";
		cin >> opcja;
		cout << endl;

		switch (opcja)
		{
		case 'm':

			cout << "\n   -----MENU-----" << endl;
			cout << "1. Wczytaj graf" << endl;
			cout << "2. Wygeneruj losowo" << endl;
			cout << "3. Wyswietl graf" << endl;
			cout << "4. Ustaw czas" << endl;
			cout << "5. Tabu Search" << endl;
			cout << "6. Simulated Annealing" << endl;
			cout << "0. Wyjscie" << endl;
			cout << "m - Wyswietl Menu" << endl;
			break;

		case '1':
			// wczytaj graf
			g = new Graph(5);
			g->readFromFile();
			break;

		case '2':
			// wygeneruj losowe
			int rozmiar;
			cout << "Podaj rozmiar macierzy: ";
			cin.clear();
			cin >> rozmiar;
			g = new Graph(rozmiar);
			g->reGenerate(rozmiar);
			g->generateRandom();
			break;

		case '3':
			// wyswietl graf
			if (g->graf_ == true)
				g->display();
			else
				cout << "brak grafu" << endl;

			if (g->sciezka_ == true)
				g->printPath();
			else
				cout << "\nbrak sciezki" << endl;

			break;
		case '4':
			// ustaw czas
			cout << "Podaj sekundy: ";
			cin.clear();
			cin >> seconds;

			break;

		case '5':
			// Tabu Search

			Tabu();

			break;

		case '6':
			// Simulated Annealing
			Annealing();

			break;
		}

	} while (opcja != '0');

}

void Menu::Tabu()
{
	t = new TabuSearch(g);
	t->set_tabuBlock(block);
	t->set_maxTime(seconds);

	cout << "\n   -----Tabu Search-----" << endl;
	cout << "1. Uruchom" << endl;
	cout << "2. Ustaw blokowanie" << endl;
	cout << "3. Ustaw aspiracje" << endl;
	cout << "4. Wyswietl ustawienia" << endl;
	cout << "0. Powrot" << endl;
	cout << "m - Wyswietl Menu" << endl;

	char opcja;

	do {
		cin.clear();
		cout << "\n>> ";
		cin >> opcja;
		cout << endl;

		switch (opcja)
		{
		case 'm':

			cout << "\n   -----Tabu Search-----" << endl;
			cout << "1. Uruchom" << endl;
			cout << "2. Ustaw blokowanie" << endl;
			cout << "3. Ustaw aspiracje" << endl;
			cout << "4. Wyswietl ustawienia" << endl;
			cout << "0. Powrot" << endl;
			cout << "m - Wyswietl Menu" << endl;
			break;

		case '1':
			// uruchom
			if (g->graf_ == true)
			{
				t->getTime();
				t->run();
				t->printPath();
			}
			else
				cout << "Brak grafu" << endl;

			break;

		case '2':
			// ustaw blokowanie
			cin.clear();
			cout << "Podaj wartosc: ";
			cin >> block;
			t->set_tabuBlock(block);

			break;

		case '3':
			// ustaw aspiracje
			cin.clear();
			cout << "Podaj wartosc aspiracji (ujemna): ";
			cin >> aspiracja;

			break;
		case '4':
			// sywietl ustawienia
			t->DisplayProperties();

			break;

		case '0':
			// powrot

			cout << "\n   -----MENU-----" << endl;
			cout << "1. Wczytaj graf" << endl;
			cout << "2. Wygeneruj losowo" << endl;
			cout << "3. Wyswietl graf" << endl;
			cout << "4. Ustaw czas" << endl;
			cout << "5. Tabu Search" << endl;
			cout << "6. Simulated Annealing" << endl;
			cout << "0. Wyjscie" << endl;
			cout << "m - Wyswietl Menu" << endl;

			return;

			break;
		}

	} while (true);
}

void Menu::Annealing()
{
	s = new SimulatedAnnealing(g);
	s->setCooling(chlodzenie);
	s->setLineK(wspolczynnik);
	s->set_maxTime(seconds);

	cout << "\n   -----Simulated Annealing-----" << endl;
	cout << "1. Uruchom (geometryczny)" << endl;
	cout << "2. Uruchom (liniowy)" << endl;
	cout << "3. Ustaw chlodzenie" << endl;
	cout << "4. Ustaw wspolczynnik dla liniowego" << endl;
	cout << "5. Wyswietl ustawienia" << endl;
	cout << "0. Powrot" << endl;
	cout << "m - Wyswietl Menu" << endl;

	char opcja;

	do {
		cin.clear();
		cout << "\n>> ";
		cin >> opcja;
		cout << endl;

		switch (opcja)
		{
		case 'm':

			cout << "\n   -----Simulated Annealing-----" << endl;
			cout << "1. Uruchom (geometryczny)" << endl;
			cout << "2. Uruchom (liniowy)" << endl;
			cout << "3. Ustaw chlodzenie" << endl;
			cout << "4. Ustaw wspolczynnik dla liniowego" << endl;
			cout << "5. Wyswietl ustawienia" << endl;
			cout << "0. Powrot" << endl;
			cout << "m - Wyswietl Menu" << endl;
			break;

		case '1':
			// uruchom (geometryczny)
			if (g->graf_ == true)
			{
				s->setSchemat("geometryczny");
				cout << "Schemat zmieniony na geometryczny" << endl;

				s->getTime();
				s->run();
				s->printPath();
			}
			else
				cout << "Brak grafu" << endl;

			break;

		case '2':
			// uruchom (liniowy)
			if (g->graf_ == true)
			{
				s->setSchemat("liniowy");
				cout << "Schemat zmieniony na liniowy" << endl;
				s->getTime();
				s->run();
				s->printPath();
			}
			else
				cout << "Brak grafu" << endl;

			break;

		case '3':
			// ustaw chlodzenie
			cin.clear();
			cout << "Podaj wartosc: ";
			cin >> chlodzenie;

			s->setCooling(chlodzenie);

			break;
		case '4':
			// ustaw wpolczynnik dla liniowego
			cin.clear();
			cout << "Podaj wspolczynnik chlodzenia: ";
			cin >> wspolczynnik;

			s->setLineK(wspolczynnik);

			break;

		case '5':
			// wyswietl ustawienia
			s->DisplayProperties();

			break;

		case '0':
			// powrot

			cout << "\n   -----MENU-----" << endl;
			cout << "1. Wczytaj graf" << endl;
			cout << "2. Wygeneruj losowo" << endl;
			cout << "3. Wyswietl graf" << endl;
			cout << "4. Ustaw czas" << endl;
			cout << "5. Tabu Search" << endl;
			cout << "6. Simulated Annealing" << endl;
			cout << "0. Wyjscie" << endl;
			cout << "m - Wyswietl Menu" << endl;

			return;

			break;
		}

	} while (true);
}