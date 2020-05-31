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

#include <map>
	
#include "board.h"
#include "player.h"

#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {North, East, South, West, Northeast, Southeast, Southwest, Northwest};

#endif

#ifndef COMMAND_H
#define COMMAND_H

enum Command {
	Invalid,
	Skip,
	Move,
	Help,
	Restart,
	Quit
};

static const map <string, Command> commandMap
{
	{ "SKIP",    Skip },
	{ "HELP",    Help },
	{ "RESTART", Restart },
	{ "QUIT",    Quit},
	{ "EXIT",    Quit},
	{ "BYE",     Quit}
};

#endif

#ifndef USERACTION_H
#define USERACTION_H

struct Useraction
{
	struct position  start;
	struct position  end;
	enum   Direction dir;
	enum   Command   command;
};

#endif

#ifndef GAME_H
#define GAME_H

class Game
{
	public:
		Game(void);
		void start(); // TODO: private??
		
	private:
		Player *currentPlayer;
		bool gameWon;
		Player *winner;
		Board meinSpielbrett; // TODO: rename
		Player playerWhite, playerBlack;
		bool grid[5][9];
		struct Grid gridCapturing;
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
		bool isMoveValid(struct position,  struct position, int direction, struct Useraction);
		bool isTokenFromCurrentTeam(struct position);
		bool beenThere(struct position);
		bool freePosition(struct position);
		bool areFieldsConnected(struct position, int direction);
		bool isMoveDirectionValid(struct Useraction, int direction);
		struct position chooseToken(void);
		bool positionInputValid(struct position);
		//check if game is over and who is winner
		void gameOver(void);
		int calculateDirection (struct position, struct position);
		bool rightfulCapturing(struct position, struct position);
		bool capturingPossible();
		bool checkIfCanCapture(int, int, struct position);
		struct Grid updateGridToken(struct position);
		//move Token from start to end position
		void moveToken (struct position, struct position);
		struct position getNeighbour(struct position, Direction);
		void capture(struct position, Direction, struct position, Direction);
		void captureToken(struct Useraction);
		void clearScreen(void);
		struct Useraction getUseraction(void);
		// TODO struct position string2position(string); // TODO: move this to public area of Class Board
		// TODO enum Direction string2direction(struct position, struct position); // TODO: move this to public area of this Class Game
		void setFieldOfView(struct position, struct Grid);
};

#endif

