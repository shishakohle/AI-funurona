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

#include <iostream>

using namespace std;

enum Team {BLACK, WHITE};

class Player
{
	private:
	
		char name[16];
		enum Team team;
	
	public:
	
		// constructor for instances of Player
		// TODO
		
		// getter for player's name
		// TODO
		
		// get player's token
		char getToken()
		{
			char token;
			
			switch (team)
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
			team = t;
		}
		Team getTeam()
		{
			return team;
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
	
		enum Team currentTeam;
		bool gameWon;
		Board meinSpielbrett;
	
	public:
	
		Game()
		{
			currentTeam = WHITE;
			gameWon = false;

			meinSpielbrett.init();
			meinSpielbrett.print();

		};
		
		void start()
		{
			cout << "Welcome to funurona! Player white begins." << endl;

			while(!gameWon)
			{
				turn();
			}
		};
	
	private:
	
		void turn()
		{
			cout << "Player " << currentTeam << ": " << "Make your turn!" << endl;
			
			cout << "Choose startpostion" << endl;
			struct position startPosition = chooseToken();
				cout << "Startposition COL: " << startPosition.column << endl;
				cout << "Startposition ROW: " << startPosition.row << endl;


			// Ist auf dieser Position ein Token von dem Team?

			cout << "Choose endposition:" << endl;
			struct position endPostion = chooseToken();
				cout << "Endposition COL: " << endPostion.column << endl;
				cout << "Endposition ROW: " << endPostion.row << endl;

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
};

int main(void)
{
	//cout << "Hello World!" << endl;
	Game meinSpiel;

	meinSpiel.start();

	return 0;
}
