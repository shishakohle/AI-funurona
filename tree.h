#include <vector>

#ifndef NODE_H
#define NODE_H

class Node
{
	private:
		int someValue; // TODO some sort of data we store to each node of the tree
		vector<Node *> children;
	public:
		void addChild(Node *child)
		{
			children.push_back(child);
		}
};

#endif

#ifndef TREE_H
#define TREE_H

class Tree
{
	private:
		Node root;
	
	public:
};

#endif

