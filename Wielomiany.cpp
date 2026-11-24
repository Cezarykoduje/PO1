#include "Wielomiany.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

Wielomian::~Wielomian() {
	delete[] wsp;
}

Wielomian::Wielomian(const Wielomian& wzor) {
	wsp = nullptr;
	stopien = 0;
	*this = wzor;
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

Wielomian::Wielomian(double wyrazWolny) {
	stopien = 0;
	wsp = new double[1];
	wsp[0] = wyrazWolny;
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

void Wielomian::ZaktualizujStopien() {
	while (stopien > 0 && wsp[stopien] == 0) {
		stopien--;
	}
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
		char* r=nullptr;
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

			char* r=nullptr;
			liczbaC = std::strtol(napis, &r, 10);

			if (r == napis)
				return napis;

			napis = r;
		}
		else liczbaC = 1;
	}

	if (liczbaC < 0 || liczbaC > stopien)
		return napis;

	wsp[liczbaC] += znak * liczbaR;
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
	ZaktualizujStopien();
}

void Wielomian::Pokaz(ostream& os) const {
	bool pierwszy = true;

	for (int i = (int)stopien; i >= 0; i--) {
		double wspolczynnik = wsp[i];

		if (wspolczynnik == 0)
			continue;

		if (!pierwszy)
			os << (wspolczynnik < 0 ? "-" : "+");
		else if (wspolczynnik < 0)
			os << "-";

		double wartosc = wspolczynnik < 0 ? -wspolczynnik : wspolczynnik;

		if (i == 0 || wartosc != 1)
			os << wartosc;

		if (i > 0) {
			os << "x";

			if (i > 1) {
				os << "^" << i;
			}

		}
		pierwszy = false;
	}

	if (pierwszy)
		os << "0";
}

Wielomian& Wielomian::operator=(const Wielomian& wzor) {
	if (this == &wzor) return *this;

	delete[] wsp;

	stopien = wzor.stopien;
	if (wzor.wsp == nullptr) {
		wsp = nullptr;
	}
	else {
		wsp = new double[stopien + 1];
		for (int i = 0; i <= stopien; i++) {
			wsp[i] = wzor.wsp[i];
		}
	}
	return *this;
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
	ZaktualizujStopien();
	return *this;
}

Wielomian& Wielomian::operator-=(const Wielomian& wi2) {
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
		wsp[i] -= wi2.wsp[i];
	ZaktualizujStopien();
	return *this;
}

Wielomian& Wielomian::operator*=(const Wielomian& wi2) {
	if ((stopien == 0 && wsp[0] == 0) || (wi2.stopien == 0 && wi2.wsp[0]==0)) {
		delete[] wsp;
		stopien = 0;
		wsp = new double[1];
		wsp[0] = 0;
		return *this;
	}
	int nowyStopien = stopien + wi2.stopien;
	double* nowaT = new double[nowyStopien + 1];

	for (int i = 0; i <= nowyStopien; i++)
		nowaT[i] = 0;

	for (int i = 0; i <= stopien; i++) {
		for (int j = 0; j <= wi2.stopien; j++) {
			nowaT[i + j] += wsp[i] * wi2.wsp[j];
		}
	}

	delete[] wsp;
	wsp = nowaT;
	stopien = nowyStopien;

	return *this;
}

Wielomian Wielomian::PodzielZReszta(const Wielomian& wi2, Wielomian& reszta) const {
	if (wi2.stopien == 0 && wi2.PobierzWspolczynnik(0) == 0) {
		cout << "Blad: Dzielenie przez 0!" << endl;
		reszta = Wielomian(0.0);
		return reszta;
	}
	if (stopien < wi2.stopien) {
		reszta = *this;
		return Wielomian(0.0);
	}

	int stopienWyniku = stopien - wi2.stopien;
	double* nowyWsp = new double[stopienWyniku + 1];
	for (int i = 0; i <= stopienWyniku; i++)
		nowyWsp[i] = 0;

	reszta = *this;
	while (reszta.stopien >= wi2.stopien) {
		int aktualnyStopien = reszta.stopien - wi2.stopien;
		double mnoznik = reszta.wsp[reszta.stopien] / wi2.wsp[wi2.stopien];

		nowyWsp[aktualnyStopien] = mnoznik;

		for (int i = 0; i <= wi2.stopien; i++)
			reszta.wsp[aktualnyStopien + i] -= mnoznik * wi2.wsp[i];

		reszta.ZaktualizujStopien();

		if (reszta.stopien == 0 && reszta.wsp[0] == 0)
			break;
	}

	Wielomian iloraz(nowyWsp, stopienWyniku + 1);
	delete[] nowyWsp;
	iloraz.ZaktualizujStopien();
	return iloraz;
}

Wielomian& Wielomian::operator/=(const Wielomian& wi2) {
	Wielomian reszta;
	*this = PodzielZReszta(wi2, reszta);
	return *this;
}

Wielomian& Wielomian::operator%=(const Wielomian& wi2) {
	Wielomian reszta;
	PodzielZReszta(wi2, reszta);
	*this = reszta;
	return *this;
}

Wielomian operator+(Wielomian lewy, const Wielomian& prawy) {
	return lewy += prawy;
}

Wielomian operator-(Wielomian lewy, const Wielomian& prawy) {
	return lewy -= prawy;
}

Wielomian operator*(Wielomian lewy, const Wielomian& prawy) {
	return lewy *= prawy;
}

Wielomian operator/(Wielomian lewy, const Wielomian& prawy) {
	return lewy /= prawy;
}

Wielomian operator%(Wielomian lewy, const Wielomian& prawy) {
	return lewy %= prawy;
}

double Wielomian::operator()(double x) const {
	double wartosc = wsp[stopien];
	for (int i = stopien-1; i>=0 ;i--) {
		wartosc *= x;
		wartosc += wsp[i];
	}
	return wartosc;
}

double Wielomian::operator[](int s) const {
	if (s >= 0 && s <= stopien) {
		return wsp[s];
	}
	else
		return 0.0;
}

ostream& operator<<(ostream& os, const Wielomian& w) {
	w.Pokaz(os);
	return os;
}

istream& operator>>(istream& is, Wielomian& w) {
	string bufor;
	getline(is >> ws, bufor);
	w = Wielomian(bufor.c_str());
	return is;
}

Wielomian Wielomian::Pochodna() const {
	if (stopien == 0) return Wielomian(0.0);

	double* nowaT = new double[stopien];
	for (int i = 1; i <= stopien; i++) {
		nowaT[i - 1] = wsp[i] * i;
	}
	Wielomian wynik(nowaT, stopien);
	delete[] nowaT;
	return wynik;
}