/*	@file	conversion.h
 *	@author	Kelsey Yuen
 *	@date	8/15/2013
 */
 
#ifndef CONVERSION_H
#define CONVERSION_H

//const double PI = 3.1415926535897;

#define GRAVITY 		32.174	// ft/s^2
#define FEET2METRES 	0.3048
#define HP2KW			0.746
#define INCH2MM			25.4
#define POUNDS2KG		0.4535924
#define POUND2TON		2240
#define SqFEET2SqMETRES	0.0992903
#define YARDS2FEET		3

float PI(){
	return 4*atan(1);
}

#endif	// CONVERSION_H