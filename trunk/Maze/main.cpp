#include "tree.h"
#include "io.h"
#include "search.h"

#include <iostream>
#include <string>

int main(){
	cout << "Enter the filename to open: ";

	string fileName;
	cin >> fileName;

	Maze *M_map 	= new Maze(fileName.c_str());
	//Maze *M_map 	= new Maze("smallMaze.lay.txt");
	M_map->output();
	cout << endl;

	Tree *T_map 	= new Tree(*M_map);


	cout << "Uninformed:" << endl;

	// DFS
	Node *dfsEnd 	= dfs(*T_map);
	cout << "Depth-First Search has a depth and path cost of " << T_map->pathLength(dfsEnd);
	cout << ", expanded " << T_map->expanded << " nodes";
	cout << " with max frontier size of " << T_map->maxSize << " nodes" << endl;
	T_map->expanded = 0;
	T_map->maxSize = 0;
	// Add output of number of nodes expanded and max size of frontier
	// Print path

	// BFS
	Node *bfsEnd	= bfs(*T_map);
	cout << "Breadth-First Search has a depth and path cost of " << T_map->pathLength(bfsEnd);
	cout << ", expanded " << T_map->expanded << " nodes";
	cout << " with max frontier size of " << T_map->maxSize << " nodes" << endl;
	T_map->expanded = 0;
	T_map->maxSize = 0;

	// GBFS
	Node *gbfsEnd	= gbfs(*T_map);
	cout << "Greedy Best-First Search has a depth and path cost of " << T_map->pathLength(gbfsEnd);
	cout << ", expanded " << T_map->expanded << " nodes";
	cout << " with max frontier size of " << T_map->maxSize << " nodes";
	T_map->expanded = 0;
	T_map->maxSize = 0;

	if (gbfsEnd->state == END)
		cout << " and reaches the goal" << endl;
	else
		cout << " and doesn't reach the goal" << endl;

	/*
	// A*
	Node *astarEnd 	= a_star(*T_map);
	cout << "A* search has a depth and path cost of " << T_map->pathLength(astarEnd);
	cout << ", expanded " << T_map->expanded << " nodes";
	cout << " with max frontier size of " << T_map->maxSize << " nodes" << endl;
	T_map->expanded = 0;
	T_map->maxSize = 0;*/
}
