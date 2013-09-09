/*	@file 	parallelballistics.cpp
 *	@author	Kelsey Yuen
 *	@date	9/8/2013
 */

#include <cmath>
#include <iostream>

#define G 9.80665

typedef struct {
	float const r;
	float const m;
	float const Cd;
	// changeable values
	float angle;
	float V;
	float h;
} shell;

float PI(){
	return 4*atan(1);
}

float toRadians(float a){
	return a * PI() / 180.0;
}

float densityH(float h){
	// Air Pressure at Height H		p(h) = p0 * (1 - Lh/T0)^(gM/RL)
	// Temperature at Height H 		T = To - Lh
	// p0 = 101.325 kPa				T0 = 288.15 K
	// g = 9.80665 m/s^2			L = 0.0065 K/m
	// R = 8.31447 J/(mol*k)		M = 0.0289644 kg/mol
	// Density at height H			rho = pM/RT

	float p = 101.325 * pow(1 - 0.0065*h/288.15, G*0.53594054);
	float T = 288.15 - 0.0065*h;

	return p * 0.0289644 / (8.31447 * T);
}

float drag ( float Cd, float rho, float A, float V, float m){
	return 0.5 * Cd * rho * A * (V * V) / m;
}

// Returns the distance traveled that step
float ballistics(float timeStep, shell &Obj){
	float A = pow(Obj.r, 2.0) * PI();
	float rho = densityH(Obj.h);
	float d = drag(Obj.Cd, rho, A, Obj.V, Obj.m);

	float Vx = Obj.V * cos(Obj.angle) - d * cos(Obj.angle) * timeStep;
	float Vy = Obj.V * sin(Obj.angle) - (d * sin(Obj.angle) + G) * timeStep;

	Obj.angle = atan(Vy/Vx);
	Obj.h = Obj.h + Vy * timeStep;
	Obj.V = pow(Vx * Vx + Vy * Vy, 0.5);		// watch for race condition

	return Vx * timeStep;
}

// Parallel the serial code by prediction
float parBallistics(float timeStep, shell &Obj){
	return Obj.V - drag(Obj.Cd, densityH(Obj.h), pow(Obj.r, 2.0) * PI(), Obj.V, Obj.m) * timeStep;
}

int main(){
	shell Mark8 { 203, 1224.7, 0.27, toRadians(45), 762.2, 0.1 };   // 16"/50 Mark 7 AP Mark 8

	float step = 1000.0;				                            // the scale, 1000 = by milliseconds
	float distance = 0.0;

	for(int i = 0; Mark8.h > 0; i++)
		distance += ballistics(i/step, Mark8);

	std::cout << distance << std::endl;

	delete &Mark8;
}
