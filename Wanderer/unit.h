/* @file unit.h
 * @author Kelsey Yuen
 * @date 03-22-2013
 */
 
#ifndef UNIT_H
#define UNIT_H

/* UNIT structure
 *
 * Holds all the information necessary to handle a unit in a game
 * Coords (x,y)
 * Unit Type (an enum similar to Affiliation in HeisenGo)
 * Sprite Filename
 * 	the name of the sprite file - I append direction to the end to get the actual filename
 * Heading (which direction it is facing)
 * Collision Width (the collision box, X direction)
 * Collision Length (the collision box, Y direction)
 *
 * LATER ADD
 * 	LIFE
 *	DAMAGE
 */

#include <string>

// Direction defined as angles, counter-clockwise as in a graph
#define EAST 0
#define NORTH 90
#define WEST 180
#define SOUTH 270

class Unit{
	public:
		/* Constructor
		 * Declares a unit without a heading (defaults to north facing)
		 * @param x		The x coord of the unit
		 * @param y		The y coord of the unit
		 * @param filename	The filename of the sprite
		 * @param		The x-height of the collision box
		 * @param		The y-height of the collision box
		 */
		Unit(int x, int y, string filename, int cwidth, int clength);
		
		/* Full Constructor
		 * Declares a unit with a heading
		 * @param x		The x coord of the unit
		 * @param y		The y coord of the unit
		 * @param filename	The filename of the sprite
		 * @param heading	The direction the sprite is facing
		 * @param cwidth	The x-width of the collision box
		 * @param clength	The y-height of the collision box
		 */
		Unit(int x, int y, string filename, int heading, int cwidth, int clength);
		
		/* Equality Operator
		 * @param other		The unit to be checked
		 */
		bool operator==(Unit const &other) const;
		
		/* Inequality Operator
		 * @param other		The unit to be checked
		 */
		bool operator!=(Unit const &other) const;
		
		/* Assignment Operator
		 * @param other		The unit to copy to the current unit
		 * @return		The current unit for assignment chaining
		 */
		Unit const & operator=(Unit const &other) const;
		
		/* Collision Checker
		 * Checks to see if the two objects are in a collision
		 * @param other		The unit to be checked against
		 * @return		Whether the two units are in collision
		 */
		bool checkForCollision(Unit const &other) const;
		
		//!!!!
		/* Tile Collision Checker
		 * Checks to see if the unit is colliding with a impassible tile
		 * @param other		The tile to be checked against
		 * @return		Whether the two are in collision
		 */
		bool checkForCollision(Tile const &other) const;
		
		/* Move Function
		 * @param x		The desired x location
		 * @param y		The desired y location
		 */
		void move(int x, int y);
		
		bool moving;	/* A flag used for the broad phase of collision detection */
		
	private:
		int _x;
		int _y;
		
		string _sprite;
		int _heading;
		
		int _cwidth;
		int _clength;
		
		void _copy(Unit &other);
};

#endif	// UNIT_H