/* @file Tile.cpp
 * @author Kelsey Yuen
 * @date 03-21-2013
 */
 
#include "tile.h"

Tile::Tile() : size(TILE_SIZE), passability(true), illumination(true), neighbor('') {
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	color.allpha = 255;
}

Tile::Tile(RGBAColor c) : size(TILE_SIZE), passability(true), illumination(true), neighbor('') {
	color = c;
}

Tile::Tile(RGBAColor c, bool p, bool l) : size(TILE_SIZE), neighbor('') {
	color = c;
	passability = p;
	illumination = l;
}

Tile::Tile(RGBAColor c, bool p, bool l, string n) : size(TILE_SIZE) {
	color = c;
	passability = p;
	illumination = l;
	neighbor = n;
}

Tile const & Tile::operator=(Tile const &other){
	if (this != &other)
		_copy(other);
	return *this;
}

void Tile::_copy(Tile const &other){
	size = other.size;
	color = other.color;
	passability = other.passability;
	illumination = other.illumination;
	neighbor = other.neighbor;
}

Tile::~Tile(){
	// Nothing allocated, nothing deallocated
}

bool Tile::operator==(Tile const &other) const{
	return size == other.size && color == other.color && passability == other.passability && illumination == other.illumination && neighbor == other.neighbor;
}

bool Tile::operator!=(Tile const &other) const{
	return !(*this == other);
}

Tile::size() const{
	return size;
}

Tile::passable() const{
	return passability;
}

Tile::light() const{
	return light;
}

Tile::portal() const{
	return neighbor;
}