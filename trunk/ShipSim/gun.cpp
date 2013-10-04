#include "gun.h"

/***** What follows is the Guns section ****/

Gun::Gun(const Gun &other){
	copyB(other);
}

const Gun& Gun::operator=(const Gun &src){
	if(this != &src)
		copyB(src);
	return *this;
}

void copyB(const Gun &src){
	loc 		= src.loc;
	beam		= src.beam;
	echelon		= src.echelon;
	g			= src.g;
	head		= src.head;
}

float Gun::Dbarb(float barrelMounts, float gunDiameter){
	float d = gunDiameter / (IN2CM * 10.);
	return (barrelMounts * (1 + d/2.) + 0.5 * d + 3) / M2FT;
}

float Gun::Wshell(float gunYear, float gunDiameter, float gunCaliber){
	float d 	= gunDiameter / (IN2CM * 10.);
	float c1 	= gunCaliber > 45. ? 1. + sqrt(gunCaliber - 45.)/45. : 1. - sqrt(45. - gunCaliber)/45.;
	float c2 	= gunYear < 1890 ? 1. - (1890. - gunYear)/66.66666 : 1.;
	return pow(d, 3.) * c1 * pow(c2, 2.) / KG2LB;
}

float Gun::Wgun(float L, float gd, float bM){
	float d		= gd / (IN2CM * 10.);
	float sW 	= Wshell(y, d, L) * KG2LB;
	return sW * L * (1. + pow(1. / d, 2.3298) / 812.389435 * bM * 3.5 * (1. - 2.163769 * d / 100.) * ST2MT;
}

float Gun::Wammo(){
}