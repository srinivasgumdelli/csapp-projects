#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>

using namespace std;

//enum NODEINFO { OPEN, WALL, EXPLORED, START, END };
enum { OPEN = 0, WALL, START, END };

typedef struct{
	int x;
	int y;
} coords;

// Converts a txt file into an array containing the whole map
class Maze{
	public:
		// Default Constructor
		Maze();
		
		// Construct from file
		Maze(const char *filename);	
		
		// Destructor, 
		~Maze();
		
		// Assignment Operator
		//const Maze &operator=(const Maze &source);

		// Prints the array to terminal
		void output();
		
		// Returns coordinates in 1 int as xxxxyyyy format
		coords *startPosition();
		
		int **cells;
		size_t	col;
		size_t	row;
		
	private:
		void resize(int newRow, int newCol);
		void trim();
		void remove();
};
 
#endif	// IO_H
