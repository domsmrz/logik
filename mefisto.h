#ifndef _MEFISTO_H
#define _MEFISTO_H

#include "macros.h"

class Mefisto {
	int ai_id;
	int pegs;
	int colors;
	int answer[MAX_PINS];
	int colors_ans[MAX_COLORS];
	int correct;

	public:
	Mefisto(int, int, int);
	int* get_reply(int*);
	int is_correct();
};

#endif
