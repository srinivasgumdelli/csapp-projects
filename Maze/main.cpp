#include "tree.h"
#include "io.h"
#include "search.h"

#include <iostream>
#include <string>

int main(){
	/*cout << "Enter the filename to open: ";

	string fileName;
	cin >> fileName;

	Maze *M_map 	= new Maze(fileName.c_str());*/
	Maze *M_map 	= new Maze("smallMaze.lay.txt");
	//M_map->output();
	Tree *T_map 	= new Tree(*M_map);
	//T_map->printTree();

	Node *end 	= dfs(*T_map);
	cout << end->state << " takes " << T_map->pathLength(end) << " Nodes" << endl;
}
