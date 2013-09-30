#include "search.h"

/* Depth-First Search
 *
 * Create a FIFO frontier and keep expanding the first thing in it.
 * Once you reach the end state, add it's children to the frontier and exit
 */ 
Node *dfs(Tree &src){
	stack<Node *> frontier;
	frontier.push(src.root);
	Node *cur;

	cout << "Root added to Frontier" << endl;
	
	while(!frontier.empty()){
		cur = frontier.top();
		frontier.pop();

		if(cur) break;

		frontier.push(cur->east);
		frontier.push(cur->south);
		frontier.push(cur->west);
		
		if (cur->state == END) break;
	}

	return cur;
}

/* Breadth-First Search
 *
 * Create a LIFO frontier in which every level is expanded before the next level
 * Once you reach the end state, add the next level to the frontier and exit
 */
Node *bfs(Tree &src){
	queue<Node *> frontier;
	frontier.push(src.root);
	Node *cur;
	
	while(!frontier.empty()){
		cur = frontier.front();
		frontier.pop();
		
		frontier.push(cur->north);
		frontier.push(cur->east);
		frontier.push(cur->south);
		frontier.push(cur->west);
		
		if (cur->state == END) break;
	}

	return cur;
}

Node *findEnd(Tree &src){
	return bfs(src);
}


/* Greedy Best-First Search
 *
 *
 */
Node *gbfs(Tree &src){
	Node *end = findEnd(src);	// pseudocode, fix

	Node *cur = src.root;
	while(cur->state != END)
		cur = minNode(cur, end);

	return cur;
}

/* A* Search
 *
 *
 */
Node *a_star(Tree &src){
	return NULL;
}

/* Minimum Node
 *
 * Returns the child node with the smallest Manhattan Distance
 */
Node *minNode(Node *cur, Node *end){
	Node *vertMin, *hozMin;

	if (mDist(cur->north, end) < mDist(cur->south, end))
		vertMin = cur->north;
	else
		vertMin = cur->south;

	if (mDist(cur->east, end) < mDist(cur->west, end))
		hozMin = cur->east;
	else
		hozMin = cur->west;

	if (mDist(vertMin, end) < mDist(hozMin, end))
		return vertMin;
	else
		return hozMin;
}

/* Manhattan Distance Function
 *
 * Computes the distance in nodes from the end node from the root node
 */
unsigned int mDist(Node *cur, Node *end){
	return abs(cur->r - end->r) + abs(cur->c - end->c);
}
