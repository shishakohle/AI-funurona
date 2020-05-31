#include "board.h"

void Board::init(void)
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

void Board::print(void)
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

Cell Board::getCell(struct position position)
{
	return cells[position.row][position.column];
}

void Board::setTokenOnCell(struct position position, Token token)
{
	cells[position.row][position.column].setToken(token); 
}

void Board::emptyCell(struct position position)
{
	cells[position.row][position.column].setOccupied(false); 
}

void Board::updateLeftTokens(void)
{
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			if(cells[row][column].getToken().getTeam() == BLACK){
				tokensLeftBlack++;
			}
			else if(cells[row][column].getToken().getTeam() == WHITE){
				tokensLeftWhite++;
			}
		}
	}
}

int Board::getLeftTokensBlack(void)
{
	return tokensLeftBlack;
}

int Board::getLeftTokensWhite(void)
{
	return tokensLeftWhite;
}

void Board::setFieldOfView(struct position position, struct Grid fieldOfView)
{
	this->cells[position.row][position.column].setFieldOfView(fieldOfView);
}

