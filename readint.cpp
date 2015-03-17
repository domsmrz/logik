#include <cstdio>
#include "readint.h"

/***
 * Funkce, která přečte long long int ze vstupu a zkontroluje jestli tam je jen toto číslo
 * @param res - ukazatel na long long int, kam se má zapsat přečtené číslo
 * @param keep - určuje zda se jedná o poslední čílo na řádku (0) či nikoliv (1)
 * @return - 1 v případě úspěchu, 0 v případě neúspěchu
 */
int read_lint(long long int* res, int keep) {
	static char buffer[BUFFERSIZE];
	static int idx = 0; // Pozice, kde v bufferu jsme (není nulová, pokud čteme jiné než 1. číslo z řádku
	static int loaded = 0; // Máme načteno něco v bufferu?
	long long int num = 0;

	if (!loaded) { // Pokud nemáme nic načteno, přečteme standartní vstup
		fgets(buffer, BUFFERSIZE, stdin);
		idx = 0;
	}

	loaded = 1;

	while (idx < BUFFERSIZE && buffer[idx] == ' ') // Odignorujeme počáteční mezery
		++idx;

	if (buffer[idx] < '0' || buffer[idx] > '9') {
		// Pokud máme něco jiného než číslo, skončíme neúspěchem
		loaded = 0;
		return 0;
	}

	while (idx < BUFFERSIZE && buffer[idx] >= '0' && buffer[idx] <= '9') {
		// Přečteme celé číslo
		num *= 10;
		num += buffer[idx] - '0';
		++idx;
	}

	if (!keep) {
		// Pokud máme přečíst poslední číslo z řádku, zkontrolujeme, zda již na řádce skutečně nic není
		while (idx < BUFFERSIZE && buffer[idx] == ' ')
			++idx;
		loaded = 0; // Čteme až do konce řádky (bufferu), takže při dalším volání fce už chceme oznámit, že nemáme načteno nic
		if (buffer[idx] != '\n') {
			// Na řádce ještě něco bylo - skončíme neúspěchem
			return 0;
		}
	}

	*res = num;

	return 1;
}

/***
 * Obalující funkce, která přečte nikoli long long int, ale int
 * @param res - ukazatel na int, kam se má zapsat výsledek
 * @param keep - určuje zda se jedná o poslední čílo na řádku (0) či nikoliv (1)
 * @return - 1 v případě úspěchu, 0 v případě neúspěchu
 */
int read_int(int* res, int keep) {
	long long int lres;
	if(read_lint(&lres, keep)) {
		*res = lres;
		return 1;
	}
	return 0;
}
