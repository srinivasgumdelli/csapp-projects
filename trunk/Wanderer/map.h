/* @file map.h
 * @author Kelsey Yuen
 * @date 03-21-2013
 */

#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include "unit.h"

/*	MAP structure
 *	Made up of small tiles
 *	Structure Looks like this:
 *	WIDTH HEIGHT TILE TILE TILE TILE COUNT UNIT UNIT SOUND_FILE_NAME
 */

class Map{
	public:
		/* Default Constructor
		 * Constructs a square map with 25 tiles or 500x500 pixels
		 */
		Map();
		
		/* Square Constructor
		 * Constructs a square map with the given number of tiles
		 * @param size		The size of the map in size x size tiles
		 */
		Map(int size);
		
		/* Non-uniform Constructor
		 * Constructs a map with the desired shape
		 * @param width
		 * @param height
		 */
		Map(int width, int height);
		
		/* Assignment Operator
		 * @param other		Map to copy into the current map
		 * @return 		The current map for assignment chaining
		 */
		Map const & operator=(Map &other);
		
		/* Destructor
		 * Invoked by system
		 */
		~Map();
		
		/* Non-const tile access operator.
		 * Gets a pointer to the tile at the given coord in the map
		 * (0,0) is the upper left corner. This pointer allows the image to be changed
		 * @param x		The x-coord (in array) for the tile pointer to be grabbed from
		 * @param y		The y-coord (in array) for the tile pointer to be grabbed from
		 * @return		A Tile at the given coordinates
		 */
		Tile *operator()(int x, int y);
		
		/* Const tile access operator, const version of the previous opreator().
		 * Doesn't allow the map to b changed via the pointer
		 * @param x		The x-coord (in array) for the tile pointer to be grabbed from
		 * @param y		The y-coord (in array) for the tile pointer to be grabbed from
		 * @return		A Tile at the given coordinates
		 */
		Tile const *operator()(int x, int y) const;
		
		/* Reads in a Map from a file. 
		 * Overwrites any current content in the Map.
		 * @param filename	The name of the file to be read from
		 * @return		Whether the map was successfully read in or not
		 */
		bool readFromFile(string const &filename);
		
		/* Writes a Map to a file
		 * @param filename	The name of the file to be written to
		 * @return		Whether the file was written successfully or not
		 */
		bool writeToFile(string const &filename);
		
		/* Returns the tile at the location	*/
		Tile search(int x, int y);
		
		/* @return		The width of the current map	*/
		int width() const;
		
		/* @return		The height of the current map	*/
		int height() const;
		
		/* Unit Move Command
		 * Finds the desired unit within the unit list and moves it to the desired location
		 * @param unit		The unit that is moving
		 * @param x		The desired x location
		 * @Param y		The desired y location
		 * @return		Whether the unit could move to the desired location
		 */
		bool moveUnit(Unit unit, int x, int y);
		
	private:
		/* Holds the size of the map structure in tiles*/
		int _width;
		int _height;
		int _unitCount;
		
		Tile *_tiles;
		Unit *_units;
		
		void _copy(Map &other);
		void _clear();
}

#endif	// MAP_H