#define UNNAMED_PLAYER "unnamed"
#define TOKEN_WHITE 'O'
#define TOKEN_BLACK '#'

#include <iostream>
	using namespace std;

#ifndef TEAM
#define TEAM

enum Team {BLACK, WHITE};

#endif

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		// overloaded constructors for instances of Player
		Player(void);
		Player(string, enum Team);
		// setter for player's name
		void setName(string);
		// setter for player's team
		void setTeam(enum Team);
		// setter for player's amount of left tokens
		void setLeftTokens(int);
		// getter for player's name
		string getName(void);
		enum Team getTeam(void);
		char getToken(void);
	private:
		string name;
		enum Team team;
		int tokensLeft;
};

#endif

