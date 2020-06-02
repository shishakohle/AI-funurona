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

bool Token::getGridBool()
{
	bool gridBool = false;
	for(int row=0; row<5; row++)
	{
		for(int column=0; column<9; column++)
		{
			if(fieldOfView.gridPosition[row][column] == 1)
			{
				gridBool = true;
			}
		}
	}
	return gridBool;
}

bool Token::getGridBool(struct position pos)
{
	bool gridBool = false;

	if(fieldOfView.gridPosition[pos.row][pos.column] == 1)
	{
		gridBool = true;
	}

	return gridBool;
}

void Token::setFieldOfView(struct Grid fieldOfView)
{
	this->fieldOfView = fieldOfView;
}

struct Grid Token::getFieldOfView(void)
{
	return this->fieldOfView;
}

