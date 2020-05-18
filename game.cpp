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

#include <fstream>
#include "game.h"

Game::Game(void)
{
	//this->currentTeam = WHITE;
	this->currentPlayer = &playerWhite;
	this->gameWon = false;
	this->playerWhite.setTeam(WHITE);
	this->playerBlack.setTeam(BLACK);

	meinSpielbrett.init();
}

void Game::start() // TODO: private??
{
	// clear screen
	this->clearScreen();
	
	// print welcome screen
	ifstream welcomeScreenFile;
	welcomeScreenFile.open("welcome.txt");
	if(welcomeScreenFile)
	{
		string line;
		while( getline(welcomeScreenFile, line) )
			cout << line << endl;
	}
	else
	{
		cout << "Welcome to Corona FUNurona!\n" << endl;
	}
	
	string playerName = "";
	
	// create Player for team WHITE
	do
	{
		cout << "Please enter the name for the WHITE player: " << flush;
		getline(cin, playerName);
	}
	while( playerName.empty() );
	this->playerWhite.setName(playerName);
	cout << "Hello " << this->playerWhite.getName() <<". " << flush;
	cout << "You're on the WHITE team, your tokens look like this: " << Token::asChar(WHITE) << "\n" << endl;
	
	// create Player for team BLACK
	do
	{
		cout << "Please enter the name for the BLACK player: " << flush;
		getline(cin, playerName);
	}
	while( playerName.empty() );
	this->playerBlack.setName(playerName);
	cout << "Hello " << this->playerBlack.getName() <<". " << flush;
	cout << "You're on the BLACK team, your tokens look like this: " << Token::asChar(BLACK) << "\n" << endl;
	
	cout << "Team WHITE (hence "<< this->playerWhite.getName() << "-" << Token::asChar(WHITE) <<") will begin." << endl; // TODO manage inconsistencies with constructor
	cout << "Press <ENTER> to start the game." << flush;
	getline(cin,playerName);
	
	while(!gameWon)
	{
		anotherMove = true; //(re)move later
		turn();
		gameOver();
		//change current player
		if(currentPlayer->getTeam() == WHITE)
		{
			currentPlayer = &playerBlack;
		}
		else
		{
			currentPlayer = &playerWhite;
		}

	}
	cout << "The game is over. "<< this->winner->getName() <<"you have won. Congratulations!" << endl;
}

	
// ZUG
struct Useraction Game::move(struct Useraction lastPositions)
{
	// clear screen
	struct position startPosition;
	struct position endPosition;
	struct position direction;
	do {

	this->clearScreen();
	
	meinSpielbrett.print();

	//TO-DO: Abfrage ob Spielfelder existieren (zB 9/9 = false)
	
	cout << "\nPlayer " << this->currentPlayer->getName() << "-" << Token::asChar( this->currentPlayer->getTeam() ) << ": " << "Make your turn!\n" << endl;
	
	cout << "Choose startpostion" << endl;
	startPosition = chooseToken();
		cout << "\tStartposition COL: " << startPosition.column << endl;
		cout << "\tStartposition ROW: " << startPosition.row << endl;

	// Ist auf dieser Position ein Token von dem Team?
	isStartTokenFromCurrentTeam = isTokenFromCurrentTeam(startPosition);

	cout << "Choose endposition:" << endl;
	endPosition = chooseToken();
		cout << "\tEndposition COL: " << endPosition.column << endl;
		cout << "\tEndposition ROW: " << endPosition.row << endl;

	startPositionInputValid = positionInputValid(startPosition);
	endPositionInputValid = positionInputValid(endPosition);

	//war in diesem Zug schon mal auf diesem spielfeld?
		
	beenThereVar = beenThere(endPosition);
	//if beenThereVar = false --> dont move token --> ask again
	//ev. endlos whileschleife von position auswahl + move machen, wenn alle if true --> break, sonst von vorne bis zug valid


	// Kann dieser Zug ausgeführt werden?
	// - Ist die Position eine freie Position?
	isEndPositionFree = freePosition(endPosition);
	
	// - ist dieses feld erreichbar? (zugweite 1, felder müssen verbunden sein)
	isMoveLengthOK = isMoveLengthValid(startPosition, endPosition, direction);

	isDirectionOK = isMoveDirectionValid(startPosition, endPosition,lastPositions);

	//TO-DO: LUKAS
	//only move when all rules are true (Lukas - combination rule se) --> otherwise: chose again


	}while(!(isMoveLengthOK && isEndPositionFree && beenThereVar && isStartTokenFromCurrentTeam && startPositionInputValid && endPositionInputValid && isDirectionOK));
	moveToken(startPosition, endPosition);
	lastPositions.start = startPosition;
	lastPositions.end = endPosition;
	meinSpielbrett.print();
}

// RUNDE
void Game::turn(void)
{
 struct Useraction lastPositions;
	//check rules
	//clear grid for check "beenThere"
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			grid[row][column] = 0;
		}
		cout << endl;
	}

	//wäre dann zB die Schleife die erneute Züge (moves) erlaubt, wenn man wieder wen schmeißen kann
	do
	{
			lastPositions = move(lastPositions);
			anotherMove = false;
	}
	while(anotherMove); //TO-DO: need to adapt anotherMove --> only if additional move allowed
	
}

bool Game::isTokenFromCurrentTeam(struct position position)
{
	enum Team tokenTeam = meinSpielbrett.getCell(position).getToken().getTeam();
	
	if(tokenTeam == this->currentPlayer->getTeam())
	{
		return true;
	} else 
	{
		return false;
	}
}

bool Game::beenThere(struct position endPosition)
{
	if(grid[endPosition.row][endPosition.column] == 0)
	{
		grid[endPosition.row][endPosition.column] = 1;
		return true;
	}
	else
	{
		cout << "You have already been there. Move invalid. Choose another endposition." << endl;
		return false;
	}
}

bool Game::freePosition(struct position position)
{
	if(meinSpielbrett.getCell(position).getOccupied() == 1 ){
		return false;
	} 
	else
	{
		return true;
	}
}

bool Game::isMoveDirectionValid(struct position start, struct position end, struct Useraction lastpositions){
	int dirColumn = end.column - start.column;
	int dirRow = end.row - start.row;
	
	if (dirColumn==lastpositions.direction.column && dirRow==lastpositions.direction.row)
	{
		return false;
	}
	else{
		return true;
	}


}


bool Game::isMoveLengthValid(struct position startPosition, struct position endPosition, struct position direction)
{
int moveLengthColumn = endPosition.column - startPosition.column;
	int moveLengthRow = endPosition.row - startPosition.row;
	int moveLengthOutput = 255; //random number, damit man sehen kann ob die werte genommen werden
	bool moveLengthvalid = false; //kann man vll weglassen
	switch (moveLengthColumn)
	{

		case 0:
			switch (moveLengthRow)
			{
				case 0: moveLengthOutput = 0; moveLengthvalid = false; break;
				case 1: moveLengthOutput = 1; moveLengthvalid = true; break;
				case -1: moveLengthOutput = 1; moveLengthvalid = true; break;
				default: moveLengthOutput = 3; moveLengthvalid = false; break;
			}
		break;

		case 1:
			switch (moveLengthRow)
			{
				case 0: moveLengthOutput = 1; moveLengthvalid = true; break;
				case 1: 
					if((startPosition.column + startPosition.row)%2==0){
						moveLengthOutput = 1; 
						moveLengthvalid = true;
					}
						
					else{
						moveLengthOutput = 2; 
						moveLengthvalid = false;
					}
				break;
				case -1: 
						if((startPosition.column + startPosition.row)%2==0){
						 moveLengthOutput = 1; 
						moveLengthvalid = true;
						}
					else{
						moveLengthOutput = 2; 
						moveLengthvalid = false;
					}
				break;
				default: moveLengthOutput = 3; moveLengthvalid = false;
			}
		break;

		case -1: 
			switch (moveLengthRow)
			{
				case 0: moveLengthOutput = 1; moveLengthvalid = true;  break;
				case 1: 
					if((startPosition.column + startPosition.row)%2==0){
						moveLengthOutput = 1; 
						moveLengthvalid = true; 
						}
					else{
						moveLengthOutput = 2;
						moveLengthvalid = false;
					}
				break;
				case -1: 
						if((startPosition.column + startPosition.row)%2==0){
							moveLengthOutput = 1; 
							moveLengthvalid = true; 
						}
					else
					{
						moveLengthOutput = 2; 
						moveLengthvalid = false;
					}
				break;
				default: moveLengthOutput = 3; moveLengthvalid = false; break;
			}
		break;

		default: moveLengthOutput = 3; moveLengthvalid = false; break;
	}

	switch (moveLengthOutput)
	{
		case 0: cout << "selbes feld" << endl; return false; break;
		case 1: cout << "geht prinzipiell" << endl; break; //wäre am ende noch zu löschen
		case 2: cout << "keine diagonale" << endl; return false; break;
		case 3: cout << "zu weit" << endl; return false; break;
		default: cout << "error, keine ahnung" << endl; return false; break;
	}

	if (moveLengthvalid==true){
		direction.column= moveLengthColumn;
		direction.row= moveLengthRow;
	}
}

//TO-DO: Anna is capturing of another token possible?
void Game::checkIfCanCapture(int i, int j, Token t)
{
	struct position currentPosition = t.getPosition(); 

	struct position endPos;
	endPos.row = currentPosition.row+i;
	endPos.column = currentPosition.column+j;
	struct position neighbour;			//TODO: CHANGE ALL
	neighbour.row = endPos.row+i; //endPosition = currentPosition + North
	neighbour.column = endPos.column+j;
	
	if(!freePosition(neighbour)){ //feld oberhalb belegt
		//Token above from other team
		if(meinSpielbrett.getCell(neighbour).getToken().getTeam() != this->currentPlayer->getTeam())
		{
			t.setGrid(endPos,true);
		}
		else
		{
			t.setGrid(endPos,false);
		}
	} 
	else //Feld unbelegt
	{
		t.setGrid(endPos,false);
	}
}

void Game::updateGridToken(Token t) //bool
{
	//set grid 0
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos;
			pos.column = column;
			pos.row = row;

			t.setGrid(pos,false);
		}
		cout << endl;
	}

	int i;
	int j;

	//set grid 1 where token could capture someone
	//TO-DO: from current position
	switch(i) //rows --> 0 = W/O, +1 = S/SW/SO, -1 = N/NW/NO
	{
		case -1: //Token moves to NORTH  
			switch(j) //columns --> 0 = N, +1 = NO, -1 = NW
			{
				case -1:
					checkIfCanCapture(i, j, t);
				;

				case 0:
					checkIfCanCapture(i, j, t);
				;

				case 1:
					checkIfCanCapture(i, j, t);
				;
			};

		case +1: //Token moves to South  
			switch(j) //columns --> 0 = S, +1 = SO, -1 = SW
			{
				case -1:
					checkIfCanCapture(i, j, t);
				;

				case 0:
					checkIfCanCapture(i, j, t);
				;

				case 1:
					checkIfCanCapture(i, j, t);
				;
			};

		case 0: //Token stay in row  
			switch(j) //columns --> 1 = O, -1 = W
			{
				case -1:
					checkIfCanCapture(i, j, t);
				;

				case 1:
					checkIfCanCapture(i, j, t);
				;
			};
	}
}

//creates a grid with all cells marked where tokens are placed, that could possible capture someone
void Game::capturingPossible() //bool
{
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos;
			pos.column = column;
			pos.row = row;

			//create a grid for token --> 1 = this token can capture someone, 0 --> token cant capture or from other team
			gridCapturing[row][column] = 0;
			
			//check all tokens from currentPlayer
			if(meinSpielbrett.getCell(pos).getToken().getTeam() == this->currentPlayer->getTeam())
			{
				updateGridToken(meinSpielbrett.getCell(pos).getToken());
				//token from currentPlayer can capture someone
				if(meinSpielbrett.getCell(pos).getToken().getGridBool() == true)
				{
					gridCapturing[row][column] = 1;
				}

				//token from currentPlayer but cant capture anyone
				else
				{
					gridCapturing[row][column] = 0;	
				}
			}

			//tokens are from other team
			else
			{
				gridCapturing[row][column] = 0;
			}
		}
		cout << endl;
	}
}

struct position Game::chooseToken(void)
{
	int row, col;
	char column;

	cout << "Please choose the row: ";
	cin >> row;
	cout << "Please choose the column: ";
	cin >> column;

	col = column - 65;

	struct position position;
	position.column = col;
	position.row = row - 1;

	return position;
}

bool Game::positionInputValid(struct position position)
{
	if(position.row >= 0 && position.row <= 5 && position.column >= 0 && position.column <= 8){
 		return true;
 	} else {
		 return false;
	 }
}

//check if game is over and who is winner
void Game::gameOver(void)
{
	if(this->playerWhite.getLeftTokens() == 0 || this->playerBlack.getLeftTokens() == 0) //TO-DO: when player captures stones - subtract amount form total count
	{
		gameWon = true;
		this->winner = currentPlayer;
	}
	else
	{
		gameWon = false;
	}

}

//move Token from start to end position
void Game::moveToken (struct position startPosition, struct position endPosition)
{
	Token tokenToMove = meinSpielbrett.getCell(startPosition).getToken();
	meinSpielbrett.setTokenOnCell(endPosition, tokenToMove);
	meinSpielbrett.emptyCell(startPosition);
}


void Game::captureToken(enum Direction direction, struct position endPosition)
{
	bool neighbourFieldEmpty = false;
	int capturedTokens = 0;
	int i = 1;

	switch(direction)
	{
		case NORTH: //Token moves from NORTH - check neighbour in the SOUTH
			while (!neighbourFieldEmpty) //while neigbourField is not empty -> delete Token
			{
				struct position neighbour;
				neighbour.row = endPosition.row + i;
				neighbour.column = endPosition.column;
				cout << "row: [" << neighbour.row << "]";
				cout << "column: [" << neighbour.column << "]" << endl;

				if(!freePosition(neighbour) && neighbour.row > 4){
					meinSpielbrett.getCell(neighbour).deleteToken(); //delete Token
					capturedTokens++;
					i++;
				} else{
					neighbourFieldEmpty = true;
				}
			}
		break;

		case SOUTH: //Token moves from SOUTH - check neighbour in the NORTH
			while (!neighbourFieldEmpty) //while neigbourField is not empty -> delete Token
			{
				struct position neighbour;
				neighbour.row = endPosition.row - i;
				neighbour.column = endPosition.column;
				cout << "row: [" << neighbour.row << "]";
				cout << "column: [" << neighbour.column << "]" << endl;

				if(!freePosition(neighbour) && neighbour.row > 0){
					meinSpielbrett.getCell(neighbour).deleteToken(); //delete Token
					capturedTokens++;
					i++;
				} else{
					//cout << "free";
					neighbourFieldEmpty = true;
				}
			}
		break;

		case EAST: //Token moves fro m EAST - check neighbour in the WEST


		break;

		case WEST: 	//Token moves from WEST - check neighbour in the EAST


		break;

		case NORTHWEST: //Token moves from NORTHWEST - check neighbour in the SOUTHEAST

		break;

		case SOUTHEAST: //Token moves from SOUTHEAST - check neighbour in the NORTHWEST

		break;

		case NORTHEAST: //Token moves from NORTHEAST - check neighbour in the SOUTHWEST

		break;

		case SOUTHWEST: //Token moves from SOUTHWEST - check neighbour in the NORTHEAST

		break;
	}

	cout << "Number of deleted tokens: " << capturedTokens << endl;
}

void Game::clearScreen(void)
{
	int i = 0;
	while(i++ < LINES_TO_CLEAR)
		cout << endl;
}

