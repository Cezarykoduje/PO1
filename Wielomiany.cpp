#include <iostream>

using namespace std;

class Wielomian
{
public:
	Wielomian() { wsp = nullptr; stopien = 0; };
	double* wsp;
	int stopien;
	Wielomian(const char*);
	Wielomian& operator+=(const Wielomian&);
	void Pokaz() const;
};

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

Wielomian alokujPamiec(int s)
{
	Wielomian w;
	w.stopien = s;
	w.wsp = new double[s + 1]; // (double *)malloc(s+1) * sizeof(double));

	for (int i = 0; i <= s; i++)
		w.wsp[i] = 0;

	return w;
}

const char* AnalizujJednomian(const char* napis, Wielomian* w)
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

	if (liczbaC < 0 || liczbaC > (int)w->stopien)
		return napis;

	w->wsp[liczbaC] += znak * liczbaR;
	pomidOdstepy(napis);
	return napis;
}

int AnalizujJednomiany(const char* napis, Wielomian* w) {
	pomidOdstepy(napis);

	while (*napis != '\0') {
		const char* nowy = AnalizujJednomian(napis, w);

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

int analizujWielomian(const char napis[], Wielomian* w) {
	int s = OkreslStopien(napis);
	*w = alokujPamiec(s);

	if (!AnalizujJednomiany(napis, w)) {
		delete[] w->wsp;
		return 0;
	}

	return 1;
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

		Wielomian w;

		if (analizujWielomian(przyklady[i], &w)) {
			w.Pokaz();
			delete[] w.wsp;
		}
		else {
			cout << "Niepoprawny Wielomian" << endl;
		}
	}


	return 0;

}
