#include "search.h"

Node *dfs(Tree &src){
	stack<Node *> frontier;
	frontier.push(src.root);
	Node *cur;
	
	while(!frontier.empty()){
		cur 		= new Node(frontier.top()->parent, frontier.top()->state, frontier.top()->r, frontier.top()->c);
		cur->north 	= frontier.top()->north;
		cur->east	= frontier.top()->east;
		cur->south	= frontier.top()->south;
		cur->west	= frontier.top()->west;
		
		if (frontier.size() > src.maxSize)
			src.maxSize = frontier.size();

		frontier.pop();
		src.expanded++;

		if(cur == NULL) break;
		if(cur->state == END) return cur;

		if (cur->north != NULL)
			frontier.push(cur->north);
		if (cur->east != NULL)
			frontier.push(cur->east);
		if (cur->south != NULL)
			frontier.push(cur->south);
		if (cur->west != NULL)
			frontier.push(cur->west);
	}

	return cur;
}

Node *bfs(Tree &src){
	queue<Node *> frontier;
	frontier.push(src.root);
	Node *cur;

	while(!frontier.empty()){
		cur 		= new Node(frontier.front()->parent, frontier.front()->state, frontier.front()->r, frontier.front()->c);
		cur->north 	= frontier.front()->north;
		cur->east	= frontier.front()->east;
		cur->south	= frontier.front()->south;
		cur->west	= frontier.front()->west;

		if (frontier.size() > src.maxSize)
			src.maxSize = frontier.size();

		frontier.pop();
		src.expanded++;

		if(cur == NULL) break;
		if(cur->state == END) return cur;

		if (cur->north != NULL)
			frontier.push(cur->north);
		if (cur->east != NULL)
			frontier.push(cur->east);
		if (cur->south != NULL)
			frontier.push(cur->south);
		if (cur->west != NULL)
			frontier.push(cur->west);
	}

	return cur;
}

Node *findEnd(Tree &src){
	return bfs(src);
}

Node *gbfs(Tree &src){
	Node *end = findEnd(src);

	Node *cur = src.root;
	while(cur != NULL && cur->state != END){
		Node *tmp = minNode(cur, end);
		if (tmp == NULL) break;
		cur = tmp;
		src.maxSize++;
		src.expanded++;
	}

	return cur;
}

/* A* Search
 *
 *
 */
Node *a_star(Tree &src){
	priority_queue<wNode *, vector<wNode *>,greater<wNode *> > frontier;		// stores the path cost

	Node *end = findEnd(src);
	
	wNode *rt;
	rt->cur		= src.root;
	rt->cost	= mDist(src.root, end);
	frontier.push(rt);


	Node *cur;

	while(!frontier.empty()){
		int cCst	= frontier.top()->cost;
		cur 		= new Node(frontier.top()->cur->parent, frontier.top()->cur->state, frontier.top()->cur->r, frontier.top()->cur->c);
		cur->north 	= frontier.top()->cur->north;
		cur->east	= frontier.top()->cur->east;
		cur->south	= frontier.top()->cur->south;
		cur->west	= frontier.top()->cur->west;

		if (frontier.size() > src.maxSize)
			src.maxSize = frontier.size();

		frontier.pop();
		src.expanded++;

		if(cur == NULL) break;
		if(cur->state == END) return cur;

		if (cur->north != NULL){
			wNode *pN = new wNode(cur->north, cCst + mDist(cur->north, end));
			frontier.push(pN);
		}
		if (cur->east != NULL){
			wNode *pE = new wNode(cur->east, cCst + mDist(cur->east, end));
			frontier.push(pE);
		}
		if (cur->south != NULL){
			wNode *pS = new wNode(cur->south, cCst + mDist(cur->south, end));
			frontier.push(pS);
		}
		if (cur->west != NULL){
			wNode *pW = new wNode(cur->west, cCst + mDist(cur->west, end));
			frontier.push(pW);
		}
	}

	return cur;
}

Node *minNode(Node *cur, Node *end){
	Node *vertMin, *hozMin;

	int n, s, w, e, vM, hM;
	n = s = w = e = vM = hM = 9999;

	if (cur->north != NULL)
		n = mDist(cur->north, end);
	if (cur->south != NULL)
		s = mDist(cur->south, end);
	if (cur->west != NULL)
		w = mDist(cur->west, end);
	if (cur->east != NULL)
		e = mDist(cur->east, end);

	if (n < s)
		vertMin = cur->north;
	else
		vertMin = cur->south;

	if (e < w)
		hozMin = cur->east;
	else
		hozMin = cur->west;

	if(vertMin != NULL)
		vM = mDist(vertMin, end);
	if(hozMin != NULL)
		hM = mDist(hozMin, end);

	if (vM == 9999 && hM == 9999)
		return NULL;

	if (vM < hM)
		return vertMin;
	else
		return hozMin;
}

unsigned int mDist(Node *cur, Node *end){
	return abs(cur->r - end->r) + abs(cur->c - end->c);
}
