#include "player.h"

#ifndef LASTMOVEDIRECTION
#define LASTMOVEDIRECTION

struct lastMoveDirection
{
	int column,row;
};

#endif

#ifndef POSITION_H
#define POSITION_H

struct position // TODO: upper case!
{
	int column,row;
};

#endif

#ifndef GRID_H
#define GRID_H

struct Grid
{
	bool gridPosition[5][9];
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
		bool getGridBool(void);
		void setFieldOfView(struct Grid);
		struct Grid getFieldOfView(void);
		
	private:
		enum Team team;
		struct lastMoveDirection lmd;
		bool gridCapturingToken[5][9]; // TODO: abolish
		struct Grid fieldOfView;
		//bool gridBool; // TODO: needed? what for? ~ingo
};

#endif

