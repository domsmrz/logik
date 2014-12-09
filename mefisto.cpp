#include <cstdlib>
#include <time.h>
#include "mefisto.h"
#include "macros.h"

Mefisto::Mefisto(int my_ai_id, int my_colors, int my_pegs) {
	ai_id = my_ai_id;
	colors = my_colors;
	pegs = my_pegs;
	correct = 0;

	for (int i = 0; i < colors; ++i) {
		colors_ans[i] = 0;
	}

	srand (time(NULL));
	for (int i = 0; i < pegs; ++i) {
		answer[i] = rand() % colors;
		colors_ans[answer[i]]++;
	}
}

int* Mefisto::get_reply(int* query) {
	int* reply = (int*) calloc(pegs, sizeof(int));
	int copy_colors[colors];
	for (int i = 0; i < colors; ++i) {
		copy_colors[i] = colors_ans[i];
	}

	int reply_i = 0;

	for (int i = 0; i < pegs; ++i) {
		if (query[i] == answer[i]) {
			copy_colors[query[i]]--;
			reply[reply_i++] = 2;
		}
	}

	if (reply_i == pegs)
		correct = 1;

	for (int i = 0; i < pegs; ++i) {
		if (query[i] != answer[i]) {
			if (copy_colors[query[i]]) {
				copy_colors[query[i]]--;
				reply[reply_i++] = 1;
			}
		}
	}

	for (;reply_i < pegs; ++reply_i) {
		reply[reply_i] = 0;
	}

	return reply;
}

int Mefisto::is_correct() {
	return correct;
}
