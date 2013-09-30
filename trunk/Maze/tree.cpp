#include "tree.h"

/* Creates a Tree Array from a given Maze Array
 * If Cell not an element of Tree
 * Then cellNeighbor.child = cell;
 * cellNeighbor an element of Tree
 *
 * A Depth-First Adding Method
 * Insert the next DIRECTION node as child, if the checkParent function returns false
 */
Tree::Tree(Maze &src){
	unsigned int sR = src.startPosition();
	unsigned int sC	= sR & 0x00ff;
	sR				= sR & 0xff00;
	
	root 	= new Node(src.cells[sR][sC]);
	root.r 	= sR;
	root.c 	= sC;
	
	createTree(src, root);
}

/* Recursive Helper Function called by the constructor
 * Depth-Based Recursion
 */
void Tree::createTree(Maze &src, Node *cur){
	if (cur.r-1 > 0 && !checkParent(cur, cur.r-1, cur.c)){
		cur->north	= new Node(src.[cur.r-1][cur.c]);
		cur->north.r = cur.r-1;
		cur->north.c = cur.c;
		createTree(src, cur->north);
	}
	
	if (cur.c+1 < src.row && !checkParent(cur, cur.r, cur.c+1)){
		cur->east	= new Node(src.[cur.r][cur.c+1];
		cur->east.r = cur.r;
		cur->east.c = cur.c+1;
		createTree(src, cur->east);
	}
	
	if (cur.r+1 < src.col && !checkParent(cur, cur.r+1, cur.c)){
		cur->south	= new Node(src.[cur.r+1][cur.c];
		cur->south.r = cur.r+1;
		cur->south.c = cur.c;
		createTree(src, cur->south);
	}
	
	if (cur.c-1 > 0 && !checkParent(cur, cur.r, cur.c-1)){
		cur->west	= new Node(src.[cur.r][cur.c-1];
		cur->west.r = cur.r;
		cur->west.c = cur.c-1;
		createTree(src, cur->west);
	}
	
}

/* Checks if the given node is in a parent (direct and indirect) node
 * This check prevents infinite loops in constructing the tree
 * Checks by coordinates
 */
bool checkParent(Node *cur, int tr, int tc){
	if (cur == NULL) return false;
	if (cur.r == tr && cur.c == tc) return true;
	checkParent(cur->parent, tr, tc);
}

Tree::~Tree(){
	remove(root);
}

void Tree::remove(Node *cur){
	cur == NULL ? return : ;

	cur->north != NULL ? remove(cur->north) : ;
	cur->east != NULL ? remove(cur->east) : ;
	cur->south != NULL ? remove(cur->south) : ;
	cur->west != NULL ? remove(cur->west) : ;

	delete cur;
	cur = NULL;
}

// Default constructor for Node class
Node::Node(int val){
	state 	= val;
	parent 	= NULL;
	north	= NULL;
	east	= NULL;
	south	= NULL;
	west	= NULL;
	r		= 01;
	c		= -1;
}