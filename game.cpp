#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "mefisto.h"
#include "mastermind.h"
#include "readint.h"

using namespace std;

int reader() {
	int n;
	int check = 0;
	while (!check) {
		check = 1;
		try {
			n = read_int(0);
		}
		catch (runtime_error e) {
			cout << e.what();
			check = 0;
		}
	}
	return n;
}

int main() {
	int pegs, colors, mef_ai;

	// Načítání parametrů hry
	cout << "Zadejte počet barev: ";
	colors = reader();

	cout << "Zadejte počet kolíků: ";
	pegs = reader();

	cout << "Vyberte si AI proti kterému chcete hrát:\n";
	cout << "0 - Náhodný (obvyklá hra)\n";
	cout << "1 - MinMax (nevhodný pro velké hry)\n";
	cout << "2 - Omezený MinMax\n";
	do {
		mef_ai = reader();
	} while (mef_ai > 2);

	Mefisto mefisto(mef_ai, colors, pegs);
	Mastermind mastermind(0, colors, pegs);

	int turns = 0;
	int* packet = new int[pegs](); // Paměť, ve které si Mastermind a Mefisto předávají data
	while (!mefisto.is_correct()) {
		// Smyčka komunikace mezi Mastermindem a Mefistem dokud se nevyhraje hra
		mastermind.get_query(packet);
		mefisto.get_reply(packet);
		mastermind.send_reply(packet);
		++turns;
	}

	cout << "Vyhráli jste! Počet tahů: " <<  turns << std::endl;

	return 0;
}
