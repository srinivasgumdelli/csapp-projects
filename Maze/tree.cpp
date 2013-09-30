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

	cout << "Deciphered Starting Position in Array, (" << sR << ", " << sC << ")" << endl;
	
	root 		= new Node(src.cells[sR][sC]);
	root->r 	= sR;
	root->c 	= sC;
	
	cout << "Created Root Node" << endl;

	createTree(src, root);

	cout << "Correctly created Tree from Maze Array" << endl;
}

/* Recursive Helper Function called by the constructor
 * Depth-Based Recursion
 */
void Tree::createTree(Maze &src, Node *cur){
	if (cur)
		return;

	//cout << "Creating North Child" << endl;
	if (cur->r > 0 && cur->c < src.col-1 && !checkParent(cur, cur->r-1, cur->c)){
		cur->north		= new Node(src.cells[cur->r-1][cur->c]);
		cur->north->r 	= cur->r-1;
		cur->north->c 	= cur->c;
		createTree(src, cur->north);
	}

	//cout << "Creating East Child" << endl;	
	if (cur->c+1 < src.row && cur->r < src.row-1 && !checkParent(cur, cur->r, cur->c+1)){
		cur->east		= new Node(src.cells[cur->r][cur->c+1]);
		cur->east->r 	= cur->r;
		cur->east->c 	= cur->c+1;
		createTree(src, cur->east);
	}
	
	//cout << "Creating South Child" << endl;
	if (cur->r+1 < src.col && cur->c < src.col-1 && !checkParent(cur, cur->r+1, cur->c)){
		cur->south	= new Node(src.cells[cur->r+1][cur->c]);
		cur->south->r = cur->r+1;
		cur->south->c = cur->c;
		createTree(src, cur->south);
	}
	
	//cout << "Creating West Child" << endl;
	if (cur->c > 0 && cur->r < src.row-1 && !checkParent(cur, cur->r, cur->c-1)){
		cur->west	= new Node(src.cells[cur->r][cur->c-1]);
		cur->west->r = cur->r;
		cur->west->c = cur->c-1;
		createTree(src, cur->west);
	}
	
}

/* Checks if the given node is in a parent (direct and indirect) node
 * This check prevents infinite loops in constructing the tree
 * Checks by coordinates
 */
bool Tree::checkParent(Node *cur, int tr, int tc){
	if (cur == NULL) return false;
	if (cur->r == tr && cur->c == tc) return true;
	return checkParent(cur->parent, tr, tc);
}

// Returns the length of the path from the given node and the root node
unsigned int Tree::pathLength(Node *cur){
	if (cur == root) return 0;
	return 1 + pathLength(cur->parent);
}

Tree::~Tree(){
	remove(root);
}

void Tree::remove(Node *cur){
	if (cur == NULL)
		return;

	if (cur->north != NULL)
		remove(cur->north);
	if (cur->east != NULL)
		remove(cur->east);
	if (cur->south != NULL)
		remove(cur->south);
	if (cur->west != NULL)
		remove(cur->west);

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
