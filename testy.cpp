#include "Wielomiany.h"

using namespace std;

int main() {
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
			cout << endl;
		}
	}

	cout << "\n--- TESTY ---" << endl;

	Wielomian a("x^2 + 5x + 6");
	Wielomian b("x + 2");
	cout << "a = " << a << ", b = " << b << endl << endl;
	cout << "a / b = " << (a / b) << endl;
	cout << "a % b = " << (a % b) << endl;
	cout << "10.5 + b = " << (10.5 + b) << endl;
	cout << "b * 2.0 = " << (b * 2.0) << endl << endl;

	Wielomian kopia = a;
	Wielomian przypisany;
	przypisany = b;
	cout << "Kopia a: " << kopia << ", Przypisany b: " << przypisany << endl << endl;

	cout << "Pochodna z a: " << a.Pochodna() << endl;
	cout << "Wartosc a(2) schematem Hornera: " << a(2.0) << endl;
	cout << "Wspolczynnik przy x^1 w a: " << a[1] << endl << endl;

	Wielomian zKlawiatury;
	cout << "Podaj wlasny wielomian: ";
	cin >> zKlawiatury;
	cout << "Wczytano: " << zKlawiatury << endl;

	return 0;
}