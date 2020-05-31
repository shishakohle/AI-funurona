#include "token.h"

#ifndef CELL_H
#define CELL_H

class Cell
{
	public:
		void setToken(Token);
		void setOccupied(bool);
		bool getOccupied(void);
		char printStatus(void);
		Token getToken(void);
		void deleteToken(void);
		void setFieldOfView(struct Grid fieldOfView);
	private:
		struct position;
		Token token;
		bool isOccupied;
};

#endif

