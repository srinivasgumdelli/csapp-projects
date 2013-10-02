#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "io.h"
#include <iostream>

#include <queue>

using namespace std;

// A node in the tree has 4 children (1 for each direction), a parent node and an enum value for whether it is the start or end
class Node{
	public:	
		// Default constructor for Node class
		Node(Node *par, int val, int _r, int _c);

		~Node();
				
		Node *parent;
		Node *north;
		Node *east;
		Node *south;
		Node *west;
		int state;
		int r, c;	// kept fot the purpose for finding in checkParent
		bool visited;
};

// A Tree consisting of nodes which can be used to traverse the map with DFS, BFS, etc.
class Tree{
	public:
		/* Creates a Tree Array from a given Maze Array
		 * If Cell not an element of Tree
		 * Then cellNeighbor.child = cell;
		 * cellNeighbor an element of Tree
		 *
		 * A Depth-First Adding Method
		 * Insert the next DIRECTION node as child, if the checkParent function returns false
		 */
		Tree(Maze &src);

		~Tree();

		// Returns the length of the path from the given node and the root node
		unsigned int pathLength(Node *cur);

		Node *root;
		int expanded;
		int maxSize;
		
	private:
		/* Recursive Helper Function called by the constructor
		 * Depth-Based Recursion
		 */
		void createTree(Maze &src, Node *cur);

		/* Checks if the given node is in a parent (direct and indirect) node
		 * This check prevents infinite loops in constructing the tree
		 * Checks by coordinates
		 */
		bool checkParent(Node *cur, int tr, int tc);

		void remove(Node *cur);
};

#endif	// TREE_H_INCLUDED
