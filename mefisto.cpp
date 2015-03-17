#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <list>

#include "readint.h"
#include "mefisto.h"
#include "macros.h"

Mefisto::Mefisto(int ai_id, int colors, int pegs) {
	this->ai_id = ai_id;
	this->colors = colors;
	this->pegs = pegs;
	this->correct = 0;
	this->nseq = (int) pow(this->colors, this->pegs);

	switch(ai_id) {
		case 0:
			this->prepare_allowed_seq_rand(1);
			break;
		case 1:
			this->prepare_allowed_seq_all();
			break;
		case 2:
			int n;
			printf("Zadejte hloubku algoritmu: ");
			while(!read_int(&n, 0))
				printf("Neplatný zápis, zkuste prosím znovu: ");
			this->prepare_allowed_seq_rand(n);
			break;
	}

	this->answers = new int[(this->pegs+1) * (this->pegs+1)]();
}

/*** PRIVATE ***/

void Mefisto::prepare_allowed_seq_rand(int number) {
	srand(time(NULL));
	for (int i = 0; i < number; ++i) {
		this->allowed_seq.push_back(rand() % this->nseq);
	}
}

void Mefisto::prepare_allowed_seq_all() {
	int i;

	for (i = 0; i < this->nseq; ++i) {
		this->allowed_seq.push_back(i);
	}
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

void Mefisto::get_reply(int* query) {
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

	// Začneme zapisovat výsledek

	i = 0;
	while (maxI >= (this->pegs+1)) {
		query[i] = 2;
		i++;
		maxI -= (this->pegs+1);
	}

	while (maxI > 0) {
		query[i] = 1;
		i++;
		maxI--;
	}

	while (i < this->pegs) {
		query[i] = 0;
		i++;
	}	

	this->correct = 1;
	for (i = 0; i < this->pegs; ++i) {
		if (query[i] != 2) {
			this->correct = 0;
			break;
		}
	}
}

int Mefisto::is_correct() {
	return this->correct;
}
