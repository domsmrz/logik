#include <cstdio>
#include <cstdlib>
#include "readint.h"
#include "mastermind.h"
#include "macros.h"

Mastermind::Mastermind(int ai_id, int colors, int pegs) {
	this->ai_id = ai_id;
	this->colors = colors;
	this->pegs = pegs;
}

void Mastermind::get_query(int* query) {
	printf("Zadejte váš tip: ");
	for (int i = 0; i < this->pegs; ++i) {
		if (!read_int(&(query[i]), i < this->pegs-1)) {
			i = -1;
			printf("Neplatný zápis, zkuste prosím znovu: ");
		}
	}
}

void Mastermind::send_reply(int* reply) {
	printf("Odpověď: ");
	for (int i = 0; i < this->pegs; ++i) {
		printf("%d ", *(reply + i));
	}
	printf("\n");
}
