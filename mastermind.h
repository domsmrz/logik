#ifndef _MASTERMIND_H
#define _MASTERMIND_H

class Mastermind {
	int ai_id;
	int pegs;
	int colors;

	public:
	Mastermind(int, int, int);
	int* get_query();
	void send_reply(int*);

};

#endif
