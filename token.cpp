#include "token.h"

void Token::setTeam(Team t)
{
	this->team = t;
}

Team Token::getTeam(void)
{
	return this->team;
}

void Token::setLastMoveDirection(struct lastMoveDirection lmd)
{
	this->lmd = lmd;
}

struct lastMoveDirection Token::getLastMoveDirection(void)
{
	return this->lmd;
}

char Token::asChar(void) // TODO invoke this when printing the board. or is this needed overall?
{
	return this->asChar(this->team);
}

char Token::asChar(enum Team team) // TODO: private??
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

//tokenGrid to check from where it could capture someone
void Token::setGrid(struct position pos, bool value)
{
	if(value = true)
	{
		//can capture one if would move there)
		gridCapturing[pos.row][pos.column] = 1;
	}
	else
	{
		//cant capture one if would move ther
		gridCapturing[row][column] = 0;
	}
}

bool Token::getGridBool()
{
	gridBool = false;
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			if(gridCapturing[row][column] == 1)
			{
				gridBool = true;
			}
		}
	}
	return gridBool;
}

//TODO: set fehlt
struct position getPosition ()
{
	return this--> pos;
}

