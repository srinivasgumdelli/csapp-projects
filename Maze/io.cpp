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

	cout << "Created Base Array and Deciphering Text" << endl;
	
	int curRow = 0;
	int curCol = 0;
	while(input.get(a)){
		if(curRow >= row || curCol >= col)
			resize(row*2, col*2);
		
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

	cout << "Finished Reading File into Maze Array" << endl << endl;
}

void Maze::output(){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++)
			cout << cells[i][j];
		cout << endl;
	}
}

void Maze::resize(int newRow, int newCol){
	int **tmp = new int*[newRow];
	for (int i = 0; i < newCol; i++)
		tmp[i] = new int[newCol];

	for(int i = 0; i < newRow; i++){
		for(int j = 0; j < newCol; j++){
			if (i < row && j < col)
				tmp[i][j] = cells[i][j];
			else
				tmp[i][j] = 9;
		}
	}
	
	remove();
	cells 	= tmp;
	tmp 	= NULL;
	row		= newRow;
	col		= newCol;
}

void Maze::trim(){
	int maxRow = 0, maxCol = 0;
	
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(cells[i][j] != 9){
				maxRow = i;
				maxCol = j;
			}else
				cells[i][j] = WALL;
		}
	}
	
	resize(maxRow+1, maxCol+1);
};

Maze::~Maze(){
	remove();
}

void Maze::remove(){
	delete[] cells;
	cells 	= NULL;
	row 	= 0;
	col 	= 0;
}

coords *Maze::startPosition(){
	coords *sP = new coords();
	sP->x = -1;
	sP->y = -1;
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			if (cells[r][c] == START){
				sP->x = r;
				sP->y = c;
				break;
			}
		}
	}
	return sP;
}
