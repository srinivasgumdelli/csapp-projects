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
	coords *tmp 		= src.startPosition();
	int sR = tmp->x;
	int sC	= tmp->y;
	depth = 0;

	cout << "Deciphered Starting Position in Array, (" << sR+1 << ", " << sC+1 << ")" << endl;
	
	root 		= new Node(src.cells[sR][sC], sR, sC);
	
	cout << "Created Root Node" << endl;

	createTree(src, root);

	cout << "Created Tree with depth " << depth << " from Maze Array" << endl << endl;
}

/* Recursive Helper Function called by the constructor
 * Depth-Based Recursion
 */
void Tree::createTree(Maze &src, Node *cur){
	if(cur == NULL)
		return;

	Node* tmpN = NULL;
	Node* tmpE = NULL;
	Node* tmpS = NULL;
	Node* tmpW = NULL;

	tmpN = src.cells[sR-1][sC];
	tmpE = src.cells[sR][sC+1];
	tmpS = src.cells[sR+1][sC];
	tmpW = src.cells[sR][sC-1];


	
	
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
Node::Node(int val, int _r, int _c) : state(val), r(_r), c(_c) {
	parent 	= NULL;
	north	= NULL;
	east	= NULL;
	south	= NULL;
	west	= NULL;
}

void Tree::printTree(){
	if(!root) return;
	queue<Node *> cur;
	queue<int> level;
	cur.push(root);
	int plev = 1;
	level.push(plev);
	while(!cur.empty()){
		int clev = level.front();
		level.pop();
		if(plev < clev){
			cout << endl;
			plev = clev;
		}
		Node *p = cur.front();
		cout << p->state;
		
		cur.push(p->north);
		level.push(clev+1);

		cur.push(p->east);
		level.push(clev+1);

		cur.push(p->south);
		level.push(clev+1);

		cur.push(p->west);
		level.push(clev+1);
	}
	cout << endl;
}
