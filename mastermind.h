#ifndef _MASTERMIND_H
#define _MASTERMIND_H

#include <vector>

class Mastermind {
	int ai_id; // Které AI se má použít (v současnosti nepoužíváno)
	int pegs; // Počet kolíků
	int colors; // Počet barev

	public:
	Mastermind(int, int, int);
	void get_query(std::vector<int>&);
	void send_reply(std::vector<int>&);

};

#endif
