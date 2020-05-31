#include "cell.h"

void Cell::setToken(Token t)
{
	token = t;
	isOccupied = true;
}

void Cell::setOccupied(bool flag)
{
	isOccupied = flag;
}

bool Cell::getOccupied(void)
{
	return isOccupied;
}

char Cell::printStatus(void)
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

Token Cell::getToken(void)
{
	return token;
}

void Cell::deleteToken(void)
{
	cout << "Token deleted" << flush; // TODO... ?
}

void Cell::setFieldOfView(struct Grid fieldOfView)
{
	this->token.setFieldOfView(fieldOfView);
}

