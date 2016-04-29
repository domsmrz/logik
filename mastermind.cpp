#include <iostream>
#include <vector>
#include <stdexcept>
#include "readint.h"
#include "mastermind.h"

Mastermind::Mastermind(int colors, int pegs) {
	this->colors = colors;
	this->pegs = pegs;
}

/***
 * Funkce, která má za úkol zjistit další dotaz na hru
 * @param query - místo, kam se má dotaz zapsat
 */
void Mastermind::get_query(std::vector<int>& query) {
	std::cout << "Zadejte váš tip: ";
	for (int i = 0; i < this->pegs; ++i) {
		// Zkouší načíst příslušný počet čísel ze vstupu
		try {
			query[i] = read_int(i < this->pegs-1); // Zde mohla vznikout výjimka
			if (query[i] >= this->colors) { // Ještě zkontrolujeme, že sedí barva do příslušného rozptylu
				if (i < this->pegs) {
					try { // Pokud nejsme nakonci, tak přečteme do konce bufferu a smažeme jej tak
						read_int(0);
					}
					catch (std::runtime_error e) {}
				}
				throw (std::runtime_error("Neplatná barva, zkuste prosím znovu: "));
			}
		}
		catch (std::runtime_error e) {
			i = -1;
			std::cout << e.what();
		}
	}
}

/***
 * Funkce Masterminda -- hráče, pomocí které zjistí, jakou odpověď dostal od Mefista
 * @param reply - pole, ve kterém je popsaná odpověď
 */
void Mastermind::send_reply(std::vector<int>& reply) {
	std::cout << "Odpověď: ";
	for (int i = 0; i < this->pegs; ++i) {
		std::cout << reply[i] << " ";
	}
	std::cout << std::endl;
}
