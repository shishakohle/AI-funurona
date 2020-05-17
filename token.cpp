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

