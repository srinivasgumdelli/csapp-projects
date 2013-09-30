#include "search.h"

/* Depth-First Search
 *
 * Create a FIFO frontier and keep expanding the first thing in it.
 * Once you reach the end state, add it's children to the frontier and exit
 */ 
Tree dfs(Tree &src){
	stack<Node> frontier;
	frontier.push(src.root);
	Node *cur;
	
	while(!frontier.empty()){	// pseudocode, fix!	
		cur = frontier.pop();

		frontier.push(cur->north);
		frontier.push(cur->east);
		frontier.push(cur->south);
		frontier.push(cur->west);
		
		if (cur.state == END) break;
	}
}

/* Breadth-First Search
 *
 * Create a LIFO frontier in which every level is expanded before the next level
 * Once you reach the end state, add the next level to the frontier and exit
 */
Tree bfs(Tree &src){
	queue<Node> frontier;
	frontier.push(src.root);
	Node *cur;
	
	while(!frontier.empty()){	// pseudocode, fix!
		cur = frontier.pop();
		
		frontier.push(cur->north);
		frontier.push(cur->east);
		frontier.push(cur->south);
		frontier.push(cur->west);
		
		if (cur.state == END) break;
	}
}