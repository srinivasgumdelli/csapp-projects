#include "gun.h"

/***** What follows is the Guns section ****/

Gun::~Gun(){
	clear();
}

void clear(){
	if(next != NULL)
		next.clear();
	delete this;
} /* Correct this! Untested and unreasonable! */

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
	spread		= src.spread;
	maxAngle	= src.maxAngle;
	g			= src.g;
	head		= src.head;
	next		= src.next;
	
	Gun *tmp 	= src.next;
	Gun *cur	= next;
	while (tmp != NULL){
		next	= tmp;
		cur		= cur->next;
		tmp		= tmp->next;
	}
}

float Gun::Dbarb(float barrelMounts){
	float d = g.d / (IN2CM * 10.);
	return (barrelMounts * (1 + g.d/2.) + 0.5 * g.d + 3) / M2FT;
}

float Gun::Wshell(){
	float d 	= g.d / (IN2CM * 10.);
	float c1 	= g.L > 45. ? 1. + sqrt(g.L - 45.)/45. : 1. - sqrt(45. - g.L)/45.;
	float c2 	= g.L < 1890 ? 1. - (1890. - g.L)/66.66666 : 1.;
	return pow(g.d, 3.) * c1 * pow(c2, 2.) / KG2LB;
}

float Gun::Wgun(){
	float total = 0.0;
	Mount *cur	= head;
	while(cur != NULL){
		total 	+= _Wgun(cur->barrel_ct);
		cur		= cur->next;
	}
	return total;
}

// Helper function
float Gun::_Wgun(unsigned int bM){
	float d		= g.d / (IN2CM * 10.);
	float sW 	= Wshell() * KG2LB;
	return sW * g.L * (1. + pow(1. / g.d, 2.3298) / 812.389435 * bM * 3.5 * (1. - 2.163769 * g.d / 100.) * ST2MT;
}

float Gun::Wammo(){
	float total = 0.0;
	Mount *cur	= head;
	while(head != NULL){
		total 	+= cur->barrel_ct;
		cur 	= cur->next;
	}
	return total * g.SpB * Wshell();
}

shell Gun::Range(){
	shell *tmp { g.d, Wshell(), 0.25, 0.3, maxAngle, mV(g.d, g.L, Wshell(), g.Y), 0.1, 0. };
	float step 	= 1000000.;
	for(int i = 0; tmp->h > 0; i++)
		tmp->d += ballistics(i/step, tmp);
	return tmp;
}