#include "token.h"

#ifndef CELL_H
#define CELL_H

class Cell
{
	public:
		void setToken(Token);
		void setOccupied(bool);
		bool getOccupied();
		char printStatus();
		Token getToken();
		void deleteToken();
	private:
		struct position;
		Token token;
		bool isOccupied;
};

#endif

