#include "player.h"

#ifndef LASTMOVEDIRECTION
#define LASTMOVEDIRECTION

struct lastMoveDirection
{
	int column,row;
};

#endif

#ifndef POSITION
#define POSITION

struct position
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
		void setGridValue(struct position,bool); //TODO: set und get position & update it somewhere
		bool getGridValue(struct position);
		bool getGridBool(void);
		
	private:
		enum Team team;
		struct position pos;
		struct lastMoveDirection lmd;
		bool gridCapturing[5][9];
		bool gridBool;
};

#endif

