#include <string>
#include <cmath>

/* Ship Class
 * Rips data from SS reports to produce the class.
 *
 *	Name			Nation
 *	Length Overall	Beam		Draught
 *	Main Battery:	
 *		Barrels		Mounts	Mount Type	Diameter	Calibre		Gun Year	Shell Weight	Ammo	Elevation
 *	Secondary:
 *		etc.
 *	Tertiary:
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
		
		// Assignment Operator
		Ship const & operator=(Ship const &other);
		
		// Destructor
		~Ship();
		
		
	private:
		string name, nation;
		float length_overall, beam, draught;
		float flotation, stability, steadiness, sea-keeping;
		
		
}