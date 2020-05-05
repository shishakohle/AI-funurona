// some comments

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

#define TOKEN_WHITE 'O'
#define TOKEN_BLACK '#'
#define UNNAMED_PLAYER "unnamed"
#define LINES_TO_CLEAR 50

#include <iostream>
#include <fstream>

using namespace std;

enum Team {BLACK, WHITE};

class Player
{
	private:
	
		string name;
		enum Team team;
		int tokensLeft;
	
	public:
	
		// overloaded constructors for instances of Player
		
		Player()
		{
			this->setName(UNNAMED_PLAYER);
			this->setLeftTokens(22);
		}
		
		Player(string name, enum Team team)
		{
			this->setName(name);
			this->setTeam(team);
		}
		
		// setter for player's name
		void setName(string name)
		{
			!name.empty() ? this->name=name : this->name = UNNAMED_PLAYER;
		}
		
		// setter for player's team
		void setTeam(enum Team team)
		{
			this->team = team;
		}

		// setter for player's amount of left tokens
		void setLeftTokens(int tokensLeft)
		{
			this->tokensLeft = tokensLeft;
		}
		
		// getter for player's name
		string getName()
		{
			return this->name;
		}
		
		enum Team getTeam()
		{
			return this->team;
		}

		int getLeftTokens()
		{
			return this->tokensLeft;
		}
		
		// get player's token // TODO: needed?
		char getToken()
		{
			char token;
			
			switch (this->team)
			{
				case WHITE: token = TOKEN_WHITE; break;
				case BLACK: token = TOKEN_BLACK; break;
				// default: break;
			}
			
			return token;
		}
};

struct position
{
	int column,row;
};

class Token
{
	public:
	
		void setTeam(Team t)
		{
			this->team = t;
		}
		
		Team getTeam()
		{
			return this->team;
		}
		
		char asChar() // TODO invoke this when printing the board. or is this needed overall?
		{
			return this->asChar(this->team);
		}
		
		static char asChar(enum Team team) // TODO: private??
		{
			char out = '?';
			
			switch (team)
			{
				case BLACK: out = TOKEN_BLACK; break;
				case WHITE: out = TOKEN_WHITE; break;
				// default: break;
			}
			
			return out;
		}
		
	private:
	
		enum Team team;
		struct position;
};

class Cell
{
	public:
		void setToken(Token t)
		{
			token = t;
			isOccupied = true;
		}
		
		void setOccupied(bool flag)
		{
			isOccupied = flag;
		}
		
		char printStatus()
		{
			char out = '.';
			
			if (isOccupied)
			{
				switch (token.getTeam()) // TODO for Ingo
				{
					case BLACK: out = TOKEN_BLACK; break;
					case WHITE: out = TOKEN_WHITE; break;
					default: break;
				}
			}
			
			return out;
		}
	private:
		struct position;
		Token token;
		bool isOccupied;
	
};

class Board
{
	private:
		Cell cells[5][9];
	
	public:
		void init(void)
		{
			// rows 4 - 5
			
			for(int row=0; row<5; row++)
			{
				for(int column=0; column<9; column++)
				{
					Token t;
					
					if (row==0||row==1)
					{
						t.setTeam(BLACK);
						cells[row][column].setToken(t);
					}
					else if (row==3||row==4)
					{
						t.setTeam(WHITE);
						cells[row][column].setToken(t);
					}
					else
					{
						switch(column)
						{
							case 0: t.setTeam(BLACK); cells[row][column].setToken(t); break;
							case 2: t.setTeam(BLACK); cells[row][column].setToken(t); break;
							case 5: t.setTeam(BLACK); cells[row][column].setToken(t); break;
							case 7: t.setTeam(BLACK); cells[row][column].setToken(t); break;
							case 1: t.setTeam(WHITE); cells[row][column].setToken(t); break;
							case 3: t.setTeam(WHITE); cells[row][column].setToken(t); break;
							case 6: t.setTeam(WHITE); cells[row][column].setToken(t); break;
							case 8: t.setTeam(WHITE); cells[row][column].setToken(t); break;
							case 4: cells[row][column].setOccupied(false); break;
							default: break;
						}
					}
				}
			}
		}
		
		void print(void)
		{
			char longitude[]="  A B C D E F G H I";
			
			// print longitude
			cout  << longitude << endl;
			
			for(int row=0; row<5; row++)
			{
				// print latitude
				cout << row+1 << " " << flush;
				
				for(int column=0; column<9; column++)
				{
					cout << cells[row][column].printStatus() << flush;
					if (column!=8)
						cout << "-" << flush;
				}
				
				// print latitude
				cout << " " << row+1 << flush;
				
				cout << endl;
				
				if(row%2 == 0 && row < 4)
					cout << "  |\\|/|\\|/|\\|/|\\|/|" << endl;
				else if (row < 4)
					cout << "  |/|\\|/|\\|/|\\|/|\\|" << endl;
			}
			
			// print longitude
			cout << longitude << endl;
		}
};


class Game {

	private:
	
		//enum Team currentTeam;
		Player *currentPlayer;
		bool gameWon;
		Player *winner;
		Board meinSpielbrett;
		Player playerWhite, playerBlack;
	
	public:
	
		Game()
		{
			//this->currentTeam = WHITE;
			this->currentPlayer = &playerWhite;
			this->gameWon = false;
			this->playerWhite.setTeam(WHITE);
			this->playerBlack.setTeam(BLACK);

			meinSpielbrett.init();
		};
		
		void start() // TODO: private??
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
				turn();
				gameOver();
				//change current player

			}
			cout << "The game is over. "<< this->winner->getName() <<"you have won. Congratulations!" << endl;
		};
	
	private:
	
		void turn()
		{
			// clear screen
			this->clearScreen();
			
			meinSpielbrett.print();
			
			cout << "\nPlayer " << this->currentPlayer->getName() << "-" << Token::asChar( this->currentPlayer->getTeam() ) << ": " << "Make your turn!\n" << endl;
			
			cout << "Choose startpostion" << endl;
			struct position startPosition = chooseToken();
				cout << "\tStartposition COL: " << startPosition.column << endl;
				cout << "\tStartposition ROW: " << startPosition.row << endl;


			// Ist auf dieser Position ein Token von dem Team?

			cout << "Choose endposition:" << endl;
			struct position endPostion = chooseToken();
				cout << "\tEndposition COL: " << endPostion.column << endl;
				cout << "\tEndposition ROW: " << endPostion.row << endl;

			// Kann dieser Zug ausgeführt werden?
			// - Ist die Position eine freie Position?
			// - ist dieses feld erreichbar? (zugweite 1, felder müssen verbunden sein)


			meinSpielbrett.print();
		}

		struct position chooseToken()
		{
			int row, col;

			cout << "Please choose the row: ";
			cin >> row;
			cout << "Please choose the column: ";
			cin >> col;

			struct position position;
			position.column = col;
			position.row = row;

			return position;
		}
		
		//check if game is over and who is winner
		void gameOver ()
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
		
		void clearScreen()
		{
			int i = 0;
			while(i++ < LINES_TO_CLEAR)
				cout << endl;
		}
};

int main(void)
{
	//cout << "Hello World!" << endl;
	Game meinSpiel;

	meinSpiel.start();

	return 0;
}
