#include <cstdio>
#include "mefisto.h"
#include "mastermind.h"
#include "readint.h"

using namespace std;

int main() {
	int pegs, colors, mef_ai;

	// Načítání parametrů hry
	printf("Zadejte počet barev: ");
	while (!read_int(&colors, 0))
		printf("Neplatný zápis, zkuste prosím znovu: ");

	printf("Zadejte počet kolíků: ");
	while (!read_int(&pegs, 0))
		printf("Neplatný zápis, zkuste prosím znovu: ");

	printf("Vyberte si AI proti kterému chcete hrát:\n");
	printf("0 - Náhodný (obvyklá hra)\n");
	printf("1 - MinMax (nevhodný pro velké hry)\n");
	printf("2 - Omezený MinMax\n");
	while (!read_int(&mef_ai, 0) || mef_ai > 2)
		printf("Neplatný zápis, zkuste prosím znovu: ");

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

	printf("Vyhráli jste! Počet tahů: %d\n", turns);

	return 0;
}
