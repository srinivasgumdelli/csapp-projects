#ifndef SEARCH_H
#define	SEARCH_H

#include "io.h"
#include "tree.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <assert.h>

using namespace std;

// Stores Node as well as it's cost
struct wNode{
	int cost;
	Node *cur;
	int operator<(const wNode& other){ return cost > other.cost; };
	wNode(Node *cr, int cst) : cost(cst), cur(cr){}
};	// weighted Node
  
/* Depth-First Search
 * Create a FIFO frontier and keep expanding the first thing in it.
 * Once you reach the end state, add it's children to the frontier and exit
 */ 
Node *dfs(Tree &src);

/* Breadth-First Search
 * Create a LIFO frontier in which every level is expanded before the next level
 * Once you reach the end state, add the next level to the frontier and exit
 */
Node *bfs(Tree &src);

/* Greedy Best-First Search
 * Decides direction to head based on which direction has the
 * minimum manhattan distance to the end node
 * Compares the r and c values of the current node to that of the end node to do so
 */
Node *gbfs(Tree &src);
Node *a_star(Tree &src);

Node *findEnd(Tree &src);

/* Minimum Node
 * Returns the child node with the smallest Manhattan Distance
 */
Node *minNode(Node *cur, Node *end);

/* Manhattan Distance Function
 * Computes the distance in nodes from the end node from the root node
 */
unsigned int mDist(Node *cur, Node *end);

#endif	// SEARCH_H
