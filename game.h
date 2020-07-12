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

#define LINES_TO_CLEAR 1

#include <map>
#include <vector>	
#include "board.h"
#include "player.h"
#include "tree.h"






#ifndef GAME_H
#define GAME_H

class Game
{
	public:
		Game(void);
		bool start();
		static enum Direction string2direction(string);
		static struct position string2position(string);
		vector<string> errorvec;
		
	private:
		Player *currentPlayer;
		bool gameWon;
		bool quit;
		bool restart;
		bool skip;
		Player *winner;
		Board meinSpielbrett; // TODO: rename
		Player playerWhite, playerBlack;
		bool grid[5][9]; //beenThere
		struct Grid gridCapturing;
		bool anotherMove;
		bool isStartTokenFromCurrentTeam;
		bool startPositionInputValid;
		bool endPositionInputValid;
		bool beenThereVar;
		bool isEndPositionFree;
		bool isMoveLengthOK;
		bool isDirectionOK;
		bool capturingYes;
		int counterMoves;
		int counterPossibleMoves;
		struct Useraction possibleMoves[150];

		//of first move
		struct position currentPosition;
		enum Direction lastDirection;
		
		//RUNDE
		void move(); //struct Useraction lastPositions
		//ZUG
		void turn(void);
		bool isMoveValid(struct position,  struct position, enum Direction); //, struct Useraction, , enum Command
		bool isTokenFromCurrentTeam(struct position);
		bool beenThere(struct position);
		bool freePosition(struct position);
		bool areFieldsConnected(struct position, int direction);
		bool isMoveDirectionValid(enum Direction);
		bool sameTokenSelected(struct position);
		bool cantSkipFirstMove(enum Command);
		struct position chooseToken(void);
		bool positionInputValid(struct position);
		//check if game is over and who is winner
		void gameOver(void);
		int calculateDirection (struct position, struct position);
		//can another token be capture?
		bool rightfulCapturing(struct position, struct position);
		bool capturingPossible();
		bool checkIfCanCapture(int, int, struct position);
		struct Grid updateGridToken(struct position);
		bool capturingAgain();
		//move Token from start to end position
		void moveToken (struct Useraction);
		static struct position getNeighbour(struct position, Direction);
		int capture(struct Useraction, struct position, Direction, struct position, Direction, string);
		void captureToken(struct Useraction);
		void clearScreen(void);
		struct Useraction getHumanUseraction(void);
		struct Useraction getAIUseraction(void);
		void setFieldOfView(struct position, struct Grid);
		std::vector<Useraction> getPossibleMoves();
		enum Direction getDirectionFromInteger (int);
		int minMaxAlgorithm(Board, int, bool);
		float nextNode(Node *, int, bool);
		void printNodeScore(Node *);
		void turnTest(Node, struct Useraction);
		void moveNew(Useraction);
		int heuristik3(Team, Board);
		int heuristik1(Team, Board);
		float heuristik2(Team, Board);
};

#endif

