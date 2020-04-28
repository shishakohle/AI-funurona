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
 * colors: black -> # , white -> o , empty cell -> .
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
	private:
		enum Team team;
		struct position;
};

class Cell
{
	public:
		
	private:
		struct position;
		Token token;
	
};

class Board
{
	private:
		Cell cells[9][5];
	
	public:
		void init(void)
		{
			
		}
};

int main(void)
{
	cout << "Hello World!" << endl;
	
	Board meinSpielbrett;
	
	meinSpielbrett.init();
	
	
	return 0;
}
