#pragma once

class Wielomian
{
private:
	double* wsp;
	int stopien;
	void ZaktualizujStopien();

	const char* AnalizujJednomian(const char* napis);
	int AnalizujJednomiany(const char* napis);
public:
	Wielomian() { wsp = nullptr; stopien = 0; };
	Wielomian(const char*);
	Wielomian(const Wielomian& wzor);
	Wielomian(const double* tablica, int liczbaElementow);
	Wielomian(double wyrazWolny);
	~Wielomian();
	Wielomian& operator+=(const Wielomian&);
	Wielomian operator+(const Wielomian& wi2) const;
	Wielomian& operator-=(const Wielomian& wi2);
	Wielomian operator-(const Wielomian& wi2) const;
	Wielomian& operator*=(const Wielomian& wi2);
	Wielomian operator*(const Wielomian& wi2) const;
	Wielomian& operator/=(const Wielomian& wi2);
	Wielomian operator/(const Wielomian& wi2) const;
	double operator()(double x);
	double operator[](int s);
	void Pokaz() const;

	int PobierzStopien() const { return stopien; }
	double PobierzWspolczynnik(int i) const {
		if (i >= 0 && i <= stopien) return wsp[i];
		return 0.0;
	}
};

void pomidOdstepy(const char* &napis);
int OkreslStopien(const char* napis);