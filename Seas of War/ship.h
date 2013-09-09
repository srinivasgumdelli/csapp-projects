#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <cmath>

#include "conversion.h"
#include "damage.h"

/* Ship Class
 * Rips data from SS reports to produce the class.
 *
 *	Name			Nation
 *	Length Overall	Beam		Draught		Displacement
 *	Main Battery:	
 *		Barrels		Mounts	Mount Type	Diameter	Calibre		Gun Year	Shell Weight	Ammo	Elevation
 *	Secondary:
 *		etc.
 *
 *	Torpedo:
 *		Tube no.	Diameter	Length		Tech Year	Ammo
 *
 *	Armour:
 *		Deck		Sidebelt	Con			Turret		Superstructure
 *
 *	Machinery:
 *		Boiler		Turbine		Top Speed
 *
 *	Flotation		Stability	Steadiness	Sea-keeping
 */
class Ship
{
	public:
		// Default Constructor, empty ship
		Ship();
		
		// Typical Constructor
		Ship(float l, float b, float d, float freeboard, float displacement, float floatation, float stead, float seakeep, float deck, float belt, float con, float spus, float tds, float v);
		
		// Assignment Operator
		Ship const & operator=(Ship const &other);
		
		// Destructor
		~Ship();
		
		turnRadius(float speed);
		
	private:
		string name, nation;
		float length, beam, draught, fB;		// deprecated: displacement
		float gEff;	// deprecated: floatation, steadiness, steadiness, sea-keeping
		
		//float mg_diameter, mg_caliber, mg_year, mg_shellweight, mg_capacity, mg_maxElevation, mg_mountAdj;	// mountAdj computed on file insert
		
		// No torpedo implementation
		
		float T_deck, T_belt, T_con, T_spus, B_tds;
		float top_speed;
		
		float hp;
};

#endif // SHIP_H