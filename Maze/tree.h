#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "io.h"

// Converts the array created in the Maze class into a 4-nary  Tree which can be used to traverse the map with DFS, BFS, etc.
class Tree{
	public:
		Tree(Maze &src);
		~Tree();
		
		Node *root;
		
	private:
		void createTree(Maze &src, Node *cur);
		bool checkParent(Node *cur, int tr, int tc);
		void remove(Node *cur);
	
		// A node in the tree has 4 children (1 for each direction), a parent node and an enum value for whether it is the start or end
		class Node{
			public:	
				Node(int val);
				
			private:
				Node *parent;
				Node *north;
				Node *east;
				Node *south;
				Node *west;
				NODEINFO state;
				int r, c;	// kept fot the purpose for finding in checkParent
		};
};

#endif;	// TREE_H_INCLUDED