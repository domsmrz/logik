#ifndef _MASTERMIND_H
#define _MASTERMIND_H

class Mastermind {
	int ai_id; // Které AI se má použít (v současnosti nepoužíváno)
	int pegs; // Počet kolíků
	int colors; // Počet barev

	public:
	Mastermind(int, int, int);
	void get_query(int*);
	void send_reply(int*);

};

#endif
