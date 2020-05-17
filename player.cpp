#include "player.h"

// overloaded constructors for instances of Player

Player::Player(void)
{
	this->setName(UNNAMED_PLAYER);
	this->setLeftTokens(22);
}

Player::Player(string name, enum Team team)
{
	this->setName(name);
	this->setTeam(team);
}

// setter for player's name
void Player::setName(string name)
{
	!name.empty() ? this->name=name : this->name = UNNAMED_PLAYER;
}

// setter for player's team
void Player::setTeam(enum Team team)
{
	this->team = team;
}

// setter for player's amount of left tokens
void Player::setLeftTokens(int tokensLeft)
{
	this->tokensLeft = tokensLeft;
}

// getter for player's name
string Player::getName(void)
{
	return this->name;
}

enum Team Player::getTeam(void)
{
	return this->team;
}

int Player::getLeftTokens(void)
{
	return this->tokensLeft;
}

// get player's token // TODO: needed?
char Player::getToken(void)
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

