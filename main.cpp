#include "Wielomiany.h"
#include <iostream>

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
		}
	}
}