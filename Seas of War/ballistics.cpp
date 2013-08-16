/*	@file	ballistic.cpp
 *	@author	Kelsey Yuen
 *	@date	08/13/2013
 */
 
#include "ballistics.h"

float toRadians(float a){
	return a * M_PI / 180.0;
}

float sinD(float a){	// sin with degrees
	return sin(toRadians(a));
}

float cosD(float a){
	return cos(toRadians(a));
}

float muzzleVelocity(float diameter, float calibre, float weight, short year){
	float c;
	if (year >  2000) c1 = 0.40;
	if (year <= 2000) c1 = 0.42;
	if (year <= 1980) c1 = 0.60;
	if (year <= 1950) c1 = 0.65;
	if (year <= 1930) c1 = 0.68;
	if (year <= 1900) c1 = 1.00;
	if (year <= 1880) c1 = 1.40;
	if (year <= 1860) c1 = 6.00;

	c *= 0.1*(year - 1870) + 14.0;

	return sqrt(pow(diameter, 3.0) * calibre * power(10.0, 6.0) / (c * weight));
}

float gunRange(float diameter, float weight, float velocity, float elevation){
	float xparabolic = pow(velocity, 2.0) * sinD(elevation) * cosD(elevation) / GRAVITY;

	float c4 = cosD(1.3 * pow(elevation, 0.78)) * velocity/3000.0 * sinD(elevation + 9.0);
	float c3 = 0.021758 * elevation + 0.082838;
	float ratio = (c3 * (0.4 + weight/pow(diameter, 3.0)) + 0.135) / c4;

	return xparabolic * ratio;
}

float strikeVelocity(float diameter, float calibre, float velocity, float distance){
	float c2 = 1.05;	// muzzle velocity corrective factor

	float c1 = pow(800.0/(diameter * calibre), 1.0/3.0);	// muzzle energy corrective factor
	float dis = distance / 5000;	// distance interval as a fraction of 5000 yards

	return c1*(19.428*pow(dis, 2.0) - 267.71*dis + (c2 * velocity));
}

float obliquity(float diameter, float weight, float elevation){
    float c;
    if (elevation > 20.0)
        c = pow(cosD(elevation), 5.0) - 0.1;
    else
        c = cosD(elevation);

    c = 1.0 + 0.15 * c * pow((sinD(elevation) + 0.95), 5.0);

    return c * elevation * pow(0.6592 / (weight / pow(diameter, 3.0)), 0.3);
}

float penetration(float d, float w, float v, float ob, float t){
    float f = 6.0 * ((t/d) - 0.45) * (pow(ob, 2.0) + 2000.0) + 40000.0;

    return 1728.04 * (w/pow(d, 3.0)) * pow((v/f) * cosD(ob), 2.0);
}
