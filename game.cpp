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

	//TO-DO: Unterscheidung ob erster Move oder erneut --> nur der schon bewegte Token darf weiter
	
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

	//if can capture --> see if chose right token to right position, else cant capture anyway and any move possible
	/*if(capturingYes)
	{
		capturingRight = rightfulCapturing();
	}
	else
	{
		capturingRight = true:
	}*/
	//TODO: Anna

	// Kann dieser Zug ausgeführt werden?
	// - Ist die Position eine freie Position?
	isEndPositionFree = freePosition(endPosition);
	
	// - ist dieses feld erreichbar? (zugweite 1, felder müssen verbunden sein)
	isMoveLengthOK = isMoveLengthValid(startPosition, endPosition, direction);

	isDirectionOK = isMoveDirectionValid(startPosition, endPosition,lastPositions);

	//TO-DO: LUKAS
	//only move when all rules are true (Lukas - combination rule se) --> otherwise: chose again

	//TODO Anna: add capturingRight
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
			//test - capturingPossible
			//capturingYes = capturingPossible();
			struct position pos;
			pos.row = 3;
			pos.column = 4;
			//updateGridToken(meinSpielbrett.getCell(pos).getToken(), pos);
			checkIfCanCapture(-1, 0, meinSpielbrett.getCell(pos).getToken(), pos);

			/*for(int row=0; row<5; row++)
			{
				for(int column=0; column<9; column++)
				{
					struct position pos1;
					pos1.row = row;
					pos1.column = column;
					//cout << cells[row][column].printStatus() << flush;
					cout << meinSpielbrett.getCell(pos).getToken().getGridValue(pos1) << flush;
				}
				cout << endl;
			}*/

			lastPositions = move(lastPositions); //TODO Anna later: give as argument capturingYes
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

bool Game::rightfulCapturing(struct position startPosition, struct position endPosition)
{
	if(gridCapturing[startPosition.row][startPosition.column] == 1 && meinSpielbrett.getCell(endPosition).getToken().getGridValue(endPosition) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//TO-DO: Anna add beenThere + areFieldsConnected
//TO-DO Anna: remove tokenPosition --> DONE

void Game::checkIfCanCapture(int i, int j, Token t, struct position currentPosition)
{
	//approach
	struct position endPos;
	endPos.row = currentPosition.row+i;
	endPos.column = currentPosition.column+j;
	struct position neighbour;			//TODO: CHANGE ALL
	neighbour.row = endPos.row+i; //endPosition = currentPosition + North
	neighbour.column = endPos.column+j;

	//widthdraw
	struct position neighbour2;			//TODO: CHANGE ALL
	neighbour2.row = endPos.row-(2*i); //endPosition = currentPosition + North
	neighbour2.column = endPos.column-(2*j);

	//struct direction dir1;

	//move valid
	//TODO: add isMoveLengthValid and check if cells are connected
	if(freePosition(endPos)) //&& isMoveLengthValid(currentPosition, endPos, dir1)
	{
		cout << "move valid" << endl;
		//TODO: include beenThere --> cant capture if already been there
		//TODO: fields connected	
		if((!freePosition(neighbour) && positionInputValid(neighbour))||(!freePosition(neighbour2) && positionInputValid(neighbour2))){ //feld oberhalb belegt
			//Token above from other team
			if((meinSpielbrett.getCell(neighbour).getToken().getTeam() != this->currentPlayer->getTeam()) || (meinSpielbrett.getCell(neighbour2).getToken().getTeam() != this->currentPlayer->getTeam()))
			{
				t.setGridValue(endPos,true);
				cout << "kann schmeißen" << endl;
			}
			else
			{
				t.setGridValue(endPos,false);
				cout << "kann nicht schmeißen" << endl;
			}
		} 
		else //Feld unbelegt
		{
			if(positionInputValid(endPos))
			{
				t.setGridValue(endPos,false);
				cout << "kann nicht schmeißen - feld leer" << endl;
			}
			else
			{
				cout << "whatever" << endl;
			}
		}
	}
	else
	{
		cout << "move not valid" << endl;
	}
}

void Game::updateGridToken(Token t, struct position currentPosition) //bool
{
	//set grid 0
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos;
			pos.column = column;
			pos.row = row;

			t.setGridValue(pos,false);
		}
		cout << endl;
	}

	int i[] = { -1, 0, 1 };
	int j[] = { -1, 0, 1 };
 
   // foreach loop
   //set grid 1 where token could capture someone
   	for (int a : i) // rows = a --> 0 = W/O, +1 = S/SW/SO, -1 = N/NW/NO
	{
		for (int b : j) // columns = b 
		{
			// row = -1, columns --> 0 = N, +1 = NO, -1 = NW 
			// row = +1, columns --> 0 = S, +1 = SO, -1 = SW
			// row = 0,  columns --> 1 = O, -1 = W

			if(!(a==0 && b==0))
			{
				checkIfCanCapture(a, b, t, currentPosition);
			}
		}
	}

	//TODO: change i/j so that switch works! --> no iteration until now! --> for each??
		// --> DONE

	//TO-DO: from current position
}

//creates a grid with all cells marked where tokens are placed, that could possible capture someone
bool Game::capturingPossible() 
{
	bool var = false;
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
				updateGridToken(meinSpielbrett.getCell(pos).getToken(),pos);
				//token from currentPlayer can capture someone
				if(meinSpielbrett.getCell(pos).getToken().getGridBool() == true)
				{
					gridCapturing[row][column] = 1;
					var = true;
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
	return var;
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

/*	struct Useraction test;
	test.dir = South;
	test.end.row = 2;
	test.end.column= 4;
	test.start.row = 3;
	test.start.column= 4;
	test.command = Move;

	captureToken(test);*/
}

struct position Game::getNeighbour(struct position position, Direction direction){
	struct position neighbour;

	switch(direction){
		case North:
			neighbour.row = position.row - 1;
			neighbour.column = position.column;
		break;

		case South:
			neighbour.row = position.row + 1;
			neighbour.column = position.column;
		break;

		case East:
			neighbour.row = position.row;
			neighbour.column = position.column + 1;
		break;

		case West:
			neighbour.row = position.row;
			neighbour.column = position.column - 1;
		break;

		case Northwest:
			neighbour.row = position.row - 1;
			neighbour.column = position.column - 1;
		break;

		case Southeast:
			neighbour.row = position.row + 1;
			neighbour.column = position.column + 1;
		break;

		case Northeast:
			neighbour.row = position.row - 1;
			neighbour.column = position.column + 1;
		break;
		
		case Southwest:
			neighbour.row = position.row + 1;
			neighbour.column = position.column - 1;
		break;
	}

	return neighbour;
}

void Game::capture(struct position startNeighbour, Direction startNeighbourDir, struct position endNeighbour, Direction endNeighbourDir){

    bool neighbourFieldEmpty = false;
    int capturedTokens = 0;
    bool withdraw = false;
    bool approach = false;
    string choice;

            //If neighbour of Startposition is not free and is Token from other Team && neighbour from endPosition is not free and is Token from other Team
            if(!freePosition(startNeighbour) && !isTokenFromCurrentTeam(startNeighbour) && !freePosition(endNeighbour) && !isTokenFromCurrentTeam(endNeighbour)){
                cout << "Please choose withdraw or approach";
                cin >> choice;

                

                if(choice.compare("withdraw") == 0){
                    withdraw = true;
                } else if(choice.compare("approach") == 0){
                    approach = true;
                }
            }
            //Only Neighbour of endPosition is Token from other Team
            else if(((freePosition(startNeighbour) || isTokenFromCurrentTeam(startNeighbour)) && !freePosition(endNeighbour) && !isTokenFromCurrentTeam(endNeighbour) && endNeighbour.row < 9)){ //Nachbar in Endposition schmeißen
                while(!neighbourFieldEmpty){
                    if(!freePosition(endNeighbour) && !isTokenFromCurrentTeam(endNeighbour)
                        && endNeighbour.row < 9 && endNeighbour.column > 0
                        && endNeighbour.column < 5 && endNeighbour.column > 0){
                        //Capture
                        meinSpielbrett.emptyCell(endNeighbour);
                        endNeighbour = getNeighbour(endNeighbour, endNeighbourDir);
                        capturedTokens++;
                    } else{
                        neighbourFieldEmpty = true;
                    }
                }
            } 
            //Only Neighbour of startPosition is Token from other Team
            else if((!freePosition(startNeighbour) && !isTokenFromCurrentTeam(startNeighbour) && (freePosition(endNeighbour) || isTokenFromCurrentTeam(endNeighbour)) && startNeighbour.row > 0)){ //Nachbar in Startposition schmeißen
                while(!neighbourFieldEmpty){
                    if(!freePosition(startNeighbour) &&  !isTokenFromCurrentTeam(startNeighbour) 
                       && startNeighbour.row < 9 && startNeighbour.row > 0 
                       && startNeighbour.row < 5 && startNeighbour.column > 0 ){
                        //Capture
                        meinSpielbrett.emptyCell(startNeighbour);
                        startNeighbour = getNeighbour(startNeighbour, startNeighbourDir);
                        capturedTokens++;
                    } else{
                        neighbourFieldEmpty = true;
                    }
                }
            }
        cout << "Number of deleted tokens: " << capturedTokens << endl;
}


void Game::captureToken(struct Useraction userAction)
{
    switch(userAction.dir)
    {
        case North: { //Token moves to North - check neighbour in the North
            struct position startNeighbour = getNeighbour(userAction.start, North);
            struct position endNeighbour = getNeighbour(userAction.end, South);

            capture(startNeighbour, North, endNeighbour, South);
        }

        case South: { //Token moves to South 
            struct position startNeighbour = getNeighbour(userAction.start, South);
            struct position endNeighbour = getNeighbour(userAction.end, North);

            capture(startNeighbour, South, endNeighbour, North);
        break;
        }
        case East:{ //Token moves to East - check neighbour in the East
            struct position startNeighbour = getNeighbour(userAction.start, East);
            struct position endNeighbour = getNeighbour(userAction.end, West);

            capture(startNeighbour, East, endNeighbour, West);

        break;
        }
        case West: {    //Token moves to West - check neighbour in the West
            struct position startNeighbour = getNeighbour(userAction.start, West);
            struct position endNeighbour = getNeighbour(userAction.end, East);

            capture(startNeighbour, West, endNeighbour, East);
        break;
        }
        case Northwest: { //Token moves to Northwest - check neighbour in the Northwest
            struct position startNeighbour = getNeighbour(userAction.start, Northwest);
            struct position endNeighbour = getNeighbour(userAction.end, Southeast);

            capture(startNeighbour, Northwest, endNeighbour, Southeast);
        break;
        }
        case Southeast: { //Token moves to Southeast - check neighbour in the Southeast
            struct position startNeighbour = getNeighbour(userAction.start, Southeast);
            struct position endNeighbour = getNeighbour(userAction.end, Northwest);

            capture(startNeighbour, Southeast, endNeighbour, Northwest);
        break;
        }
        case Northeast: {//Token moves to Northeast - check neighbour in the Northeast
            struct position startNeighbour = getNeighbour(userAction.start, Northeast);
            struct position endNeighbour = getNeighbour(userAction.end, Southwest);

            capture(startNeighbour, Northeast, endNeighbour, Southwest);
        break;
        }
        case Southwest:{//Token moves to Southwest - check neighbour in the Southwest
            struct position startNeighbour = getNeighbour(userAction.start, Southwest);
            struct position endNeighbour = getNeighbour(userAction.end, Northeast);

            capture(startNeighbour, Southwest, endNeighbour, Northeast);
        break;
        }
    }
}


void Game::clearScreen(void)
{
	int i = 0;
	while(i++ < LINES_TO_CLEAR)
		cout << endl;
}

