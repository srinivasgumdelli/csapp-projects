#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>

using namespace std;

//enum NODEINFO { OPEN, WALL, EXPLORED, START, END };
enum { OPEN, WALL, EXPLORED, START, END };

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
		
		// Returns coordinates in 1 int as xxxxyyyy format
		inline int startPosition(){
			for(unsigned long r = 0; r < row; r++)
				for(unsigned long c = 0; c < col; c++)
					if (cells[r][c] == START)
						return (r << 4) + c;
			return -1;
		}
		
		int **cells;
		size_t	col;
		size_t	row;
		
	private:
		void resize(int newRow, int newCol);
		void trim();
};
 
#endif	// IO_H
