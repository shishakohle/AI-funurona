/* A B C D E F G H I
 * #-#-#-#-#-#-#-#-# 1
 * |\|/|\|/|\|/|\|/| 
 * #-#-#-#-#-#-#-#-# 2
 * |/|\|/|\|/|\|/|\| 
 * #-O-#-O-.-#-O-#-O 3
 * |\|/|\|/|\|/|\|/|
 * O-O-O-O-O-O-O-O-O 4
 * |/|\|/|\|/|\|/|\|
 * O-O-O-O-O-O-O-O-O 5
 * 
 * Size: 9x5
 * initial state: 22 token for each color
 * colors: black -> # , white -> O , empty cell -> .
 */

#define LINES_TO_CLEAR 50

#include <iostream>
	using namespace std;
	
#include "board.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H

class Game
{
	public:
		Game(void);
		void start(); // TODO: private??
		
	private:
		//enum Team currentTeam;
		Player *currentPlayer;
		bool gameWon;
		Player *winner;
		Board meinSpielbrett;
		Player playerWhite, playerBlack;
		bool grid[5][9];
		bool anotherMove;
		bool isStartTokenFromCurrentTeam;
		bool beenThereVar;
		bool isEndPositionFree;
		bool isMoveLengthOK;
		
		//RUNDE
		void move(void);
		//ZUG
		void turn(void);
		bool isTokenFromCurrentTeam(struct position);
		bool beenThere(struct position);
		bool freePosition(struct position);
		bool isMoveLengthValid(struct position, struct position);
		struct position chooseToken(void);
		//check if game is over and who is winner
		void gameOver(void);
		//move Token from start to end position
		void moveToken (struct position, struct position);
		void clearScreen(void);
};

#endif

