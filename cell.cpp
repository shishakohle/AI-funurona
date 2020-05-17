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

bool Cell::getOccupied()
{
	return isOccupied;
}

char Cell::printStatus()
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

Token Cell::getToken()
{
	return token;
}

void Cell::deleteToken()
{
	printf("Token deleted");
}

