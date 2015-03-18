#include <cstdio>
#include <cstdlib>
#include "readint.h"
#include "mastermind.h"

Mastermind::Mastermind(int ai_id, int colors, int pegs) {
	this->ai_id = ai_id;
	this->colors = colors;
	this->pegs = pegs;
}

/***
 * Funkce, která má za úkol zjistit další dotaz na hru
 * @param query - místo, kam se má dotaz zapsat
 */
void Mastermind::get_query(int* query) {
	printf("Zadejte váš tip: ");
	for (int i = 0; i < this->pegs; ++i) {
		if (!read_int(&(query[i]), i < this->pegs-1) || query[i] >= this->colors) {
			// Pokud se nějaké číslo nepodařilo načíst, skartujeme co jsme přečetli a čteme od začátku
			i = -1;
			printf("Neplatný zápis, zkuste prosím znovu: ");
		}
	}
}

/***
 * Funkce Masterminda, pomocí které zjistí, jakou odpověď dostal od Mefista
 * (Aktuálně jen vypíše na výstup, jelikož Mastermind není AI, ale je ovládán člověkem)
 * @param reply - pole, ve kterém je popsaná odpověď
 */
void Mastermind::send_reply(int* reply) {
	printf("Odpověď: ");
	for (int i = 0; i < this->pegs; ++i) {
		printf("%d ", *(reply + i));
	}
	printf("\n");
}
