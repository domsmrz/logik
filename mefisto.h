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
		long long int nseq;

		long long int* answers;
		std::list<long long int> allowed_seq;

		void prepare_allowed_seq_all();
		void prepare_allowed_seq_rand(long long int);
		long long int get_answer(long long int, int*);

	public:
		Mefisto(int, int, int);
		void get_reply(int*);
		int is_correct();
};

#endif
