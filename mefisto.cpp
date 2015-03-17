#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <list>

#include "mefisto.h"
#include "macros.h"

Mefisto::Mefisto(int ai_id, int colors, int pegs) {
	this->ai_id = ai_id;
	this->colors = colors;
	this->pegs = pegs;
	this->correct = 0;
	this->nseq = (int) pow(this->colors, this->pegs);

	this->prepare_allowed_seq();

	this->answers = new int[(this->pegs+1) * (this->pegs+1)]();
}

/*** PRIVATE ***/

void Mefisto::prepare_allowed_seq(void) {
	int i;

	for (i = 0; i < this->nseq; ++i) {
		this->allowed_seq.push_back(i);
	}

	return;
}

int Mefisto::get_answer(int final, int* query) {
	int i;

	int final_seq[this->pegs];
	for (i = this->pegs - 1; i >= 0; --i) {
		final_seq[i] = final % this->colors;
		final /= this->colors;
	}

	int correct_pegs = 0;
	int correct_colors = 0;

	for (i = 0; i < this->pegs; ++i) {
		if (final_seq[i] == query[i])
			correct_pegs++;
	}

	int final_colors[this->colors];
	int query_colors[this->colors];
	for (i = 0; i < this->colors; ++i) {
		final_colors[i] = query_colors[i] = 0;
	}

	for (i = 0; i < this->pegs; ++i) {
		final_colors[final_seq[i]]++;
		query_colors[query[i]]++;
	}

	for (i = 0; i < this->colors; ++i) {
		correct_colors += std::min(final_colors[i], query_colors[i]);
	}
	correct_colors -= correct_pegs;

	return correct_pegs * (this->pegs+1) + correct_colors;
}


/*** PUBLIC ***/

int* Mefisto::get_reply(int* query) {
	int i;
	int answerI;
	std::list<int>::iterator allowed_seq_it;

	for (allowed_seq_it = this->allowed_seq.begin(); allowed_seq_it != this->allowed_seq.end(); ++allowed_seq_it) {
		answerI = this->get_answer(*allowed_seq_it, query);
		this->answers[answerI]++;
	}

	int max = -1;
	int maxI = -1;

	for (i = 0; i < (this->pegs+1) * (this->pegs+1); ++i) {
		if (this->answers[i] > max) {
			max = this->answers[i];
			maxI = i;
		}
		this->answers[i] = 0;
	}

	for (allowed_seq_it = this->allowed_seq.begin(); allowed_seq_it != this->allowed_seq.end(); ) {
		if (this->get_answer(*allowed_seq_it, query) != maxI) {
			this->allowed_seq.erase(allowed_seq_it++);
		}
		else {
			allowed_seq_it++;
		}
	}

	int* reply = new int[this->pegs]();

	i = 0;
	while (maxI >= (this->pegs+1)) {
		reply[i] = 2;
		i++;
		maxI -= (this->pegs+1);
	}

	while (maxI > 0) {
		reply[i] = 1;
		i++;
		maxI--;
	}

	this->correct = 1;
	for (i = 0; i < this->pegs; ++i) {
		if (reply[i] != 2) {
			this->correct = 0;
			break;
		}
	}

	return reply;
}

int Mefisto::is_correct() {
	return correct;
}
