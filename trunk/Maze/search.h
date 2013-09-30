#ifndef SEARCH_H
#define	SEARCH_H

#include "io.h"
#include "tree.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <assert.h>

using namespace std;

/*	A layout where spaces are open paths, % are walls
 *	P = starting position, . =  ending position
 *	Uniform cost
 *	
 *	Depth-first search
 *	Breadth-first search
 *	Greedy best-first search
 *	A* search
 *
 *	For greedy and A* search
 *	Use the Manhattan distance from the current position to the goal
 *	As the heuristic function
 */
 
 /*	Include
  *	The solution and its path cost
  *	Number of nodes expanded
  *	Maximum tree depth searched
  *	Maximum size of the frontier
  */
  
Node *dfs(Tree &src);
Node *bfs(Tree &src);
Node *gbfs(Tree &src);
Node *a_star(Tree &src);

Node *findEnd(Tree &src);
Node *minNode(Node *cur, Node *end);
unsigned int mDist(Node *cur, Node *end);

#endif	// SEARCH_H
