#include <cstdio>
#include "readint.h"

int read_lint(long long int* res, int keep) {
	static char buffer[BUFFERSIZE];
	static int idx = 0;
	static int loaded = 0;
	long long int num = 0;

	if (!loaded) {
		fgets(buffer, BUFFERSIZE, stdin);
		idx = 0;
	}

	loaded = 1;

	while (idx < BUFFERSIZE && buffer[idx] == ' ')
		++idx;

	if (buffer[idx] < '0' || buffer[idx] > '9') {
		loaded = 0;
		return 0;
	}

	while (idx < BUFFERSIZE && buffer[idx] >= '0' && buffer[idx] <= '9') {
		num *= 10;
		num += buffer[idx] - '0';
		++idx;
	}

	if (!keep) {
		while (idx < BUFFERSIZE && buffer[idx] == ' ')
			++idx;
		loaded = 0;
		if (buffer[idx] != '\n') {
			return 0;
		}
	}

	*res = num;

	return 1;
}

int read_int(int* res, int keep) {
	long long int lres;
	if(read_lint(&lres, keep)) {
		*res = lres;
		return 1;
	}
	return 0;
}
