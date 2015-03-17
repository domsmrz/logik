#include <cstdio>
#include "mefisto.h"
#include "mastermind.h"
#include "macros.h"
#include "readint.h"

using namespace std;

int main() {
	int pegs, colors;

	scanf("%d%d", &colors, &pegs);
	Mefisto mefisto(1, colors, pegs);
	Mastermind mastermind(0, colors, pegs);

	int* packet = new int[pegs]();
	while (!mefisto.is_correct()) {
		mastermind.get_query(packet);
		mefisto.get_reply(packet);
		mastermind.send_reply(packet);
	}

	return 0;
}
