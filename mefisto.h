#ifndef _MEFISTO_H
#define _MEFISTO_H

#include "macros.h"
#include <list>

class Mefisto {
	private:
		int ai_id;
		int pegs;
		int colors;
		int answer[MAX_PINS];
		int colors_ans[MAX_COLORS];
		int correct;
		int nseq;

		int* answers;
		std::list<int> allowed_seq;

		void prepare_allowed_seq();
		int get_answer(int, int*);

	public:
		Mefisto(int, int, int);
		int* get_reply(int*);
		int is_correct();
};

#endif
