#ifndef SEARCH_H
#define	SEARCH_H

#include "maze.h"
#include "tree.h"
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
  
Tree dfs(Tree &src);
Tree bfs(Tree &src);
Tree gbfs(Tree &src);
Tree a_star(Tree &src);

#endif	// SEARCH_H