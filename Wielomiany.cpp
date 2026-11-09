#include <iostream>

using namespace std;

class Wielomian
{
	private:
		double* wsp;
		int stopien;

		const char* AnalizujJednomian(const char* napis);
		int AnalizujJednomiany(const char* napis);
	public:
		Wielomian() { wsp = nullptr; stopien = 0; };
		Wielomian(const char*);
		Wielomian(const Wielomian& wzor);
		Wielomian(const double* tablica, int liczbaElementow);
		~Wielomian();
		Wielomian& operator+=(const Wielomian&);
		Wielomian operator+(const Wielomian& wi2) const;
		void Pokaz() const;

		int PobierzStopien() const { return stopien; }
		double PobierzWspolczynnik(int i) const {
			if (i >= 0 && i <= stopien) return wsp[i];
			return 0.0;
		}
};

Wielomian::~Wielomian() {
	delete[] wsp;
}

Wielomian::Wielomian(const Wielomian& wzor) {
	stopien = wzor.stopien;
	wsp = new double[stopien + 1];

	for (int i = 0; i <= stopien; i++) {
		wsp[i] = wzor.wsp[i];
	}
}

Wielomian::Wielomian(const double* tablica, int liczbaElementow) {
	if (liczbaElementow <= 0) {
		stopien = 0;
		wsp = new double[1];
		wsp[0] = 0;
	}
	else {
		stopien = liczbaElementow - 1;
		wsp = new double[liczbaElementow];

		for (int i = 0; i < liczbaElementow; i++) {
			wsp[i] = tablica[i];
		}
	}
}

Wielomian Wielomian::operator+(const Wielomian& wi2) const {
	Wielomian wynik(*this);
	wynik += wi2;
	return wynik;
}

void pomidOdstepy(const char*& napis)
{
	while (*napis == ' ' || *napis == '\t')
		napis++;
}

int OkreslStopien(const char* napis) {
	int n = 0;
	const char* temp = napis;
	while (*temp != '\0') {
		if (*temp == 'x') {
			temp++;
			pomidOdstepy(temp);
			int s = 1;
			if (*temp == '^') {
				temp++;
				pomidOdstepy(temp);
				char* r = nullptr;
				s = std::strtol(temp, &r, 10);
				temp = r;
			}

			if (s > n)
				n = s;

		} else
		temp++;
	}
	return n;
}



const char* Wielomian::AnalizujJednomian(const char* napis)
{
	double liczbaR = 1;
	int liczbaC = 0;
	int znak = 1;

	pomidOdstepy(napis);

	if (*napis == '-')
	{
		napis++;
		znak = -1;
	}
	else if (*napis == '+')
		napis++;

	pomidOdstepy(napis);

	if (*napis == 'x')
		liczbaR = 1;
	else {
		char* r;
		liczbaR = std::strtod(napis, &r);

		if (r == napis)
			return napis;


		napis = r;
	}

	pomidOdstepy(napis);

	if (*napis == 'x') {
		napis++;
		pomidOdstepy(napis);

		if (*napis == '^') {
			napis++;
			pomidOdstepy(napis);

			char* r;
			liczbaC = std::strtol(napis, &r, 10);

			if (r == napis)
				return napis;

			napis = r;
		}
		else liczbaC = 1;
	}

	if (liczbaC < 0 || liczbaC > stopien)
		return napis;

	wsp[liczbaC] += znak * liczbaR; // wsp declared in class Wielomian
	pomidOdstepy(napis);
	return napis;
}

int Wielomian::AnalizujJednomiany(const char* napis) {
	pomidOdstepy(napis);

	while (*napis != '\0') {
		const char* nowy = AnalizujJednomian(napis);

		if (nowy == napis)
			return 0;

		napis = nowy;
		pomidOdstepy(napis);

		if (*napis == '\0')
			return 1;

		if (*napis != '+' && *napis != '-')
			return 0;
	}
	return 1;
}

Wielomian::Wielomian(const char* napis) {
	stopien = OkreslStopien(napis);
	wsp = new double[stopien + 1];

	for (int i = 0; i <= stopien; i++)
		wsp[i] = 0;

	if (!AnalizujJednomiany(napis)) {
		delete[] wsp;
		wsp = new double[1];
		wsp[0] = 0;
		stopien = 0;
	}
}

void Wielomian::Pokaz() const
{
	bool pierwszy = true;

	for (int i = (int)stopien; i >= 0; i--) {
		double wspolczynnik = wsp[i];

		if (wspolczynnik == 0)
			continue;

		if (!pierwszy)
			cout << (wspolczynnik < 0 ? "-" : "+");
		else if (wspolczynnik < 0)
			cout << "-";

		double wartosc = wspolczynnik < 0 ? -wspolczynnik : wspolczynnik;

		if (i == 0 || wartosc != 1)
			cout << wartosc;

		if (i > 0) {
			cout << "x";

			if (i > 1) {
				cout << "^" << i;
			}
			
		}
		pierwszy = false;
	}

	if (pierwszy)
		cout << "0";

	cout << endl;
}

Wielomian& Wielomian::operator+=(const Wielomian& wi2) {
	if (stopien < wi2.stopien) {
		double* nowaT = new double[wi2.stopien + 1];
		for (int i = 0; i <= stopien; i++)
			nowaT[i] = wsp[i];
		for (int i = stopien + 1; i <= wi2.stopien; i++)
			nowaT[i] = 0;
		delete[] wsp;
		wsp = nowaT;
		stopien = wi2.stopien;
	}
	for (int i = 0; i <= wi2.stopien; i++)
		wsp[i] += wi2.wsp[i];

	return *this;
}

int main()
{
	const char* przyklady[] = {
		"x^2-2x+5",
		"x^3 - x^2 + 2x - 7.5",
		"2.5x^3 + x - 4",
		"-x^4 + 3",
		"7",
		"0",
		"x^2 + 3x^2 - x",
		"x^5 + 2x^2 - 1",
		"x^2 + 1",
		"  x ^ 2 + 3 ",
		"x^2+",
		"x^2++3",
		"x^2+-3",
		"2 3x+1",
		"x^",
		"x^2 abc",
		"x^-2",
		"" };

	int ile = sizeof(przyklady) / sizeof(przyklady[0]);

	for (int i = 0; i < ile; i++) {
		cout << przyklady[i] << " = ";

		Wielomian w(przyklady[i]);

		if (w.PobierzStopien() == 0 && w.PobierzWspolczynnik(0) == 0 && przyklady[i][0] != '0') {
			cout << "Niepoprawny Wielomian" << endl;
		}
		else {
			w.Pokaz();
		}
	}

	// --- TEST KONSTRUKTORA Z TABLICY ---
	//double suroweDane[] = { 5.0, -2.0, 3.0 };
	//int ilosc = sizeof(suroweDane) / sizeof(suroweDane[0]);

	//Wielomian zTablicy(suroweDane, ilosc);
	//zTablicy.Pokaz();

	// --- TEST OPERATORA + ---
	//Wielomian w1("x^2 + 2x");
	//Wielomian w2("3x^2 + 5");

	//cout << "Test operatora + :" << endl;
	//Wielomian suma = w1 + w2;
	//suma.Pokaz();

	return 0;

}
