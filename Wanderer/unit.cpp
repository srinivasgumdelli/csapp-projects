/* @file unit.cpp
 * @author Kelsey Yuen
 * @ date 03-22-2013
 */

#include "unit.h"

Unit::Unit(int x, int y, string filename, int cwidth, int clength) : _x(x), _y(y), _sprite(filename), _heading(NORTH), _cwidth(cwidth), _clength(clength), moving(false) {
}

Unit::Unit(int x, int y, string filename, int heading, int cwidth, int clength) : _x(x), _y(y), _sprite(filename), _heading(heading), _cwidth(cwidth), _clength(clength), moving(false) {
}

bool Unit::operator==(Unit const &other) const{
	return _x == other._x && _y == other._y && _sprite == other._sprite && _heading == other._heading && _cwidth == other._cwidth && _clength == other._clength;
}

bool Unit::operator!=(Unit const &other) const{
	return !(*this == other);
}

Unit const & Unit::operator=(Unit const &other){
	if (this != &other)
		_copy(other);
	return *this;
}

void Unit::_copy(Unit const &other){
	_x = other._x;
	_y = other._y;
	_sprite = other._sprite;
	_cwidth = other._cwidth;
	_clength = other._clength;
}

bool Unit::checkForCollision(Unit const &other) const{
	return (_x + _cwidth < other._x) || (_y + _clength < other._y) || (other._y + other._clength < _y) || (other._x + other._cwidth < _x);
}

bool Unit::checkForCollision(Tile const &other) const{
	// TBD
}

void move(int x, int y){
	_x = x;
	_y = y;
}