#include <cstdio>
#include "readint.h"

#define BUFFERSIZE 2000

int read_int(int* res, int keep) {
	static char buffer[BUFFERSIZE];
	static int idx = 0;
	static int loaded = 0;
	int num = 0;

	if (!loaded) {
		fgets(buffer, BUFFERSIZE, stdin);
		idx = 0;
	}

	loaded = 1;

	while (idx < BUFFERSIZE && buffer[idx] == ' ')
		++idx;

	if (buffer[idx] < '0' && buffer[idx] > '9') {
		loaded = 0;
		return 0;
	}

	while (idx < BUFFERSIZE && buffer[idx] > '0' && buffer[idx] < '9') {
		num *= 10;
		num += buffer[idx] - '0';
		++idx;
	}

	if (!keep) {
		while (idx < BUFFERSIZE && buffer[idx] == ' ')
			++idx;
		loaded = 0;
		if (buffer[idx] != '\n')
			return 0;
	}

	*res = num;

	return 1;
}
