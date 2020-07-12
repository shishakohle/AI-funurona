#include <vector>

#ifndef NODE_H
#define NODE_H


#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {North, East, South, West, Northeast, Southeast, Southwest, Northwest, InvalidDirection};
enum CaptureOption {Approach, Withdraw, Unset};

static const map <string, Direction> directionMap
{
	{ "N" , North},
	{ "NE", Northeast},
	{ "E" , East},
	{ "SE", Southeast},
	{ "S" , South},
	{ "SW", Southwest},
	{ "W" , West},
	{ "NW", Northwest}
};

#endif

#ifndef COMMAND_H
#define COMMAND_H

enum Command {
	Invalid, // TODO replace by InvalidCommand
	Skip,
	Move,
	Help,
	Restart,
	Quit,
	Rules
};


static const map <string, Command> commandMap
{
	{ "SKIP",    Skip },
	{ "HELP",    Help },
	{ "RESTART", Restart },
	{ "QUIT",    Quit},
	{ "EXIT",    Quit},
	{ "BYE",     Quit},
	{ "RULES",   Rules}
};

#endif


#ifndef USERACTION_H
#define USERACTION_H

struct Useraction
{
	struct position  		start;
	struct position  		end;
	enum   Direction		dir;
	enum   Command 			command;
	enum   CaptureOption	captureOption;
};

#endif

class Node
{
	private:
		Board currentBoard; // TODO some sort of data we store to each node of the tree
		Useraction userAction;
		vector<Node> children;
		float cost;
		float alpha;
		float beta;
	public:
		void setBoard(Board value){
			this->currentBoard = value;
		}
		void setUseraction(Useraction value){
			this->userAction = value;
		}
		void setCost(float value){
			this->cost = value;
		}
		void setAlpha(float value){
			this->alpha = value;
		}
		void setBeta(float value){
			this->beta = value;
		}
		Board getBoard(){
			return this->currentBoard;
		}
		float getCost(){
			return this->cost;
		}
		void addChild(Node child)
		{
			children.push_back(child);
		}
		vector<Node> getChildren(){
			return this->children;
		}
};

#endif

#ifndef TREE_H
#define TREE_H

class Tree
{
	private:
	
	public:
		Node root;

};

#endif

