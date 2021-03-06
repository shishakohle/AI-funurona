#include "cell.h"

#ifndef BOARD_H
#define BOARD_H

class Board
{
	private:
		Cell cells[5][9];
		int tokensLeftWhite = 0; // TODO: local variable
		int tokensLeftBlack = 0; // TODO: local variable
		float heuristik2grid[5][9];
	
	public:
		void init(void);
		void print(void);
		float getheuristik2(struct position);
		Cell getCell(struct position);
		void setTokenOnCell(struct position, Token);
		void emptyCell(struct position);
		void updateLeftTokens(void);
		int getLeftTokensWhite(void);
		int getLeftTokensBlack(void);
		void setFieldOfView(struct position, struct Grid);
};

#endif

