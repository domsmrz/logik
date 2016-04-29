#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <list>
#include <stdexcept>

#include "readint.h"
#include "mefisto.h"

Mefisto::Mefisto(int ai_id, int colors, int pegs) {
	this->ai_id = ai_id;
	this->colors = colors;
	this->pegs = pegs;
	this->correct = 0;
	this->nseq = (long long int) pow(this->colors, this->pegs);

	switch(ai_id) {
		case 0:
			// "Normální" AI - vybere jednu náhodnou posloupnost a tu prohlásí za koncovou
			this->prepare_allowed_seq_rand(1);
			break;
		case 1:
			// "MinMax" - mezi přípustné posloupnosti na začátku zařadí úplně všechny
			this->prepare_allowed_seq_all();
			break;
		case 2:
			// "Omezený MinMax" - vybere náhodně n sekvencí a ty prohlásí za přípustné;
			long long int n;
			std::cout << "Zadejte hloubku algoritmu: ";
			int check = 0;
			while (!check) {
				check = 1;
				try {
					n = read_lint(0);
				}
				catch (std::runtime_error e) {
					std::cout << e.what();
					check = 0;
				}
			}
			this->prepare_allowed_seq_rand(n);
			break;
	}

	this->answers = new long long int[(this->pegs+1) * (this->pegs+1)]();
}

/*** PRIVATE ***/

/***
 * Funkce, která do přípustných polsoupností zařadí n náhodných posloupností
 * @param number - počet posloupností k zařazení
 */
void Mefisto::prepare_allowed_seq_rand(long long int number) {
	srand(time(NULL));
	for (long long int i = 0; i < number; ++i) {
		this->allowed_seq.push_back(rand() % this->nseq);
	}
}

/***
 * Funkce, která do přípustných posloupností zařadí všechny možné posloupnosti
 */
void Mefisto::prepare_allowed_seq_all() {
	long long int i;

	for (i = 0; i < this->nseq; ++i) {
		this->allowed_seq.push_back(i);
	}
}

/***
 * Funkce, která pro daný dotaz a danou správnou posloupnost vrátí příslušnou odpověď
 * @param final - správná posloupnost zakódováná jako číslo v soustavě o základu rovnému počtu barev
 * @param query - pole s dotazem
 * @return - příslušná odpověď zakódovaná jako dvojciferné číslo v soustavě o základu (#kolíků+1), kde 1. cifra je počet správných umístění a 2. počet správných barev
 */
long long int Mefisto::get_answer(long long int final, int* query) {
	int i;

	int final_seq[this->pegs];
	for (i = this->pegs - 1; i >= 0; --i) {
		// Rozkódujeme správnou posloupnost do pole
		final_seq[i] = final % this->colors;
		final /= this->colors;
	}

	int correct_pegs = 0;
	int correct_colors = 0;

	for (i = 0; i < this->pegs; ++i) {
		// Zjistíme, kolik kolíků odpovídá s barvou i umístěním
		if (final_seq[i] == query[i])
			correct_pegs++;
	}

	int final_colors[this->colors]; // Kolikrát se i-tá barva vyskytuje ve správné posloupnosti
	int query_colors[this->colors]; // Kolikrát se i-tá barva vyskytuje v dotazu
	for (i = 0; i < this->colors; ++i) {
		final_colors[i] = query_colors[i] = 0;
	}

	for (i = 0; i < this->pegs; ++i) {
		final_colors[final_seq[i]]++;
		query_colors[query[i]]++;
	}

	for (i = 0; i < this->colors; ++i) {
		// Za každou barvu přičteme, kolikrát jsme se do ní strefili
		correct_colors += std::min(final_colors[i], query_colors[i]);
	}
	// Musíme odečíst ty barvy, které jsme již vyjádřili tím, že jsme se strefili přímo kolíkem
	correct_colors -= correct_pegs;

	return correct_pegs * (this->pegs+1) + correct_colors;
}


/*** PUBLIC ***/

/***
 * Funkce, která dostane dotaz a má na něj vygenerovat odpověď
 * @param query - pole s dotazem, do kterého se nakonec uloží i odpověď
 */
void Mefisto::get_reply(int* query) {
	long long int i;
	int answerI;
	std::list<long long int>::iterator allowed_seq_it;

	for (allowed_seq_it = this->allowed_seq.begin(); allowed_seq_it != this->allowed_seq.end(); ++allowed_seq_it) {
		// Projdeme všechny přípustné kódy a u každé odpovědi si poznamenáme, kolikrát jsme ji dostali
		answerI = this->get_answer(*allowed_seq_it, query);
		this->answers[answerI]++;
	}

	long long int max = -1;
	int maxI = -1;

	for (i = 0; i < (this->pegs+1) * (this->pegs+1); ++i) {
		// Vybereme tu nejčastější odpověď (pokud je víc stejně častých vybereme tu lexikograficky menší, tedy "vše správně" odpovídáme jen když už jinak nemůžeme)
		if (this->answers[i] > max) {
			max = this->answers[i];
			maxI = i;
		}
		this->answers[i] = 0;
	}

	for (allowed_seq_it = this->allowed_seq.begin(); allowed_seq_it != this->allowed_seq.end(); ) {
		// Odstraníme ty dosud přípustné kódy, na které bychom dostali jinou odpověď na nynější dotaz, než vrátíme
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

	// Zkontrolujeme, jesli jsme odpověděli "vše správně"
	this->correct = 1;
	for (i = 0; i < this->pegs; ++i) {
		if (query[i] != 2) {
			this->correct = 0;
			break;
		}
	}
}

/***
 * Funkce, která pouze vrátí to, jestli jsme už dostali dotaz, na který jsme odpověděli, že se jedná o hledanou posloupnost
 * @return - 1 v případě, že jsme takový dotaz dostlali, jinak 0
 */
int Mefisto::is_correct() {
	return this->correct;
}
