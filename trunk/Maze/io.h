#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>

using namespace std;

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
		
		// Construct from file given
		Maze(const char *filename);	
		
		// Destructor
		~Maze();

		// Prints the array to terminal
		void output();
		
		// Returns coordinates a coords struct
		coords *startPosition();
		
		int **cells;
		size_t	col;
		size_t	row;
		
	private:
		// Resizes the array to the new dimensions
		void resize(int newRow, int newCol);

		// Trims the maze to best fit size
		void trim();

		void remove();
};
 
#endif	// IO_H
