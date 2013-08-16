/*	@file	ballistics.h
 *	@author	Kelsey Yuen
 *	@date	8/13/2013
 */

#ifndef BALLISTIC_H
#define BALLISTIC_H
 
#include <cmath>
#include "conversion.h"

float toRadians(float a);

float sinD(float a);

float cosD(float a);

/*
 * My empirical formula for calculating muzzle velocity from gun diameter, calibre, shell weight, gun year.
 * Works from 1820-2010 with an error between +10% and -5%. The vast majority is in the ±5% band.
 */
float muzzleVelocity(float diameter, float calibre, float weight, short year);

/*
 * My empirical formula which relates gun range to gun diameter, shell weight, muzzle velocity, and elevation.
 * The prediction is mostly within ±5% of the data and 99% is within ±10% of the prediction
 */
float gunRange(float diameter, float weight, float velocity, float elevation);

/*
 * My empirical formula which relates shell striking velocity to gun range, muzzle velocity, diameter, and calibre.
 * Not extensively tested.
 * Appears to be ±2% error.
 */
float strikeVelocity(float diameter, float calibre, float velocity, float distance);

/*
 * My empirical formula which relates shell density and elevation to the striking angle.
 * The prediction is ±10% accurate.
 */
float obliquity(float diameter, float weight, float elevation);

/*
 * Thompson F-Formula All-Purpose Armour Penetration (US, 1930)
 * T/D  = (1728.04)(W/D^3)[(V/F)Cos(Ob)]^2
 * F = 6[(T/D) - 0.45][Ob^2 + 2000] + 40000
 */
float penetration(float d, float w, float v, float ob, float t);

#endif	// BALLISTCS_H