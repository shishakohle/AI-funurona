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

#include <iostream>

using namespace std;

enum Team {black, white};

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
				switch (token.getTeam())
				{
					case black: out = '#'; break;
					case white: out = 'O'; break;
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
						t.setTeam(black);
						cells[row][column].setToken(t);
					}
					else if (row==3||row==4)
					{
						t.setTeam(white);
						cells[row][column].setToken(t);
					}
					else
					{
						switch(column)
						{
							case 0: t.setTeam(black); cells[row][column].setToken(t); break;
							case 2: t.setTeam(black); cells[row][column].setToken(t); break;
							case 5: t.setTeam(black); cells[row][column].setToken(t); break;
							case 7: t.setTeam(black); cells[row][column].setToken(t); break;
							case 1: t.setTeam(white); cells[row][column].setToken(t); break;
							case 3: t.setTeam(white); cells[row][column].setToken(t); break;
							case 6: t.setTeam(white); cells[row][column].setToken(t); break;
							case 8: t.setTeam(white); cells[row][column].setToken(t); break;
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

int main(void)
{
	//cout << "Hello World!" << endl;
	
	Board meinSpielbrett;
	
	meinSpielbrett.init();
	meinSpielbrett.print();
	
	
	return 0;
}
