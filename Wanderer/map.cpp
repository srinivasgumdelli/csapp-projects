/* @file map.cpp
 * @author Kelsey Yuen
 * @date 03-21-2013
 */

#include "map.h"

Map::Map() : _width(25), _height(25) {
	_tiles = new Tile[25][25];
}

Map::Map(int size) : _width(size), _height(size) {
	_tiles = new Tile[size][size];
}

Map::Map(int width, int height) : _width(width), _height(height) {
	_tiles = new Tile[width][height];
}

Map const & Map::operator=(Map &other){
	if (this != &other){
		_clear();
		_copy(other);
	}
	return *this;
}

void Map::_copy(Map &other){
	_width = other._width;
	_height = other._height;
	_tiles = new Tile[_width][_height];
	
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_tiles[x][y] = other._tiles[x][y];
}

void Map::_clear(){
	delete[] _tiles;
	_tiles = NULL;
	
	delete _unit;
	_units = NULL;
	
	_width = 0;
	_height = 0;
	_unitCount = 0;
}

Map::~Map(){
	_clear();
}

Tile * Map::operator()(int x, int y){
	return &(_tiles[x][y]);
}

Tile const * Map::operator()(int x, int y) const{
	return &(_tiles[x][y]);
}

Map Map::readFromFile(string const &filename){
	_clear();
	
	ifstream file;
	file.open(filename);
	
	file >> _width >> _height;
	if (_width <= 0 || _height <= 0)
		return false;
	_tiles = new Tile[_width][_height];
	
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			file >> _tiles[x][y];
	
	file >> _unitCount;
	if (_unitCount <= 0)
		return false;
	_units = new Unit[_unitCount];
	
	for(int i = 0; !file.eof(), i++)
		file >> _units[i];
		
	file.close();
	
	return true;
}

bool Map::writeToFile(string const &filename){
	ofstream file;
	file.open(filename, ios::trunc);
	
	file << _width << _height;
	
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			file << _tiles[x][y];
			
	file << _unitCount;
	
	for (int i = 0; i < size; i++)
		file << _units[i];
	
	file.close();
	
	return true;
}

Tile Map::search(int x, int y){
	int xcoord = 0;
	int ycoord = 0;
	int xcur, ycur;
	
	for (ycur = 0; ycur < _height; ycur++){
		ycoord += _tile[0][ycur].size();
		if (y < ycoord)
			break;
	}
	
	for (xcur = 0; xcur < _width; xcur++){
		ycoord += _tile[xcur][0].size();
		if (x < xcoord)
			break;
	}
	
	return _tile[xcur][ycur];
}

int Map::width() const{
	return _width;
}

int Map::height() const{
	return _height;
}

bool Map::moveUnit(Unit unit, int x, int y){
	for (int i = 0; i < _unitCount; i++){
		if (!checkForCollision(_units[i]))
			return false;
	}

	for (int x = 0; i < _width; i++){
		for (int y = 0; i < _height; i++){
			if (!checkForCollision(_tiles[x][y]))
				return false;
		}
	}
			
	unit.move(x,y);
	return true;
}