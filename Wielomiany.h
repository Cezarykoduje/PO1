#pragma once
#include <iostream>

class Wielomian
{
private:
	double* wsp;
	int stopien;
	void ZaktualizujStopien();

	const char* AnalizujJednomian(const char* napis);
	int AnalizujJednomiany(const char* napis);

	Wielomian PodzielZReszta(const Wielomian& dzielnik, Wielomian& reszta) const;
public:
	Wielomian() { wsp = new double[1]{0}; stopien = 0; };
	Wielomian(const char* napis);
	Wielomian(const Wielomian& wzor);
	Wielomian(const double* tablica, int liczbaElementow);
	Wielomian(double wyrazWolny);
	~Wielomian();
	Wielomian& operator=(const Wielomian& wzor);
	Wielomian& operator+=(const Wielomian&);
	Wielomian& operator-=(const Wielomian& wi2);
	Wielomian& operator*=(const Wielomian& wi2);
	Wielomian& operator/=(const Wielomian& wi2);
	Wielomian& operator%=(const Wielomian& wi2);

	double operator()(double x) const;
	double operator[](int s) const;

	Wielomian Pochodna() const;
	void Pokaz(std::ostream& os = std::cout) const;

	int PobierzStopien() const { return stopien; }
	double PobierzWspolczynnik(int i) const {
		if (i >= 0 && i <= stopien && wsp != nullptr) return wsp[i];
		return 0.0;
	}
};
std::ostream& operator<<(std::ostream& os, const Wielomian& w);
std::istream& operator>>(std::istream& is, Wielomian& w);

Wielomian operator+(Wielomian lewy, const Wielomian& prawy);
Wielomian operator-(Wielomian lewy, const Wielomian& prawy);
Wielomian operator*(Wielomian lewy, const Wielomian& prawy);
Wielomian operator/(Wielomian lewy, const Wielomian& prawy);
Wielomian operator%(Wielomian lewy, const Wielomian& prawy);

void pomidOdstepy(const char* &napis);
int OkreslStopien(const char* napis);