#ifndef SHIPSIM_H
#define SHIPSIM_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstring>

#include "enumparser.h"
#include "gun.h"
#include "main.h"

#define SHAFTSIZE 3
#define ENGINESIZE 6

using namespace std;

typedef struct {
	float Lpp;
	float B;
	float D;
	float fB;
	float cB;
	float Vk;
	float Vc;
	float Range;
	float Coalpct;
	unsigned int Year;
	float Lspus;
	float r;
	float e;
} vitalParams;

typedef struct {
	float Shafts;
	float Z;
	AftShape Faa;
	Engin Eng;
	Gearbox Gear;
	Service_Allowance SA;
} engineParams;

typedef struct {
    float mb_Ttop;
    float mb_Tbot;
    float b_L;
    float b_uL;
    float b_H;
    float b_Db;
    float b_deg;
    float eb_Ttop;
    float eb_Tbot;
    float ub_Ttop;
    float ub_Tbot;
    float md_T;
    float md_H;
    float md_P;
    float wd_T;
    float wd_P;
    float sd_T;
    float sd_P;
    float ed_T;
	float blk_T;
	float blk_L;
	float blk_H;
	float blk_Lct;
	float blk_D;
} armorParams;

inline ShaftType find(ShaftType *s, Gearbox g){
    for(unsigned int i = 0; i < SHAFTSIZE; i++){
        if(s[i].g == g)
            return s[i];
    }
}

inline EngineType find(EngineType *et, Engin e){
    for(unsigned int i = 0; i < ENGINESIZE; i++){
        if(et[i].e == e)
            return et[i];
    }
}

class Ship{
	public:
		Ship(vitalParams x, engineParams y, armorParams z, gunParams w, bool _db, bool _par, battery _b);

		Ship(const Ship &src);
		const Ship& operator=(const Ship &src);

		void output();

		vitalParams 	v;
		engineParams 	e;
		armorParams 	arm;
		battery			b;
		bool DB;
		bool PAR;

	private:
	    void copyS(const Ship &src);

		float Fn();
		float Dprop();
		float Havg();

		float Cb();
		float Cm();
		float Vol();
		float Cp();
		float Cw();
		float Sw();
		float WPA();

		float lcb();
		float lcg();

		float w();
		float t();

		float AeAo();
		float Tprop();
		float Va();
		float Cth();
		float NUm();
		float NUh();
		float NUo();
		float NUt();
		float Pe(float V);
		float Pd(float V);
		float Bunker();

		float Wh();
		float Wm();
		float aB();
		float Wwo();
		float We();
		float Wspus();

		float Lcm();
		float Lcmi();
		float Ve();
		float TPC();
		float MCTC();
		float lr();
		float iE();
		float KGs();
		float KGe();
		float hDB();
		float KGm();
		float KGspus();
		float KGh();
		float KM();
		float GM();
		float TR();

		float Stability();
		float Flotation();

		float Hullship();
		float Lightship();
		float KGb(float Ttop, float Tbot, float H, float Db, float deg, float Height);
		float Wbelt(float Tt, float Tb, float Lb, float H, float Db, float deg);
		float Wmb();
		float Web();
		float Wub();
		float KGmb();
		float KGeb();
		float KGub();

		float Wdeck(float T, float perc);
		float Wmd();
		float Wwd();
		float Wsd();
		float Wed();
		float KGmd();
		float KGwd();
		float KGsd();
		float KGed();

		float Wblk();
		float KGblk();
		float Vblk();
};

#endif // SHIPSIM_H
