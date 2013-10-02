#include "tree.h"

Tree::Tree(Maze &src){
	expanded 	= 0;
	maxSize		= 0;

	coords *tmp = src.startPosition();
	int sR 		= tmp->x;
	int sC		= tmp->y;

	cout << "Deciphered Starting Position, " << src.cells[sR][sC] << ", in Array (" << sR+1 << ", " << sC+1 << ")" << endl;
	
	root = new Node(NULL, src.cells[sR][sC], sR, sC);
	
	cout << "Created Root Node" << endl;

	createTree(src, root);

	cout << "Created Tree" << endl << endl;
}

void Tree::createTree(Maze &src, Node *cur){
	if(cur == NULL)
		return;

	int r = cur->r;
	int c = cur->c;

	Node* tmpN = NULL;
	Node* tmpE = NULL;
	Node* tmpS = NULL;
	Node* tmpW = NULL;

	if (r-1 >= 0 && !checkParent(cur, r-1, c))
		tmpN = new Node(cur, src.cells[r-1][c], r-1, c);
	if (c+1 < src.col && !checkParent(cur, r, c+1))
		tmpE = new Node(cur, src.cells[r][c+1], r, c+1);
	if (r+1 < src.row && !checkParent(cur, r+1, c))
		tmpS = new Node(cur, src.cells[r+1][c], r+1, c);
	if (c-1 >= 0 && !checkParent(cur, r, c-1))
		tmpW = new Node(cur, src.cells[r][c-1], r, c-1);

	/*if (tmpN != NULL && tmpN->state != WALL)
		cout << tmpN << " " << tmpN->state << " (" << tmpN->r+1 << ", " << tmpN->c+1 << ")" << endl;
	if (tmpE != NULL && tmpE->state != WALL)
		cout << tmpE << " " << tmpE->state << " (" << tmpE->r+1 << ", " << tmpE->c+1 << ")" << endl;
	if (tmpS != NULL && tmpS->state != WALL)
		cout << tmpS << " " << tmpS->state << " (" << tmpS->r+1 << ", " << tmpS->c+1 << ")" << endl;
	if (tmpW != NULL && tmpW->state != WALL)
		cout << tmpW << " " << tmpW->state << " (" << tmpW->r+1 << ", " << tmpW->c+1 << ")" << endl;
	cout << endl;*/

	if (tmpN != NULL && tmpN->state != WALL){
		cur->north = tmpN;
		createTree(src, tmpN);
	}
	if (tmpE != NULL && tmpE->state != WALL){
		cur->east = tmpE;
		createTree(src, tmpE);
	}
	if (tmpS != NULL && tmpS->state != WALL){
		cur->south = tmpS;
		createTree(src, tmpS);
	}
	if (tmpW != NULL && tmpW->state != WALL){
		cur->west = tmpW;
		createTree(src, tmpW);
	}
}

bool Tree::checkParent(Node *cur, int tr, int tc){
	if (cur == NULL)
		return false;
	if (cur->r == tr && cur->c == tc)
		return true;
	return checkParent(cur->parent, tr, tc);
}

unsigned int Tree::pathLength(Node *cur){
	if (cur == NULL || cur == root || cur->parent == NULL) return 0;
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

Node::Node(Node * par, int val, int _r, int _c) : parent(par), state(val), r(_r), c(_c) {
	north	= NULL;
	east	= NULL;
	south	= NULL;
	west	= NULL;
	visited = false;
}

Node::~Node(){
	parent	= NULL;
	north	= NULL;
	east	= NULL;
	south	= NULL;
	west	= NULL;
	r		= 0;
	c 		= 0;
	visited = false;
	state	= WALL;
}
