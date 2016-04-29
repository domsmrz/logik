#include <cstdio>
#include <iostream>
#include <string>
#include <stdexcept>
#include "readint.h"

/***
 * Funkce, která přečte long long int ze vstupu a zkontroluje jestli tam je jen toto číslo
 * @param keep - určuje zda se jedná o poslední čílo na řádku (0) či nikoliv (1)
 * @except runtime_error - vyskytne se v případě, kdy vstup nebyl validní
 * @return - 1 v případě úspěchu, 0 v případě neúspěchu
 */
long long int read_lint(int keep) {
	static std::string buffer;
	static unsigned int idx = 0; // Pozice, kde v bufferu jsme (není nulová, pokud čteme jiné než 1. číslo z řádku)
	static int loaded = 0; // Máme načteno něco v bufferu?
	long long int num = 0;

	if (!loaded) { // Pokud nemáme nic načteno, přečteme standartní vstup
		getline(std::cin, buffer);
		if (std::cin.fail())
			throw (std::runtime_error("Neplatný zápis, zkuste prosím znovu: "));
		idx = 0;
	}
	loaded = 1;

	while (idx < buffer.length() && buffer[idx] == ' ') // Odignorujeme počáteční mezery
		++idx;

	if (buffer[idx] < '0' || buffer[idx] > '9') {
		// Pokud máme něco jiného než číslo, skončíme neúspěchem
		loaded = 0;
		if (idx == buffer.length())
			throw (std::runtime_error("Příliš málo zadaných čísel, zkuste prosím znovu: "));
		else
			throw (std::runtime_error("Neplatný zápis, zkuste prosím znovu: "));
	}

	while (idx < buffer.length() && buffer[idx] >= '0' && buffer[idx] <= '9') {
		// Přečteme celé číslo
		num *= 10;
		num += buffer[idx] - '0';
		++idx;
	}

	if (!keep) {
		// Pokud máme přečíst poslední číslo z řádku, zkontrolujeme, zda již na řádce skutečně nic není
		while (idx < buffer.length() && buffer[idx] == ' ')
			++idx;
		loaded = 0; // Čteme až do konce řádky (bufferu), takže při dalším volání fce už chceme oznámit, že nemáme načteno nic
		if (idx < buffer.length()) {
			// Na řádce ještě něco bylo - skončíme neúspěchem
			throw (std::runtime_error("Příliš mnoho zadaných čísel, zkuste prosím znovu: "));
		}
	}

	return num;
}

/***
 * Obalující funkce, která přečte nikoli long long int, ale int
 * @param keep - určuje zda se jedná o poslední čílo na řádku (0) či nikoliv (1)
 * @except runtime_error - vyskytne se v případě, kdy vstup nebyl validní
 * @return - 1 v případě úspěchu, 0 v případě neúspěchu
 */
int read_int(int keep) {
	return (int) read_lint(keep);
}
