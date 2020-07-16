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

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "game.h"
#include<cmath>

using namespace std;

Game::Game(void)
{
	this->currentPlayer = &playerWhite;
	this->gameWon = false;
	this->gameDraw = false;
	this->restart = false;
	this->quit = false;
	this->playerWhite.setTeam(WHITE);
	this->playerBlack.setTeam(BLACK);

	meinSpielbrett.init();
	meinSpielbrett.updateLeftTokens();
}

bool Game::start() // TODO: private??
{
Tree testTree;
    testTree.root.setIsMax(true);
    testTree.root.setCost(std::numeric_limits<float>::min());

    Node min2x1;
    min2x1.setIsMax(false);
    min2x1.setCost(std::numeric_limits<float>::max());
    testTree.root.addChild(&min2x1);

        Node max3x1;
        max3x1.setIsMax(true);
        max3x1.setCost(std::numeric_limits<float>::min());
        min2x1.addChild(&max3x1);

            Node min4x1;
            min4x1.setIsMax(false);
            min4x1.setCost(4);
            max3x1.addChild(&min4x1);

            Node min4x2;
            min4x2.setIsMax(false);
            min4x2.setCost(8);
            max3x1.addChild(&min4x2);

        Node  max3x2;
        max3x2.setIsMax(true);
        max3x2.setCost(std::numeric_limits<float>::min());
        min2x1.addChild(&max3x2);

            Node  min4x3;
            min4x3.setIsMax(false);
            min4x3.setCost(9);
            max3x2.addChild(&min4x3);

            Node min4x4;
            min4x4.setIsMax(false);
            min4x4.setCost(3);
            max3x2.addChild(&min4x4);

    Node min2x2;
    min2x2.setIsMax(false);
    min2x2.setCost(std::numeric_limits<float>::max());
    testTree.root.addChild(&min2x2);

        Node max3x3;
        max3x3.setIsMax(true);
        max3x3.setCost(std::numeric_limits<float>::min());
        min2x2.addChild(&max3x3);

            Node min4x5;
            min4x5.setIsMax(false);
            min4x5.setCost(2);
            max3x3.addChild(&min4x5);

            Node min4x6;
            min4x6.setIsMax(false);
            min4x6.setCost(-2);
            max3x3.addChild(&min4x6);
        
        Node max3x4;
        max3x4.setIsMax(true);
        max3x4.setCost(std::numeric_limits<float>::min());
        min2x2.addChild(&max3x4);

            Node min4x7;
            min4x7.setIsMax(false);
            min4x7.setCost(-1);
            max3x4.addChild(&min4x7);

            Node min4x8;
            min4x8.setIsMax(false);
            min4x8.setCost(9);
            max3x3.addChild(&min4x8);


    //printNodeScore(&(testTree.root), 2);


	Node * bestNode;
	if(alphaBeta){
		Node empty;
		empty.setIsMax(true);
		empty.setCost(2);
		bestNode = compareChildrenAlphaBeta(&(testTree.root), &empty); //evaluate tree and find best option
	} else {
		bestNode = compareChildren(&(testTree.root)); //evaluate tree and find best option
	}

	cout << bestNode->getCost() << endl;
	cout << bestNode->getAlpha() << endl;
	cout << bestNode->getBeta() << endl;


	bool anotherGame = false;
	// clear screen
	//this->clearScreen();
	
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
		cout << "Please enter the name for the WHITE player. If it's an AI please type in 'AI': " << flush;
		getline(cin, playerName);
	}
	while( playerName.empty() );
	this->playerWhite.setName(playerName);

	if(playerName.compare("AI") == 0){
		this->playerWhite.setIsHuman(false);
	} else {
		this->playerWhite.setIsHuman(true);
	}

	cout << "Hello " << this->playerWhite.getName() <<". " << flush;
	cout << "You're on the WHITE team, your tokens look like this: " << Token::asChar(WHITE) << "\n" << endl;
	
	// create Player for team BLACK
	do
	{
		cout << "Please enter the name for the BLACK player. If it's an AI please type in 'AI': " << flush;
		getline(cin, playerName);
	}
	while( playerName.empty() );
	this->playerBlack.setName(playerName);

	if(playerName.compare("AI") == 0){
		this->playerBlack.setIsHuman(false);
	} else {
		this->playerBlack.setIsHuman(true);
	}
	cout << "Hello " << this->playerBlack.getName() <<". " << flush;
	cout << "You're on the BLACK team, your tokens look like this: " << Token::asChar(BLACK) << "\n" << endl;
	
	cout << "Team WHITE (hence "<< this->playerWhite.getName() << "-" << Token::asChar(WHITE) <<") will begin." << endl; // TODO manage inconsistencies with constructor
	cout << "Press <ENTER> to start the game." << flush;
	getline(cin,playerName);
  
	while(!gameWon && !quit && !restart && !gameDraw)
	{
		//anotherMove = true; //(re)move later
		turn();
		gameOver();

		if(this->counterCapture >= 10){
			gameDraw = true;
		}

		//change current player
		if(currentPlayer->getTeam() == WHITE)
		{
			currentPlayer = &playerBlack;
		}
		else
		{
			currentPlayer = &playerWhite;
		}
		lastDirection = InvalidDirection;
	}
	if(gameWon)
	{
		this->clearScreen();
		this->meinSpielbrett.print();
		cout << endl;
		cout << "The game is over. Player [" << Token::asChar( this->winner->getTeam() ) << "] " << this->winner->getName() <<", you won. Congratulations!" << endl;
		//cout << "Would you like to play again?"<<endl;
		anotherGame = false;
	}
	else if(gameDraw)
	{
		this->clearScreen();
		this->meinSpielbrett.print();
		cout << endl;
		cout << "The game is over. There has been a draw!" << endl;
		//cout << "Would you like to play again?"<<endl;
		anotherGame = false;
	}
	else if(restart)
	{
		cout<<"You have ended a game and started a new one."<<endl;
		anotherGame = true;
	}
	else if(quit)
	{
		cout<<"You have ended the game."<<endl;
		anotherGame = false;
	}
	else
	{
		anotherGame = false;
	}
	return anotherGame;
}

	
// ZUG
void Game::move() //struct Useraction lastPositions
{
	// clear screen
	/*struct position startPosition;
	struct position endPosition;
	enum Direction dir;*/
	struct Useraction useraction;  // TODO: maybe wanna declare somewhere else?
	bool validAction = false;
	skip = false;

	do
	{
		do
		{
			if(currentPlayer->getIsHuman())
			{
				useraction = getHumanUseraction();
			} else 
			{
				useraction = getAIUseraction();
			}
		
		}
		while(useraction.command == Invalid);
		
	
		
		switch(useraction.command)
		{
			//case Invalid: break;
			case Skip:
				{
					if(counterMoves == 1)
					{
						errorvec.push_back("You can't skip this move, since it's the first one in your turn.");
						validAction = false;
						skip = false;
					}
					else
					{
						validAction = true;
						skip = true;
					}

				}; break;

			case Move:
				{
					/*cout << "Start Col: " << useraction.start.column << endl;
					cout << "Start Row: " << useraction.start.row << endl;
					cout << "End Col: " << useraction.end.column << endl;
					cout << "End Row: " << useraction.end.row << endl;
					cout << "Dir: " << useraction.dir << endl;
					cout << currentPlayer->getName();*/

					if(isMoveValid(useraction.start, useraction.end, useraction.dir)) //enum Command command
					{
						//update grid for beenThere
						if(counterMoves == 1) 
						{
							grid[useraction.start.row][useraction.start.column] = 1;
						}
						if(grid[useraction.end.row][useraction.end.column] == 0)
						{
							grid[useraction.end.row][useraction.end.column] = 1;
						}

						int capturedTokens = moveToken(useraction);

							if(capturedTokens == 0){
								this->counterCapture++;
							} else{
								this->counterCapture = 0;
							}

						lastDirection = useraction.dir;
						currentPosition = useraction.end;
						counterMoves++; 

						validAction = true; //true
					}
					else
					{
						validAction = false;
					}

				}; break;

			case Help: 
				{
					ifstream helpScreenFile;
					helpScreenFile.open("Help.txt");
					if(helpScreenFile)
					{
						string line;
						while( getline(helpScreenFile, line) )
							cout << line << endl;
					}
					else
					{
						cout << "Make your next move!" << endl;
					}
					cout<<"Press enter to continue."<<endl;
					getchar();
					validAction = false;
				}; break;

			case Restart:
				{
					restart = true;
					validAction = true;
				}; break;

			case Quit:
				{
					quit = true;
					validAction = true;
				}; break;

			case Rules:
				{
					ifstream rulesScreenFile;
					rulesScreenFile.open("Rules_Fanorona.txt");
					if(rulesScreenFile)
					{
						string line;
						while( getline(rulesScreenFile, line) )
							cout << line << endl;
					}
					else
					{
						cout << "Make your next move!" << endl;
					}
					cout<<"Press enter to continue."<<endl;
					getchar();
					validAction = false;
				}; break;
			// default: break;
		}

	/*if(!validAction){
		return;
	}*/

	//TO-DO: LUKAS
	//only move when all rules are true (Lukas - combination rule se) --> otherwise: chose again
	
	//while validAction == false
	//}while(!isMoveValid(useraction.start, useraction.end, useraction.dir, useraction.command)); //, lastPositions
	}while(!validAction);
		
	/*	
	//update grid for beenThere
	if(counterMoves == 1) 
	{
		grid[useraction.start.row][useraction.start.column] = 1;
	}
	if(grid[useraction.end.row][useraction.end.column] == 0)
	{
		grid[useraction.end.row][useraction.end.column] = 1;
	}

	moveToken(useraction);
	
	//lastPositions.start = useraction.start;
	//lastPositions.dir = useraction.dir;
	lastDirection = useraction.dir;
	currentPosition = useraction.end;

	counterMoves++; */

	//return lastPositions;
}

bool Game::isMoveValid(struct position startPosition, struct position endPosition, enum Direction direction){ //, struct Useraction lastaction, , enum Command command
	// Ist auf dieser Position ein Token von dem Team?

	bool returnvalue = true;
	//std::vector<string> errorvec;
	//int errorcounter= -1;
	//input needs to be valid before checking other rules
	if(positionInputValid(startPosition) || positionInputValid(endPosition))
	{
		if(!isTokenFromCurrentTeam(startPosition)){
			returnvalue = false;
			//cout << "Token is not from current team" << endl;
			errorvec.push_back("Token is not from current team");
			//errorcounter++;
		}

		// cout << "Choose endposition:" << endl;
		// endPosition = chooseToken();
		// 	cout << "\tEndposition COL: " << endPosition.column << endl;
		// 	cout << "\tEndposition ROW: " << endPosition.row << endl;

		//war in diesem Zug schon mal auf diesem spielfeld?
		if(!beenThere(endPosition))
		{
			returnvalue = false;
			//cout << "you have already been to this field in your turn" << endl;
			errorvec.push_back("you have already been to this field in your turn");
			//errorcounter++;
		}
		
		//if can capture --> see if chose right token to right position, else cant capture anyway and any (valid) move possible
		if(capturingYes)
		{
			if(!rightfulCapturing(startPosition, endPosition))
			{
				returnvalue = false;
				//cout << "you are able to capture someone and therefore have to" << endl;
				errorvec.push_back("you are able to capture someone and therefore have to");
				//errorcounter++;
				
			}
		}

		// Kann dieser Zug ausgeführt werden?
		// - Ist die Position eine freie Position?
		if(!freePosition(endPosition))
		{
			returnvalue = false;
			//cout << "this position is taken by another token" << endl;
			errorvec.push_back("this position is taken by another token");
			//errorcounter++;
		}
		
		// - ist dieses feld erreichbar? (felder müssen verbunden sein)
		if(!areFieldsConnected(startPosition, direction)) {
									cout << "connected";

			returnvalue = false;
			//cout << "fields are not connected" << endl;
			errorvec.push_back("fields are not connected");
			//errorcounter++;
		}

		if (!isMoveDirectionValid(direction)){
									cout << "dir valid";

			returnvalue = false;
			//cout << "your last move was in this direction" << endl;
			errorvec.push_back("your last move was in this direction");
			//errorcounter++;
		}
		
		//second++ moves in one turn: has to move with same token as before
		if (!sameTokenSelected(startPosition))
		{
			cout << "not same T";

			returnvalue = false;
			//cout << "you have to select the same token as in your previous moves" << endl;
			errorvec.push_back("you have to select the same token as in your previous moves");
			//errorcounter++;
		}

		/*if(!cantSkipFirstMove(command))
		{
			returnvalue = false;
			errorvec.push_back("you can't skip the first move");
		}*/

	}
	else
	{
		if(!positionInputValid(startPosition)) 
		{
			returnvalue = false;
			//cout << "startposition input invalid" << endl;
			errorvec.push_back("startposition input invalid");
			//errorcounter++;
		}
		if (!positionInputValid(endPosition))
		{ 
			returnvalue = false;
			//cout << "endpositioninput invalid" << endl;
			errorvec.push_back("endposition input invalid");
			//errorcounter++;
		}
	}

	return returnvalue;
}

// RUNDE
void Game::turn(void)
{
 	//clear grid for check "beenThere"
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			grid[row][column] = 0;
		}
		//cout << endl;
	}

	counterMoves = 1; //set: first move of current player
	anotherMove = true;

	//check if currentPlayer could capture anyone (true = yes)
	capturingYes = capturingPossible(); 

	//test
	/*for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos1;
			pos1.row = row;
			pos1.column = column;
			cout << gridCapturing.gridPosition[pos1.row][pos1.column]<< flush;
		}
		cout << endl;
	}*/

	//loop until cant/dont want to move and capture anymore
	do
	{
			//std::vector<Useraction> test = getPossibleMoves();
			//cout<<counterPossibleMoves<<endl;

			move();
			//TODO: struct Groß- und Kleinschreibung vereinheitlichen Useraction, position
			//is another move/capturing with latest token possible?
			if(!restart && !quit)
			{
				if(capturingAgain() && capturingYes && !skip) 
				{
					anotherMove = true;
				} 
				else
				{
					anotherMove = false;
				}
			}
			else
			{
				anotherMove = false;
			}
	}
	while(anotherMove); //maybe insert capturingAgain here?
	
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

//make sure token doenst enter cell twice in a turn
bool Game::beenThere(struct position endPosition) 
{
	if(grid[endPosition.row][endPosition.column] == 0)
	{
		return true;
	}
	else
	{
		return false; //been there already
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

bool Game::isMoveDirectionValid(enum Direction direction)
{
	if(counterMoves > 1)
	{
		if (lastDirection == direction)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else{
		return true;
	}
}

bool Game::areFieldsConnected(struct position startPosition, int direction)
{
	if (direction == Southeast || direction == Southwest || direction == Northeast || direction == Northwest)
	{
		if ((startPosition.column + startPosition.row)%2==0){
				return true;
		}
		else
		{
			return false;
		}
		
	}
	else 
	{
		return true;
	}

}

//second++ moves: is same token selected?
bool Game::sameTokenSelected(struct position startPosition)
{
	bool value;
	if(counterMoves>1)
	{
		//why cant compare positions?
		if(startPosition.row == currentPosition.row && startPosition.column == currentPosition.column) 
		{
			value = true;
		}
		else
		{
			value = false;
		}
	}
	else
	{
		value = true;
	}
	return value;
}

/*bool Game::cantSkipFirstMove(enum Command skip)
{
	if(counterMoves == 1 && skip == Skip)
	{
		return false;
	}
	else
	{
		return true;
	}
}*/

int Game::calculateDirection (struct position start, struct position end)
{
	//  0	  1		 2		3		4		  5			 6			7
	//North, East, South, West, Northeast, Southeast, Southwest, Northwest
	int row = end.row - start.row;
	int column = end.column - start.column;
	int direction = 0; //Attention: return North if same positions are entered

	switch(row) //rows --> 0 = W/O, +1 = S/SW/SO, -1 = N/NW/NO
	{
   		case -1: //Token moves to North  
			switch(column) //columns --> 0 = N, +1 = NO, -1 = NW
			{
				case -1:
					direction = 7;
				; break;

				case 0:
					direction = 0;
				; break;

				case 1:
					direction = 4;
				; break;
			} break;

		case +1: //Token moves to South  
			switch(column) //columns --> 0 = S, +1 = SO, -1 = SW
			{
				case -1:
					direction = 6;
				; break;

				case 0:
					direction = 2;
				; break;

				case 1:
					direction = 5;
				; break;
			} break;

		case 0: //Token stays in row 
			switch(column) //columns --> 1 = O, -1 = W
			{
				case -1:
					direction = 3;
				; break;

				case 1:
					direction = 1;
				; break;

				case 0: //attention: stays - shouldnt give direcction
					direction = 0; //now: north
				; break;
			} break;
		//TODO?: need to return smtgh when 0-0 --> if yes: what?
	}
	return direction;
}

bool Game::rightfulCapturing(struct position startPosition, struct position endPosition)
{
	bool value = false;
	//struct Grid gridTemp;
	//gridTemp = meinSpielbrett.getCell(startPosition).getToken().getFieldOfView();
	if(counterMoves == 1)
	{
		if(gridCapturing.gridPosition[startPosition.row][startPosition.column].capture == 1 && meinSpielbrett.getCell(startPosition).getToken().getFieldOfView().gridPosition[endPosition.row][endPosition.column].capture == 1)
		{
			value = true;
		}
		else
		{
			value = false;
		}
	}
	else
	{
		if(meinSpielbrett.getCell(startPosition).getToken().getFieldOfView().gridPosition[endPosition.row][endPosition.column].capture == 1)
		{
			value = true;
		}
		else
		{
			value = false;
		}
	}
	return value; 
}

//checks if a token moved in a certain direction can capture someone
CheckcaptureAW Game::checkIfCanCapture(int i, int j, struct position currentPos)
{
	bool approach = false;
	bool widthdraw = false;
	bool returnValue = false;
	//approach
	struct position endPos;
	endPos.row = currentPos.row+i;
	endPos.column = currentPos.column+j;
	struct position neighbour;			
	neighbour.row = endPos.row+i; 
	neighbour.column = endPos.column+j;

	//widthdraw
	struct position neighbour2;			
	neighbour2.row = currentPos.row-i; 
	neighbour2.column = currentPos.column-j;

	int direction = calculateDirection(currentPos, endPos);

	if(positionInputValid(endPos)) // endPosition exists
	{
		//move valid
		if(freePosition(endPos) && areFieldsConnected(currentPos, direction))
		{
			//approach
			// the neigboring cell (of endPos - APPROACH) is filled with a token
			if(positionInputValid(neighbour))
			{
				if(!freePosition(neighbour))
				{ 
					if(meinSpielbrett.getCell(neighbour).getToken().getTeam() != this->currentPlayer->getTeam() && meinSpielbrett.getCell(neighbour).getOccupied() == true) 
					{
						approach = true; // captruing possible
					}
					else
					{
						approach = false; // neighboring token from my own team
					}
				} 
				else //empty cell - no token to capture
				{
					returnValue = false;
				}
			}
			else //neighbor does not exist
			{
				returnValue = false;
			}

			//widthdraw
			// the neigboring cell2 (of startPos - WIDTHDRAW) is filled with a token
			if(positionInputValid(neighbour2))
			{
				if(!freePosition(neighbour2))
				{ 
					if(meinSpielbrett.getCell(neighbour2).getToken().getTeam() != this->currentPlayer->getTeam() && meinSpielbrett.getCell(neighbour2).getOccupied() == true)
					{
						widthdraw = true; // captruing possible
					}
					else
					{
						widthdraw = false; // neighboring token from my own team
					}
				} 
				else //empty cell - no token to capture
				{
					returnValue = false;
				}
			}
			else //neighbor2 does not exist
			{
				returnValue = false;
			}
		}
		else //move not valid
		{
			returnValue = false;
		}
	}
	else //can't move there because cell doesn't exist
	{
		returnValue = false;
	}

	if(approach == true || widthdraw == true)
	{
		returnValue = true;
	}

	CheckcaptureAW returnStruct;
	returnStruct.capture = returnValue;
	returnStruct.approach = approach;

	return returnStruct;
}

struct Grid Game::updateGridToken(struct position currentPos) 
{
	struct Grid temporaryGrid;
	//set grid 0
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos;
			pos.column = column;
			pos.row = row;

			temporaryGrid.gridPosition[pos.row][pos.column].capture = false;
		}
		//cout << endl;
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
				CheckcaptureAW valueTemp;
				valueTemp = checkIfCanCapture(a, b, currentPos); 
				struct position endPos;
				endPos.row = currentPos.row+a;
				endPos.column = currentPos.column+b;
				if(positionInputValid(endPos))
				{
					temporaryGrid.gridPosition[endPos.row][endPos.column] = valueTemp;
				}

				//test
				/*for(int row=0; row<5; row++)
				{
					for(int column=0; column<9; column++)
					{
						struct position pos1;
						pos1.row = row;
						pos1.column = column;
						cout << temporaryGrid.gridPosition[pos1.row][pos1.column]<< flush;
					}
					cout << endl;
				}
				cout<<endl;
				cout<<a<<endl;
				cout<<b<<endl;*/
			} //if doenst work again - add else here
		}
	}
	return temporaryGrid;
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
			gridCapturing.gridPosition[row][column].capture = false;
			
			//check all tokens from currentPlayer
			if(meinSpielbrett.getCell(pos).getToken().getTeam() == this->currentPlayer->getTeam() && meinSpielbrett.getCell(pos).getOccupied() == true)
			{
				//TODO: cells with token captured = still have token on them...
				setFieldOfView(pos, updateGridToken(pos));
				/*cout<<pos.row<<endl;
				cout<<pos.column<<endl;*/
				
				//token from currentPlayer can capture someone
				if(meinSpielbrett.getCell(pos).getToken().getGridBool() == true) // boolTemp
				{
					gridCapturing.gridPosition[row][column].capture = true;
					var = true;
				}

				//token from currentPlayer but cant capture anyone
				else
				{
					gridCapturing.gridPosition[row][column].capture = false;	
				}
			}

			//tokens are from other team
			else
			{
				gridCapturing.gridPosition[row][column].capture = false;
			}
		}
	}

	return var;
}

//is another move/capturing with latest token possible?, update tokenGrid for currentToken
bool Game::capturingAgain()
{

	bool var = false;	
	struct Grid temporaryGrid;
	temporaryGrid = updateGridToken(currentPosition);
	//test
	/*for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos1;
			pos1.row = row;
			pos1.column = column;
			cout << temporaryGrid.gridPosition[pos1.row][pos1.column]<< flush;
		}
		cout << endl;
	}*/
	
	//sameDirection --> not allowed
	struct position sameDirectionPosition;
	sameDirectionPosition = getNeighbour(currentPosition, lastDirection);

	if(positionInputValid(sameDirectionPosition)){
		temporaryGrid.gridPosition[sameDirectionPosition.row][sameDirectionPosition.column].capture = 0;
	}


	//remove positions where cant go (beenThere, sameDirection)
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			if(grid[row][column]==1)
			{
				temporaryGrid.gridPosition[row][column].capture = 0;
			}
		}
	}


	setFieldOfView(currentPosition, temporaryGrid);

	//test
	/*for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			struct position pos1;
			pos1.row = row;
			pos1.column = column;
			cout << temporaryGrid.gridPosition[pos1.row][pos1.column]<< flush;
		}
		cout << endl;
	}*/
	
	if(meinSpielbrett.getCell(currentPosition).getToken().getGridBool() == true) 
	{
		var = true;
	}

	return var;
}

//TODO: can again capture --> need different rightfulCapturing

/*struct position Game::chooseToken(void) // TODO abolish
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
}*/

std::vector<Useraction> Game::getPossibleMoves()
{
	struct Useraction possibleUseraction;
	int index = 0;
	int count = 0;
	std::vector<Useraction> listofMoves;
	

	if(counterMoves == 1)
	{
		//cout << currentPlayer->getName();

		if(capturingYes) //if can capture someone get position from gridCapturing and tokenGrid
		{
			for(int row=0; row<5; row++)
			{
				for(int column=0; column<9; column++)
				{
					struct position startPosition;
					startPosition.row = row;
					startPosition.column = column;
					if(gridCapturing.gridPosition[startPosition.row][startPosition.column].capture == 1)
					{
						for(int row1=0; row1<5; row1++)
						{
							for(int column1=0; column1<9; column1++)
							{
								struct position endPosition;
								endPosition.row = row1;
								endPosition.column = column1;
								if(meinSpielbrett.getCell(startPosition).getToken().getFieldOfView().gridPosition[endPosition.row][endPosition.column].capture == 1)
								{
									possibleUseraction.command = Move;
									possibleUseraction.captureOption = Approach;
									possibleUseraction.start = startPosition;
									possibleUseraction.end = endPosition;
									int direction = calculateDirection(startPosition, endPosition);
									possibleUseraction.dir = getDirectionFromInteger(direction);
								//	possibleMoves[index] = possibleUseraction;
									index++;
									count++;
									listofMoves.push_back(possibleUseraction);
								}
							}
						}	
					}
				}
			}

		}
		else //cant capture anyone - any valid move possible
		{
			for(int row=0; row<5; row++)
			{
				for(int column=0; column<9; column++)
				{
					struct position startPosition;
					startPosition.row = row;
					startPosition.column = column;

					//only token from current Player
					if(meinSpielbrett.getCell(startPosition).getToken().getTeam() == this->currentPlayer->getTeam() && meinSpielbrett.getCell(startPosition).getOccupied() == true)
					{
						int i[] = { -1, 0, 1 };
						int j[] = { -1, 0, 1 };
		
						for (int a : i) // rows = a --> 0 = W/O, +1 = S/SW/SO, -1 = N/NW/NO
						{
							for (int b : j) // columns = b 
							{
								// row = -1, columns --> 0 = N, +1 = NO, -1 = NW 
								// row = +1, columns --> 0 = S, +1 = SO, -1 = SW
								// row = 0,  columns --> 1 = O, -1 = W

								if(!(a==0 && b==0))
								{
									//check if move in that direction is valid --> then add currentUseraction
									struct position endPosition;
									endPosition.row = startPosition.row+a;
									endPosition.column = startPosition.column+b;
									int direction = calculateDirection(startPosition, endPosition);
									if(positionInputValid(endPosition)) //always check inputValid before checking anything else
									{
										if(freePosition(endPosition) && areFieldsConnected(startPosition, direction))
										{
											possibleUseraction.command = Move;
											possibleUseraction.start = startPosition;
											possibleUseraction.end = endPosition;
											possibleUseraction.captureOption = Unset;
											possibleUseraction.dir = getDirectionFromInteger(direction);
										//	possibleMoves[index] = possibleUseraction;
											index++;
											count++;
											listofMoves.push_back(possibleUseraction);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else //second+ move --> only checked again when can capture
	{
		struct Grid temporaryGrid;
		temporaryGrid = meinSpielbrett.getCell(currentPosition).getToken().getFieldOfView();

		for(int row=0; row<5; row++)
		{
			for(int column=0; column<9; column++)
			{
				struct position endPosition;
				endPosition.row = row;
				endPosition.column = column;

				if(temporaryGrid.gridPosition[endPosition.row][endPosition.column].capture == 1) 
				{
					possibleUseraction.command = Move;
					possibleUseraction.start = currentPosition;
					possibleUseraction.end = endPosition;

					if(temporaryGrid.gridPosition[endPosition.row][endPosition.column].approach){
						possibleUseraction.captureOption = Approach;
					} else{
						possibleUseraction.captureOption = Withdraw;
					}

					int direction = calculateDirection(currentPosition, endPosition);
					possibleUseraction.dir = getDirectionFromInteger(direction);
					//possibleMoves[index] = possibleUseraction;
					index++;
					count++;
					listofMoves.push_back(possibleUseraction);

				}
			}
		}
	}
	counterPossibleMoves = count;
	return listofMoves;
}

bool Game::positionInputValid(struct position position)
{
	if(position.row >= 0 && position.row <= 4 && position.column >= 0 && position.column <= 8){
 		return true;
 	} else 
	{
		return false;
	}
}

//check if game is over and who is winner
void Game::gameOver(void)
{

	if(meinSpielbrett.getLeftTokensBlack() == 0 || meinSpielbrett.getLeftTokensWhite() == 0 ){
		gameWon = true;
		this->winner = currentPlayer;
	}
	else
	{
		gameWon = false;
	}

}

//move Token from start to end position
int Game::moveToken (struct Useraction useraction)
{
	//Token tokenToMove = meinSpielbrett.getCell(useraction.start).getToken();
	meinSpielbrett.setTokenOnCell(useraction.end, meinSpielbrett.getCell(useraction.start).getToken()); //tokenToMove
	meinSpielbrett.emptyCell(useraction.start);
	int capturedTokens = captureToken(useraction);

	return capturedTokens;
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

		case InvalidDirection:
		break;
	}

	return neighbour;
}

int Game::capture(struct Useraction useraction, struct position startNeighbour, Direction startNeighbourDir, struct position endNeighbour, Direction endNeighbourDir, string mode){

	bool neighbourFieldEmpty = false;
    int capturedTokens = 0;
    string choice;
	bool startNeighbourValid = false;
	bool endNeighbourValid = false;

	if(positionInputValid(startNeighbour) && positionInputValid(endNeighbour))
	{
		//At start AND endPosition is Token from other Team
		if(!freePosition(startNeighbour) && !isTokenFromCurrentTeam(startNeighbour) && !freePosition(endNeighbour) && !isTokenFromCurrentTeam(endNeighbour) && useraction.captureOption == Unset){
			while(choice.compare("W") != 0 && choice.compare("A") != 0 ){
				cout << "Capturing not explicit: Please choose if you want to withdraw ('W') or approach ('A'):";
				cin >> choice;
				
				if(choice.compare("W") == 0){
					useraction.captureOption = Withdraw;
				} else if(choice.compare("A") == 0){
					useraction.captureOption = Approach;
				}
			}
		}
	}	

	if(positionInputValid(startNeighbour))
	{
		if(freePosition(startNeighbour) || isTokenFromCurrentTeam(startNeighbour))
		{
			startNeighbourValid = true;
		}
		else
		{
			startNeighbourValid = false;
		}
	}
	else
	{
		startNeighbourValid = true;
	}


	//Only Neighbour of endPosition is Token from other Team
	if(positionInputValid(endNeighbour))
	{
		//TODO: shouldnt be able to check anything if cell doesnt exist
		if((startNeighbourValid == true && !freePosition(endNeighbour) && !isTokenFromCurrentTeam(endNeighbour)) || useraction.captureOption == Approach )
		{
			while(!neighbourFieldEmpty){
				if(positionInputValid(endNeighbour)) //need to check again because new endNeighbour
				{
					if(!freePosition(endNeighbour) && !isTokenFromCurrentTeam(endNeighbour)){
						//Capture
						if(mode.compare("capture") == 0){
							meinSpielbrett.emptyCell(endNeighbour);
						}
						endNeighbour = getNeighbour(endNeighbour, endNeighbourDir);
						capturedTokens++;
					} else{
						neighbourFieldEmpty = true;
					}
				}
				else
				{
					neighbourFieldEmpty = true;
				}
			}
		} 
	}

	if(positionInputValid(endNeighbour))
	{
		if(freePosition(endNeighbour) || isTokenFromCurrentTeam(endNeighbour))
		{
			endNeighbourValid = true;
		}
		else
		{
			endNeighbourValid = false;
		}
	}
	else
	{
		endNeighbourValid = true;
	}

	//Only Neighbour of startPosition is Token from other Team
	if(positionInputValid(startNeighbour))
	{
		if((endNeighbourValid == true && !freePosition(startNeighbour) && !isTokenFromCurrentTeam(startNeighbour)) || useraction.captureOption == Withdraw )
		{
			while(!neighbourFieldEmpty){
				if(positionInputValid(startNeighbour))
				{
					if(!freePosition(startNeighbour) &&  !isTokenFromCurrentTeam(startNeighbour)){
						if(mode.compare("capture") == 0){
							meinSpielbrett.emptyCell(startNeighbour);
						}
						startNeighbour = getNeighbour(startNeighbour, startNeighbourDir);
						capturedTokens++;
					} else{
						neighbourFieldEmpty = true;
					}
				}
				else
				{
					neighbourFieldEmpty = true;
				}
			}
		}
	}
    //cout << "Number of deleted tokens: " << capturedTokens << endl;
	meinSpielbrett.updateLeftTokens();

	return capturedTokens;
}


int Game::captureToken(struct Useraction userAction)
{
	int capturedTokens;

	switch(userAction.dir)
    {
        case North: { //Token moves to North - check neighbour in the North
            struct position startNeighbour = getNeighbour(userAction.start, South);
            struct position endNeighbour = getNeighbour(userAction.end, North);

            capturedTokens = capture(userAction, startNeighbour, South, endNeighbour, North, "capture");
        }
		break;
        case South: { //Token moves to South 
            struct position startNeighbour = getNeighbour(userAction.start, North);
            struct position endNeighbour = getNeighbour(userAction.end, South);

            capturedTokens =  capture(userAction, startNeighbour, North, endNeighbour, South, "capture");
        break;
        }
        case East:{ //Token moves to East - check neighbour in the East
            struct position startNeighbour = getNeighbour(userAction.start, West);
            struct position endNeighbour = getNeighbour(userAction.end, East);

            capturedTokens = capture(userAction, startNeighbour, West, endNeighbour, East, "capture");

        break;
        }
        case West: {    //Token moves to West - check neighbour in the West
            struct position startNeighbour = getNeighbour(userAction.start, East);
            struct position endNeighbour = getNeighbour(userAction.end, West);

            capturedTokens = capture(userAction, startNeighbour, East, endNeighbour, West, "capture");
        break;
        }
        case Northwest: { //Token moves to Northwest - check neighbour in the Northwest
			struct position startNeighbour = getNeighbour(userAction.start, Southeast);
            struct position endNeighbour = getNeighbour(userAction.end, Northwest);

            capturedTokens = capture(userAction, startNeighbour, Southeast, endNeighbour, Northwest, "capture");
        break;
        }
        case Southeast: { //Token moves to Southeast - check neighbour in the Southeast
            struct position startNeighbour = getNeighbour(userAction.start, Northwest);
            struct position endNeighbour = getNeighbour(userAction.end, Southeast);

            capturedTokens = capture(userAction, startNeighbour, Northwest, endNeighbour, Southeast, "capture");
        break;
        }
        case Northeast: {//Token moves to Northeast - check neighbour in the Northeast
            struct position startNeighbour = getNeighbour(userAction.start, Southwest);
            struct position endNeighbour = getNeighbour(userAction.end, Northeast );

            capturedTokens = capture(userAction, startNeighbour, Southwest, endNeighbour, Northeast, "capture");
        break;
        }
        case Southwest:{//Token moves to Southwest - check neighbour in the Southwest
            struct position startNeighbour = getNeighbour(userAction.start, Northeast );
            struct position endNeighbour = getNeighbour(userAction.end, Southwest);

            capturedTokens = capture(userAction, startNeighbour, Northeast, endNeighbour, Southwest, "capture");
        break;
        }
		case InvalidDirection: 
		break;
    }

	return capturedTokens;
}


void Game::clearScreen(void)
{
	int i = 0;
	while(i++ < LINES_TO_CLEAR)
		cout << endl;
}

struct Useraction Game::getHumanUseraction(void)
{
	struct Useraction useraction;
	useraction.command = Invalid;
	useraction.captureOption = Unset;
	
	string userinput;
	
	this->clearScreen();
	this->meinSpielbrett.print();
	cout << endl;

	//show all errors
	for(string entry : errorvec){
		cout << entry << endl;
	}
	//clear all errors
	errorvec.clear();

	cout << endl;
		
	do
	{
		cout << " [" << Token::asChar( this->currentPlayer->getTeam() ) << "] " << this->currentPlayer->getName() << ", " << "make your turn! (example A3 SW) > " << flush;	
		getline(cin, userinput);
	}
	while(userinput=="");
	
	// use toupper() in a Lambda expression to transform userinput to upper case
	std::for_each( userinput.begin(), userinput.end(),
		// pass each character by reference to callback
		[](char &c){ c = ::toupper(c); }
	);
	
	string snippet;
	istringstream iss(userinput);
	
	iss >> snippet;
	
	// recognize patterns in userinput through ECMAScript regular expressions	
	
	regex coordinateLiteral = regex("^[A-I][1-5]|[1-5][A-I]$");
	regex directionLiteral  = regex("^N|NE|E|SE|S|SW|W|NW$");
	
	if( regex_match(snippet, coordinateLiteral) ) // user typed XY (...)
	{
		useraction.start = string2position(snippet);
		
		if (iss >> snippet) // user typed XY dir
		{
			/*
			if( regex_match(snippet, directionLiteral) ) // user typed XY dir
			{
				useraction.dir = string2direction(snippet);
				useraction.command = useraction.dir != InvalidDirection ? Move : Invalid; // TODO validate!!
			}
			else
			{
				useraction.command = Invalid;
			}
			*/
			
			useraction.dir = string2direction(snippet);
			useraction.end = getNeighbour(useraction.start, useraction.dir);
			useraction.command = useraction.dir != InvalidDirection ? Move : Invalid; // TODO validate!!
		}
		else // user typed XY (only)
		{
			useraction.command = Invalid;
		}
		
		if (useraction.start.row < 0 || useraction.start.column < 0)
			useraction.command = Invalid;
	}
	else if( regex_match(snippet, directionLiteral) ) // user typed dir
	{
		// TODO useraction.start = ...  ,  useraction.end = ...
		useraction.dir = string2direction(snippet);
		useraction.command = useraction.dir != InvalidDirection ? Move : Invalid; // TODO validate!!
	}	
	else // user typed sth else
	{
		// as it's no MOVE command, try to identify command on the map
		auto iterator = commandMap.find(snippet);
		useraction.command = iterator != commandMap.end() ? iterator->second : Invalid; // TODO validate!!
	}
	
	if(useraction.command == Invalid)
	{
		string temp = "Invalid command: " + snippet + "\nUse command \"help\" for a short manual.";
		errorvec.push_back(temp);
		// cout << "Press <ENTER> to try again." << flush;
		// getline(cin,userinput); // TODO: just some random string not used anymore
	}
	

	return useraction;
}

struct Useraction Game::getAIUseraction(void){
	//save current status of game
	Board savedBoard = meinSpielbrett;
	Player *savedPlayer = currentPlayer;
	struct position newCurPos = currentPosition;
	enum Direction saveDir = lastDirection;
	int counterSave = counterMoves;
	bool beenThereSave[5][9];
	bool capturingYesSave = capturingYes;

	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			beenThereSave[row][column] = grid[row][column];
		}
	}

	this->clearScreen();
	this->meinSpielbrett.print();
	cout << endl;

	Tree decisionTree;
<<<<<<< HEAD
=======
	nextNode(&(decisionTree.root), 3); //create Tree 
	
>>>>>>> 7c8a5bc1d2eb4b03d3ec30fc6394df98c1f078d4

	nextNode(&(decisionTree.root), 5); //create Tree 

	Node * bestNode;
	if(alphaBeta){
		Node empty;
		empty.setIsMax(true);
		empty.setCost(2);
		bestNode = compareChildrenAlphaBeta(&(decisionTree.root), &empty); //evaluate tree and find best option
	} else {
		bestNode = compareChildren(&(decisionTree.root)); //evaluate tree and find best option
	}

	//printNodeScore(&(decisionTree.root), 2);
	Useraction bestAction = bestNode->getUseraction();

	cout << "Dir: " << bestAction.dir << endl;
	cout << "Cmd: " << bestAction.command << endl;
	cout << "CaptureOption: " << bestAction.captureOption << endl;
	cout << "End Row: " << bestAction.end.row << endl;
	cout << "End Column: " << bestAction.end.column << endl;
	cout << "Start Row: " << bestAction.start.row << endl;
	cout << "Start Column: " << bestAction.start.column << endl;

	//reset game to status before testing possible moves
	meinSpielbrett = savedBoard;
	currentPlayer = savedPlayer;
	counterMoves = counterSave;
	lastDirection = saveDir;
	currentPosition = newCurPos;
	capturingYes = capturingYesSave;
	capturingPossible();

	//reset beenThere
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			grid[row][column] = beenThereSave[row][column];
		}
	}

	/*std::vector<Useraction> possibleMoves = getPossibleMoves();

	for (int i=0; i < possibleMoves.size() ; ++i){
		cout << "Dir: " << possibleMoves.at(i).dir << endl;
		cout << "Cmd: " << possibleMoves.at(i).command << endl;
		cout << "CaptureOption: " << possibleMoves.at(i).captureOption << endl;
		cout << "End Row: " << possibleMoves.at(i).end.row << endl;
		cout << "End Column: " << possibleMoves.at(i).end.column << endl;
		cout << "Start Row: " << possibleMoves.at(i).start.row << endl;
		cout << "Start Column: " << possibleMoves.at(i).start.column << endl;
		cout << endl;

	}*/


	return bestAction;
}

void Game::printNodeScore(Node *root, int depth){
	vector<Node *> children =  root->getChildren();
	cout << "length: " << children.size() << endl;
	cout << "IsMax: " << root->getIsMax() << endl;

	for (int i=0; i < children.size() ; ++i){
		cout << "Cost: " << (children)[i]->getCost() << endl;

		vector<Node *> childrenNode =  (children)[i]->getChildren();
		cout << "Children length: " << childrenNode.size() << endl;

		if(childrenNode.size() > 0){ // if there are more childs go deeper
			printNodeScore((children)[i], depth-1);
		} else { //no more children


		}
	} 
}

Node* Game::compareChildren(Node * root)
{
	vector<Node *> children =  root->getChildren();

	Node* winningChild;

	if(children.size() > 0){
		winningChild = children.at(0);

		for (int i=0; i < children.size() ; ++i)
		{	
			Node* child = compareChildren(children.at(i));

			//get winningChild
			if(root->getIsMax()) //max
			{
				/*if(winningChild->getCost() < children.at(i)->getCost()){
					winningChild = children.at(i);
				}*/

				if(root->getCost() < children.at(i)->getCost()){
					root->setCost(children.at(i)->getCost());
					winningChild = children.at(i);
				}
			} else //min
			{

				if(root->getCost() > children.at(i)->getCost()){
					root->setCost(children.at(i)->getCost());
					winningChild = children.at(i);
				}
				/*if(winningChild->getCost() > children.at(i)->getCost()){
					winningChild = children.at(i);
				}*/
			}
		}
	} 
	else
	{
		return root;
	}
	
	//root->setCost(winningChild->getCost());
	return winningChild;
}

	bool betaIsSet= false;
	bool alphaIsSet = false;

Node* Game::compareChildrenAlphaBeta(Node * root, Node * parent){
	vector<Node *> children =  root->getChildren();
	Node* winningChild;

	//cout << "Children size: " << children.size() << endl;
	if(children.size() > 0){
		winningChild = children.at(0);
		/*winningChild->setAlpha(alpha);
		winningChild->setBeta(beta);*/


		for (int i=0; i < children.size() ; ++i)
		{	

			children.at(i)->setAlpha(root->getAlpha());
			children.at(i)->setBeta(root->getBeta());
			Node* child = compareChildrenAlphaBeta(children.at(i), root);
	

			//get winningChild
			if(root->getIsMax()) //max
			{
				/*cout << "isMax" << endl;
				cout << "Root Cost:" << root->getCost() << endl;
				cout << "Root Alpha:" << root->getAlpha() << endl;
				cout << "Root Beta:" << root->getBeta() << endl;

				cout << "Child Cost:" << children.at(i)->getCost() << endl;
				cout << "Child Alpha:" << children.at(i)->getAlpha() << endl;
				cout << "Child Beta:" << children.at(i)->getBeta() << endl;*/

				
				if(root->getCost() < children.at(i)->getCost()){
					root->setCost(children.at(i)->getCost());
					winningChild = children.at(i);
				}

				if(root->getBeta() <= children.at(i)->getCost()){
					//root->setBeta(children.at(i)->getCost());
					/*cout << "beta prun" << endl;
					cout << "Root Cost PRUN:" << root->getCost() << endl;
					cout << "Root Alpha PRUN:" << root->getAlpha() << endl;
					cout << "Root Beta PRUN:" << root->getBeta() << endl;*/
					//winningChild = children.at(i);
					return winningChild;
				}

				if(root->getAlpha() < children.at(i)->getCost()){
					root->setAlpha(children.at(i)->getCost());
				}

				/*cout << "Root Cost AFTER:" << root->getCost() << endl;
				cout << "Root Alpha AFTER:" << root->getAlpha() << endl;
				cout << "Root Beta AFTER:" << root->getBeta() << endl;*/


			} else //min
			{
				if(root->getCost() > children.at(i)->getCost()){
					root->setCost(children.at(i)->getCost());
					winningChild = children.at(i);
				}
				if(root->getAlpha() >= children.at(i)->getCost()){
					//root->setAlpha(children.at(i)->getCost());
					//winningChild = children.at(i);
					return winningChild;
				}
				if(root->getBeta() > children.at(i)->getCost()){
					root->setBeta(children.at(i)->getCost());
					betaIsSet = true;
				}
			}
				if(parent->getIsMax()){
				/*	cout << "hier wirds ernst MAX" << endl;
					cout << "Root Cost VORHER:" << root->getCost() << endl;
					cout << "Parent Cost VORHER:" << parent->getCost() << endl;*/
					if((root->getCost() < parent->getCost())){
						return winningChild;
					}
				} else {
					/*cout << "hier wirds ernst MIN" << endl;
					cout << "Root Cost VORHER:" << root->getCost() << endl;
					cout << "Parent Cost VORHER:" << parent->getCost() << endl;*/
					if((root->getCost() > parent->getCost())){
						return winningChild;
					}
				}

		/*	cout << "Cost: " << root->getCost() << endl;
			cout << "Alpha: " << root->getAlpha() << endl;
			cout << "Beta: " << root->getBeta() << endl;*/
		}
	} 
	else
	{
		return root;
	}
	
	//root->setCost(winningChild->getCost());
	//root->setAlpha(winningChild->getAlpha());
	//root->setBeta(winningChild->getBeta());



	/*root->setCost(winningChild->getCost());
	root->setAlpha(winningChild->getAlpha());
	root->setBeta(winningChild->getBeta());*/


	return winningChild;
}



void Game::nextNode(Node *root, int depth){
	std::vector<Useraction> possibleMoves = getPossibleMoves();

	//cout << "possibleMoves length: " << possibleMoves.size() << endl;
	
	Player *test = currentPlayer; 
	Board savedBoard = meinSpielbrett;
	struct position newCurPos = currentPosition;
	enum Direction savedDir = lastDirection;
	int counterSave = counterMoves;
	bool capturingYesSaved = capturingYes;

	// hier grid speichern
	bool beenThereSave[5][9];

	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			beenThereSave[row][column] = grid[row][column];
		}
	}

	if(possibleMoves.size() > 0){
	for (int i=0; i < possibleMoves.size() ; ++i){
		currentPlayer = test;
		meinSpielbrett = savedBoard;
		currentPosition = newCurPos;
		counterMoves = counterSave;
		lastDirection = savedDir;
		capturingYes = capturingYesSaved;
		Node* n = root->createNode(possibleMoves.at(i));

		for(int row=0; row<5; row++)
		{
			for(int column=0; column<9; column++)
			{
				grid[row][column] = beenThereSave[row][column];
			}
		}

		counterMoves = 1; //set: first move of current player

		//cout << "Calculate" << endl;

		//check if currentPlayer could capture anyone (true = yes)
		capturingYes = capturingPossible(); 

		moveNew(possibleMoves.at(i));
		/*this->clearScreen();
		this->meinSpielbrett.print();
		cout << endl;*/

		if(!restart && !quit)
		{
							

			if(capturingAgain() && capturingYes && !skip) 
			{
				anotherMove = true;
			} 
			else
			{
				anotherMove = false;
			}

		}
		else
		{
				anotherMove = false;
		}
	
		if (!anotherMove && depth != 0){ //switch Player
			counterMoves = 1;

			if(currentPlayer->getTeam() == WHITE)
			{
				currentPlayer = &playerBlack;
			}
			else
			{
				currentPlayer = &playerWhite;
			}
			lastDirection = InvalidDirection;

			//clear grid for check "beenThere"
			for(int row=0; row<5; row++)
			{
				for(int column=0; column<9; column++)
				{
					grid[row][column] = 0;
				}
			}

			capturingYes = capturingPossible(); 
			n->setIsMax(!(n->getIsMax()));

			if(n->getIsMax()){
				n->setCost(std::numeric_limits<float>::min());
			} else {
				n->setCost(std::numeric_limits<float>::max());
			}


			nextNode(n, depth-1); // maybe causes segmentation fault
		} 
		else if(anotherMove && depth != 0) //another move for same player
		{

			nextNode(n, depth-1); // maybe causes segmentation fault
		} 
		else if (depth == 0) //Abbrechen wenn depth 0 ist
		{ 
			int heuristik1TokenDel = heuristik1(currentPlayer->getTeam(), meinSpielbrett);
			float tokensInLine = heuristik3(currentPlayer->getTeam(), meinSpielbrett);
			float tokensPosition = heuristik2(currentPlayer->getTeam(), meinSpielbrett);

			float cost = tokensPosition + heuristik1TokenDel + tokensInLine;
			// cout << "Heuristik 1: " << heuristik1TokenDel << endl;
			// cout << "Heuristik 2: " << tokensPosition << endl;
			// cout << "Heuristik 3: " << tokensInLine << endl;
			// cout << possibleMoves[i].start.column <<  "," << possibleMoves[i].start.row << ";" << possibleMoves[i].dir << ": cost" << cost << endl;

			n->setCost(cost);
		}	
	//delete (n); // to keep the Heap empty on application terminating, so Valgrind Leak summary looks nicer :)
	}
	} else {
			int heuristik1TokenDel = heuristik1(currentPlayer->getTeam(), meinSpielbrett);
			float tokensInLine = heuristik3(currentPlayer->getTeam(), meinSpielbrett);
			float tokensPosition = heuristik2(currentPlayer->getTeam(), meinSpielbrett);

			float cost = tokensPosition + heuristik1TokenDel + tokensInLine;
			root->setCost(cost);
	}
}

void Game::moveNew(Useraction useraction){

	bool validAction = false;
	skip = false;

		switch(useraction.command)
		{
			case Move:
				{
					if(isMoveValid(useraction.start, useraction.end, useraction.dir)) //enum Command command
					{
						//update grid for beenThere
						if(counterMoves == 1) 
						{
							grid[useraction.start.row][useraction.start.column] = 1;
						}
						if(grid[useraction.end.row][useraction.end.column] == 0)
						{
							grid[useraction.end.row][useraction.end.column] = 1;
						}

						int capturedTokens = moveToken(useraction);
						
						lastDirection = useraction.dir;
						currentPosition = useraction.end;
						counterMoves++; 

						validAction = true;
					}
					else
					{
						validAction = false;
					}

				}; break;

		}
}


void Game::setFieldOfView(struct position position, struct Grid fieldOfView)
{
	this->meinSpielbrett.setFieldOfView(position,fieldOfView);
}

enum Direction Game::string2direction(string str)
{
	// use toupper() in a Lambda expression to transform string to upper case
	std::for_each( str.begin(), str.end(),
		// pass each character by reference to callback
		[](char &c){ c = ::toupper(c); }
	);
	
	auto iterator = directionMap.find(str);
	return iterator != directionMap.end() ? iterator->second : InvalidDirection;
}

struct position Game::string2position (string str)
{
	struct position pos {-1,-1};
	char c;
	
	if (str.length() == 2)
	{
		// use toupper() in a Lambda expression to transform string to upper case
		std::for_each( str.begin(), str.end(),
			// pass each character by reference to callback
			[](char &c){ c = ::toupper(c); }
		);
		
		c = str.at(0);
		if (c >= 'A' && c <= 'I')
			pos.column = c - 65;
		else if (c >= '1' && c <= '5')
			pos.row = c - 49;
		
		c = str.at(1);
		if (c >= 'A' && c <= 'I')
			pos.column = c - 65;
		else if (c >= '1' && c <= '5')
			pos.row = c - 49;
	}
	
	return pos;
}

enum Direction Game::getDirectionFromInteger (int direction)
// TODO: why this conversion func? enums ARE integers! ~~ingo
{
	enum Direction result;

	switch(direction) 
	{
   		case 0: result = North; break;
		
		case 1: result = East; break;

		case 2: result = South; break;

		case 3: result = West; break;

		case 4: result = Northeast; break;

		case 5: result = Southeast; break;

		case 6: result = Southwest; break;

		case 7: result = Northwest; break;
	}
	return result;
}

int Game::heuristik3(Team currentPlayer, Board board){
	int counter=0;
	Team PlayerOfLastToken=currentPlayer;
	vector<int> heuristik3vec;
	//int returnvalue=0;

	for (int i=0; i<9; i++){
		for (int j=0; j<5; j++){
			struct position pos;
			pos.row=j;
			pos.column=i;

			if (board.getCell(pos).getToken().getTeam()==PlayerOfLastToken){
				if (board.getCell(pos).getToken().getTeam()==currentPlayer){
					counter++;
				}
				else{
					counter--;
				}
			}
			else{
				heuristik3vec.push_back(counter);
			}
				
		

			if (j==4){
					PlayerOfLastToken=currentPlayer;
					counter=0;
			}
		}
	}

	for (int j=0; j<5; j++){
		for (int i=0; i<9; i++){
			struct position pos;
			pos.row=i;
			pos.column=j;

			if (board.getCell(pos).getToken().getTeam()==PlayerOfLastToken){
				if (board.getCell(pos).getToken().getTeam()==currentPlayer){
					counter++;
				}
				else{
					counter--;
				}
			}
			else{
				heuristik3vec.push_back(counter);
			}


			if (i==8){
					PlayerOfLastToken=currentPlayer;
					counter=0;
			}

		}
	}

	for (int i=0; i<9; i++){
		for (int j=0; j<5; j++){
			if ((i+j==4)|| (i+j==6)|| (i+j==8)|| (i+j==10)|| (i+j==12)){
				struct position pos;
				pos.row=i;
				pos.column=j;

				if (board.getCell(pos).getToken().getTeam()==PlayerOfLastToken){
					if (board.getCell(pos).getToken().getTeam()==currentPlayer){
						counter++;
					}
					else{
						counter--;
					}
				}
				else{
					heuristik3vec.push_back(counter);
				}


				if ((i==8)||(j==4)){
					PlayerOfLastToken=currentPlayer;
					counter=0;
				}
			}
		}
	}

		for (int i=0; i<9; i++){
		for (int j=0; j<5; j++){
			if ((i==j) || (i==j-2) || (i==j+2) || (i==j+4) || (i==j+6)){
				struct position pos;
				pos.row=i;
				pos.column=j;

				if (board.getCell(pos).getToken().getTeam()==PlayerOfLastToken){
					if (board.getCell(pos).getToken().getTeam()==currentPlayer){
						counter++;
					}
					else{
						counter--;
					}
				}
				else{
					heuristik3vec.push_back(counter);
				}


				if ((i==8)||(j==4)){
					PlayerOfLastToken=currentPlayer;
					counter=0;
				}
			}
		}
	}


	float squarenumber=1.5;
	int returnvaluepos=0;
	int returnvalueneg=0;
	for (int value : heuristik3vec){
		if (value>0){
			returnvaluepos+=pow(value,squarenumber);
		}
		else{
			returnvalueneg+=pow(value,squarenumber);
		}
		
	}

	returnvaluepos= pow(returnvaluepos,1/squarenumber);
	returnvalueneg= pow(returnvalueneg,1/squarenumber);

	return returnvaluepos-returnvalueneg;
}

int Game::heuristik1(Team currentPlayer,Board board){

	int tokensLeftBlack = 0;
	int tokensLeftWhite = 0;

	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{			

			struct position pos;
			pos.row=row;
			pos.column=column;

			if(board.getCell(pos).getOccupied() && board.getCell(pos).getToken().getTeam() == BLACK){
				tokensLeftBlack++;
			}
			else if( board.getCell(pos).getOccupied() && board.getCell(pos).getToken().getTeam() == WHITE){
				tokensLeftWhite++;
			}
		}
	}

	int c1=5;
	int returnvalue;
	if (currentPlayer==WHITE){
		returnvalue=c1*(tokensLeftWhite-tokensLeftBlack);
	}
	if(currentPlayer==BLACK){
		returnvalue=c1*(tokensLeftBlack-tokensLeftWhite);
	}

	return returnvalue;
	

}

float Game::heuristik2(Team currentPlayer,Board board){

	float returnvalue = 0;

	for (int i=0; i<9; i++){
		for (int j=0; j<5; j++){
			struct position pos;
			pos.row=j;
			pos.column=i;

			if (board.getCell(pos).getToken().getTeam()==currentPlayer){
				returnvalue+=board.getheuristik2(pos);
				//cout << board.getheuristik2(pos) << endl << i << "," << j<<  endl << endl;
			}
			else{
				returnvalue-=board.getheuristik2(pos);
			}
			
		}
	}
	float c1=2.0;
	return c1*returnvalue;
}

