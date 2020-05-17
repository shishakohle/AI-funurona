#include "player.h"

#ifndef LASTMOVEDIRECTION
#define LASTMOVEDIRECTION

struct lastMoveDirection
{
	int column,row;
};

#endif

#ifndef TOKEN_H
#define TOKEN_H

class Token
{
	public:
		void setTeam(Team);
		Team getTeam(void);
		void setLastMoveDirection(struct lastMoveDirection);
		struct lastMoveDirection getLastMoveDirection(void);
		char asChar(void); // TODO invoke this when printing the board. or is this needed overall?
		static char asChar(enum Team); // TODO: private??
	private:
		enum Team team;
		struct position;
		struct lastMoveDirection lmd;
};

#endif

