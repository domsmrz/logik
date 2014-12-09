#include <cstdio>
#include <cstdlib>
#include "mastermind.h"
#include "macros.h"

Mastermind::Mastermind(int my_ai_id, int my_colors, int my_pegs) {
	ai_id = my_ai_id;
	colors = my_colors;
	pegs = my_pegs;
}

int* Mastermind::get_query() {
	int* query = (int*) calloc(pegs, sizeof(int));
	for (int i = 0; i < pegs; ++i) {
		scanf("%d", &(query[i]));
	}

	return query;
}

void Mastermind::send_reply(int* reply) {
	for (int i = 0; i < pegs; ++i) {
		printf("%d ", *(reply + i));
	}
	printf("\n");
}
