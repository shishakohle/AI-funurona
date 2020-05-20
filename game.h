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

#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {North, East, South, West, Northeast, Southeast, Southwest, Northwest};

#endif

#ifndef COMMAND_H
#define COMMAND_H

enum Command {Invalid, Skip, Move, Help, Restart, Quit};

#endif

#ifndef GAME_H
#define GAME_H



#ifndef USERACTION_H
#define USERACTION_H

struct Useraction
{
	struct position end;       // TODO: end       will not be used anymore.
	struct position	direction; // TODO: direction will not be used anymore.

	struct position  start;	
	enum   Direction dir;
	enum   Command   command;
};

#endif


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
		bool gridCapturing[5][9];
		bool anotherMove;
		bool isStartTokenFromCurrentTeam;
		bool startPositionInputValid;
		bool endPositionInputValid;
		bool beenThereVar;
		bool isEndPositionFree;
		bool isMoveLengthOK;
		bool isDirectionOK;
		
		//RUNDE
		struct Useraction move(struct Useraction lastPositions);
		//ZUG
		void turn(void);
		bool isTokenFromCurrentTeam(struct position);
		bool beenThere(struct position);
		bool freePosition(struct position);
		bool isMoveLengthValid(struct position, struct position, struct position);
		bool isMoveDirectionValid(struct position, struct position,struct Useraction);
		struct position chooseToken(void);
		bool positionInputValid(struct position);
		//check if game is over and who is winner
		void gameOver(void);
		void capturingPossible();
		void checkIfCanCapture(int, int, Token);
		void updateGridToken(Token);
		//move Token from start to end position
		void moveToken (struct position, struct position);
		struct position getNeighbour(struct position, Direction);
		void capture(struct position, Direction, struct position, Direction);
		void captureToken(struct Useraction);
		void clearScreen(void);
};

#endif

