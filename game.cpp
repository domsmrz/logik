#include <cstdio>
#include "mefisto.h"
#include "mastermind.h"
#include "macros.h"

using namespace std;

int main() {
	Mefisto mefisto(0, 6, 4);
	Mastermind mastermind(0, 6, 4);

	int* packet;
	while (!mefisto.is_correct()) {
		packet = mastermind.get_query();
		packet = mefisto.get_reply(packet);
		mastermind.send_reply(packet);
	}

	return 0;
}
