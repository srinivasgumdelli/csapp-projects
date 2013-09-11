/*	@file 	parallelballistics.cpp
 *	@author	Kelsey Yuen
 *	@date	9/8/2013
 */

#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <time.h>

#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

#define G 9.80665
#define M2IN 39.3701
#define M2FT 3.28084
#define KGM32LBIN3 0.000036
#define KG2LB 2.20462

typedef struct {
	float const r;
	float const m;
	float const Cd;
	// armor properties
	float const t;
	// changeable values
	float angle;
	float V;
	float h;
	float d;
} shell;

float PI(){
	return 4*atan(1);
}

float toRadians(float a){
	return a * PI() / 180.0;
}

float toDegrees(float a){
    return a * 180.0 / PI();
}

float densityH(float h){
	// Air Pressure at Height H		p(h) = p0 * (1 - Lh/T0)^(gM/RL)
	// Temperature at Height H 		T = To - Lh
	// p0 = 101.325 kPa				T0 = 288.15 K
	// g = 9.80665 m/s^2			L = 0.0065 K/m
	// R = 8.31447 J/(mol*k)		M = 0.0289644 kg/mol
	// Density at height H			rho = pM/RT

	float p = 101.325 * pow(1 - 0.0065 * h / 288.15, G * 0.0289644 / (8.31447 * 0.0065));
	float T = 288.15 - 0.0065*h;

	return p * 0.0289644 / (8.31447 * T) * 1000;
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

float penetration(shell &Obj){
    float t = Obj.t * M2IN;
    float d = 2 * Obj.r * M2IN;
    float wd = Obj.m/pow(2*Obj.r, 3.0) * KGM32LBIN3;
    float V = Obj.V * M2FT;

	float FSTD = 6 * ( t/d - 0.45) * (toDegrees(Obj.angle) * 0.85 + 2000.0) + 40000.0;
	return 1728.04 * wd * pow(V / FSTD * cos(Obj.angle * 0.85), 2.0) * d * 25.4 * 0.61;	// 25.4 to convert in -> mm, 0.61 because penetration is too high, 0.85*angle to account for lift from gyroscopic force
}

// Estimates muzzle velocity from calibre for the period 1820-2010
float muzzleVelocity(float diameter, float calibre, float weight, short year){
	float c;
	if (year >  2000) c = 0.40;
	if (year <= 2000) c = 0.42;
	if (year <= 1980) c = 0.60;
	if (year <= 1950) c = 0.65;
	if (year <= 1930) c = 0.68;
	if (year <= 1900) c = 1.00;
	if (year <= 1880) c = 1.40;
	if (year <= 1860) c = 6.00;

	c *= 0.1*(year - 1870) + 14.0;

	return 0.92 * sqrt(pow(diameter * M2IN, 3.0) * calibre * pow(10.0, 6.0) / (c * weight * KG2LB));
}

int main(){
    /*
    std::cout << "Enter the details in the following order" << std::endl;
    std::count << "Diameter, Mass, Cd, angle (Rads), muzzle velocity, height" << std::endl;
    */
	string input = "";
	float diameter, weight, cd, mV, L, year, inc;

	int mode;
	cout << "In mode 1, the table printed is in elevation increments. In mode 2, the table is printed in range increments." << endl;
	cout << "Enter the output mode (1 or 2):\n";
	getline(cin, input);
	stringstream mStream(input);
	assert(mStream >> mode);

	cout << "Enter the increment the table will be printed in:\n";
	getline(cin, input);
	stringstream iStream(input);
	assert(iStream >> inc);

	cout << "Enter the diameter (mm):\n";
	getline(cin, input);
	stringstream dStream(input);
	assert(dStream >> diameter);
	diameter /= 2000.0;

	cout << "Enter the calibre:\n";
	getline(cin, input);
	stringstream cStream(input);
	assert(cStream >> L);

	cout << "Enter the gun year (1820-2010):\n";
	getline(cin, input);
	stringstream yStream(input);
	assert(yStream >> year);

	cout << "Enter the weight (kg):\n";
	getline(cin, input);
	stringstream wStream(input);
	assert(wStream >> weight);

	mV = muzzleVelocity(diameter, L, weight, year);
	//cout << mV << endl;

	cout << "Enter the Cd (0.25-0.27):\n";
	getline(cin, input);
	stringstream cdStream(input);
	assert(cdStream >> cd);
	cout << endl;

	/*cout << "Enter the muzzle velocity (mps):\n";
	getline(cin, input);
	cout << endl;
	stringstream mvStream(input);
	assert(mvStream >> mV);*/

	shell Obj { diameter, weight, cd, 0.300, 0.0, mV, 0.1, 0.0 };
	float step = 1000000.0;
	cout << setprecision(2) << fixed;
	for(float t = 0; t <= 45; t += 0.05){
		Obj.angle 	= toRadians(t);
		Obj.V		= mV;
		Obj.h		= 0.1;
		Obj.d		= 0.0;

        int i;
		for(i = 0; Obj.h > 0; i++)
			Obj.d += ballistics(i/step, Obj);

		switch(mode){
            case 1:
                if (fmod(t, inc) < 0.04 || fmod(t, inc) > inc - 0.04)
                    cout << t << " deg\t" << Obj.d << " m\t" << i << " s\t" << Obj.V << " mps\t" << toDegrees(Obj.angle) << " deg\t" << penetration(Obj) << "mm" << endl;
                break;
            case 2:
                if (fmod(Obj.d, inc) < 40 || fmod(Obj.d, inc) > inc - 40)
                    cout << t << " deg\t" << Obj.d << " m\t" << i << " s\t" << Obj.V << " mps\t" << toDegrees(Obj.angle) << " deg\t" << penetration(Obj) << "mm" << endl;
                break;
            default:
                break;
        }
	}

	delete &Obj;

    /*clock_t begin, end, start, stop;
    begin = clock();

	shell Mark8 { 0.203, 1224.7, 0.27, 0.300, toRadians(45), 762.2, 0.1, 0.0 };   // 16"/50 Mark 7 AP Mark 8

	float step = 1000.0;				                            // the scale, 1000 = by milliseconds

	std::cout << std::setprecision(2) << std::fixed;

    for(float theta = 0; theta <= 45; theta += 1){
		start = clock();
        Mark8.angle = toRadians(theta);
        Mark8.V     = 762.2;
        Mark8.h     = 0.1;
		Mark8.d 	= 0.0;

        for(int i = 0; Mark8.h > 0; i++)
            Mark8.d += ballistics(i/step, Mark8);

        //if ((int)distance % 5000 < 100 || (int)distance % 5000 > 4900)
        cout << theta << " degrees\t" << Mark8.d << " m\t" << Mark8.V << " mps\t" << toDegrees(Mark8.angle) * 0.85 << " degrees\t" << penetration(Mark8) << " mm" << endl;

		stop = clock();
		cout << "\tTime Spent: " << (double)(stop - start) / (CLOCKS_PER_SEC/1000) << endl;
    }

    end = clock();
    cout << "Steps: " << step << "\tTime Spent: " << (double)(end - begin) / (CLOCKS_PER_SEC/1000) << endl;

    delete &Mark8;*/

	cout << "\nEnter any key to exit.\n";
	char hold;
	cin >> hold;
}
