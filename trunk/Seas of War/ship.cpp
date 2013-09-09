#include "ship.h"

Ship::Ship() : name("null"), nation("null") {
	length 		= 300;
	beam 		= 50;
	draught		= 23;
	fB			= 20;

	gEff		= 0;

	T_deck 		= 0;
	T_belt 		= 0;
	T_con 		= 0;
	T_spus 		= 0;
	B_tds 		= 0;
	
	top_speed 	= 0;
	hp 			= shipHipoints(0, 0);
}

Ship::Ship(float l, float b, float d, float displacement, float freeboard, float floatation, float stead, float seakeep, float deck, float belt, float con, float spus, float tds, float v){
	length		= l;
	beam		= b;
	draught		= d;
	fB			= freeboard;
	
	gEff		= stead * seakeep;
	
	T_deck		= deck;
	T_belt		= belt;
	T_con		= con;
	T_spus		= spus;
	B_tds		= tds;
	
	top_speed	= v;
	hp 			= shipHitpoints(displacement, floatation);
}

Ship Ship::const &operator=(Ship const &other){
	name.strcopy(other.name);		// ??
	nation.strcopy(other.nation);	// ??
	length 		= other.length;
	beam 		= other.beam;
	draught		= other.draught;
	fB			= other.fB;
	
	gEff		= other.stabAdj;
	
	T_deck 		= other.T_deck;
	T_belt 		= other.T_belt;
	T_con 		= other.T_con;
	T_spus		= other.T_spus;
	B_tds		= other.B_tds;
	
	top_speed	= other.top_speed;
	hp			= other.hp;
}

Ship::~Ship(){
	delete this;
}

float Ship::turnRadius(float speed){
	// turning radius (yds) = 4 x Loa / 3 or 60 x Loa / (3xV)
	return 60.0 * length / (3.0 * speed);
}