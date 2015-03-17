#ifndef _MEFISTO_H
#define _MEFISTO_H

#include "macros.h"
#include <list>

class Mefisto {
	private:
		int ai_id; // AI, které se má použít
		int pegs; // Počet kolíků
		int colors; // Počet barev
		int correct; // Dostal jsem už odpověď, na kterou jsem odpověděl ukončením hry?
		long long int nseq; // Celkový počet možných sekvencí v daném počtu barev a kolíků

		long long int* answers; // Pole s ohodnocením jednotlivých odpovědí, když se zjišťuje odpověď
					// --- odpověd na i té pozici je lze chápat tak, že i je dvojciferné číslo
					// --- se základem (#kolíků+1), kde 1. cifra vyjadřuje počet správně umístěncýh
					// --- kolíků a 2. cifra počet správných barev
		std::list<long long int> allowed_seq; // Seznam ještě přípustných koncových odpovědí

		void prepare_allowed_seq_all();
		void prepare_allowed_seq_rand(long long int);
		long long int get_answer(long long int, int*);

	public:
		Mefisto(int, int, int);
		void get_reply(int*);
		int is_correct();
};

#endif
