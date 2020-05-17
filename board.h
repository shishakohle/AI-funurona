#include "cell.h"

#ifndef POSITION
#define POSITION

struct position
{
	int column,row;
};

struct superstruct
{
	struct position start,end,direction;
};

#endif

#ifndef BOARD_H
#define BOARD_H

class Board
{
	private:
		Cell cells[5][9];
	
	public:
		void init(void);
		void print(void);
		Cell getCell(struct position);
		void setTokenOnCell(struct position, Token);
		void emptyCell(struct position);
};

#endif

