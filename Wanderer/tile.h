/* @file Tile.h
 * @author Kelsey Yuen
 * @date 03-21-2013
 */

#ifndef TILE_H
#define TILE_H 
 
#include <string>

#include "rgbacolor.h"
#define TILE_SIZE 20
 
/*
 * TILE structure
 * Makes up MAP structure
 * Holds
 * 	Color
 *	Passability
 *	Light Condition
 *	Who is my neighbour?	<- If not another map, 0, otherwise the filename
 */
class Tile{
	public:
		/* Default Constructor
		 * Creates a white passable and lighted tile that has no neighbor
		 */
		Tile();
		
		/* Color Constructor
		 * Creates a tile with the given colors and is passable, lighted with no neighbor
		 * @param color		RGBAColor of the new tile
		 */
		Tile(RGBAColor color);
		
		/* Normal Constructor
		 * Creates a tile with given color, passability, and light condition, but it has no neighbor
		 * @param color		RGBAColor of the new tile
		 * @param passable	Passability of the new tile
		 * @param light		Light condition of the new tile
		 */
		Tile(RGBAColor color, bool passable, bool light);
		
		/* Everything Constructor
		 * Everything is custom
		 * @param color		RGBAColor of the new tile
		 * @param passable	Passability of the new tile
		 * @param light		Light condition of the new tile
		 * @param neighbor	The neighbor file of the new tile
		 */
		Tile(RGBAColor color, bool passable, bool light, string neighbor);
		
		/* Assignment Operator
		 * @param other		Tile to copy to the current tile
		 * @return		The current tile for assignment chaining
		 */
		Tile const & operator=(Tile const &other);
		
		/* Destructor
		 * Invoked by system
		 */
		~Tile();
		
		/* Equality Operator
		 * @param other		Tile to be checked
		 */
		bool operator==(Tile const &other) const;
		
		/* Inequality Operator
		 * @param other		Tile to be checked
		 */
		bool operator!=(Tile const &other) const;
		
		/* @return		Size of the tile */
		int size() const;
		
		/* @return		Passability of the tile */
		bool passable() const;
		
		/* @return		Light condition of the tile */
		bool light() const;
		
		/* @return		Neighbor of the tile */
		string portal() const;
		
		
	private:
		/* Holds the size in pixels of the tile */
		int size;
		
		RGBAColor color;
		
		bool passability;
		
		bool illumination;
		
		string neighbor;	//<- empty string for now! DO NOT IMPLEMENT YET!
		
		void _copy(Tile &other);
};

#endif	TILE_H