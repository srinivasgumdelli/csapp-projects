#include "io.h"

Maze::Maze() : row(0), col(0) {
}

Maze::Maze(const char *filename){
	char	a;
	ifstream	input(filename);
	
	cells = new int*[1];
	for (int i = 0; i < 1; i++)
		cells[i] = new int[1];

	row = 1;
	col = 1;

	cout << "Created Base Array" << endl;
	
	int curRow = 0;
	int curCol = 0;
	while(input.get(a)){
		//cout << "Check for Resize" << endl;
		if(curRow >= row || curCol >= col)
			resize(row*2, col*2);
		
		//cout << "Deciphering Text" << endl;
		//cout << a << " ";

		if (a == '\n'){
			curRow++;
			curCol = 0;
			continue;
		}

		switch(a){
			case '%':
				cells[curRow][curCol] = WALL;
				break;
			case ' ':
				cells[curRow][curCol] = OPEN;
				break;
			case 'P':
				cells[curRow][curCol] = START;
				break;
			case '.':
				cells[curRow][curCol] = END;
				break;
			//default:		// Default does nothing, don't want to create walls on Windows style '\r\n's '\n'
				//cells[curRow][curCol] = WALL;
		}
			
		curCol++;
	}
	
	input.close();
	input.clear();

	cout << "Trimming from " << row << ", " << col;
	
	trim();

	cout << " to " << row << ", " << col << endl;

	cout << "Correctly read file in Maze Array" << endl;
}

void Maze::resize(int newRow, int newCol){
	if(row < 1 || col < 1){
		delete cells;
		cells = new int*[1];
		for (int i = 0; i < 1; i++)
			cells[i] = new int[1];

		row = col = 1;
		return;
	}
	
	int **tmp = new int*[newRow];
	for (int i = 0; i < newCol; i++)
		tmp[i] = new int[newCol];

	for(int i = 0; i < newRow; i++){
		for(int j = 0; j < newCol; j++){
			if (i < row && j < col)
				tmp[i][j] = cells[i][j];
			else
				tmp[i][j] = -1;
		}
	}
	
	delete[] cells;
	cells 	= tmp;
	tmp 	= NULL;
	row		= newRow;
	col		= newCol;
}

// Trims the maze to best fit size and fills empty border cells with wall state
void Maze::trim(){
	int maxRow = 0, maxCol = 0;
	
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if( cells[i][j] == -1){
				if (maxRow < i)
					maxRow = i;
				if (maxCol < j)
					maxCol = j;

				cells[i][j] = WALL;
			}
		}
	}
	
	resize(maxRow, maxCol);
};

Maze::~Maze(){
	delete[] cells;
	row = 0;
	col = 0;
}

/*const Maze& operator=(const Maze &source){
	delete[] cells;
	cells 	= new int[source->row][source->col];
	row 	= source->row;
	col 	= source->col;
	
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++)
			cells[r][c] = source.cells[r][c];
}*/
