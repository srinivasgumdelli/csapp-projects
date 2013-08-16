/*	@file	damage.cpp
 *	@author	Kelsey Yuen
 *	@date	8/15/2013
 */

#include "conversion.cpp"

float shipHitpoints(float displacement, float flotation){
	return 0.025 * displacement + flotation / 50.0;
}

float gunDamage(float diameter){
	return 0.6445 * diameter;
}

float torpedoDamage(float diameter, float length, bool torpex, float tds_beam){
	float c1 = 0.012;
	float density = 0.00165;
	
	float derMod = 1.0;
	if(torpex) derMod = 1.5;
	
	return (PI() * pow(diameter/2.0, 2.0) * length * density * c1) * 4.0 * pow(0.5, tds_beam/3.0) * dermod;
}