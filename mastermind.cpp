#include <cstdio>
#include <cstdlib>
#include "mastermind.h"
#include "macros.h"

Mastermind::Mastermind(int ai_id, int colors, int pegs) {
	this->ai_id = ai_id;
	this->colors = colors;
	this->pegs = pegs;
}

void Mastermind::get_query(int* query) {
	for (int i = 0; i < this->pegs; ++i) {
		scanf("%d", &(query[i]));
	}
}

void Mastermind::send_reply(int* reply) {
	for (int i = 0; i < this->pegs; ++i) {
		printf("%d ", *(reply + i));
	}
	printf("\n");
}
