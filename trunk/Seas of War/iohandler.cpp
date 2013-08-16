#include <fstream>

bool readFromFile(string const &filename){
	ifstream file;
	file.open(filename);
	
	file >> _width >> _height
	_tiles = new Tile[_width][_height];
	
	file >> _unitCount;
	if (_unitCount <= 0)
		return false;
	_units = new Unit[_unitCount];
	
	for(int i = 0; !file.eof(), i++)
		file >> _units[i];
		
	file.close();
	
	return true;
}

bool writeToFile(string const &filename){
	ofstream file;
	file.open(filename, ios::trunc);
	
	file << _width << _height;
			
	file << _unitCount;
	
	for (int i = 0; i < size; i++)
		file << _units[i];
	
	file.close();
	
	return true;
}