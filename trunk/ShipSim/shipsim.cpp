#include "shipsim.h"

ShaftType st[] = {
	{ Direct, 0.98, 1., 1.55 },
	{ Geared, 0.96, 1., 1. },
	{ Turbo_Electric, 1., 0.75, 1.2 }
};

EngineType et[] = {
	{ Diesel2stk, 2.41, 0.62, 0.66 },
	{ Diesel4stk, 1.88, 0.60, 0.60 },
	{ QuadExp, 6.7, 0.54, 0.77 },
	{ TripExp, 7.7, 0.54, 0.88 },
	{ SimExp, 8.5, 0.54, 1. },
	{ SteamTur, 5., 0.54, 1.1 }
};

Ship::Ship(vitalParams x, engineParams y, armorParams z, bool _db, bool _par, battery _b){
	v	= x;
	e	= y;
	arm	= z;
    DB	= _db;
    PAR	= _par;
	// add linked list copying for battery
	b	= _b;
}

Ship::Ship(const Ship &src) {
	copyS(src);
}

const Ship& Ship::operator=(const Ship &src){
	if (this != &src)
		copyS(src);
	return *this;
}

void Ship::copyS(const Ship &src){
	v	= src.v;
	e	= src.e;
	arm	= src.arm;
    DB	= src.DB;
    PAR	= src.PAR;
	// add linked list copying for battery
	b	= _b;
}

void Ship::output(){
	ofstream file;
	file.open("Report.txt");
	file << "[table]" << endl;

	cout << fixed << setprecision(2) << "Length: \t\t\t\t" << v.Lpp << " m" << endl;
	file << fixed << setprecision(2) << "[tr][td]Length: \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[/td][td]" << v.Lpp << " m[/td][/tr]" << endl;
	cout << "Beam: \t\t\t\t\t" << v.B << " m" << endl;
	file << "[tr][td]Beam: [/td][td]" << v.B << " m[/td][/tr]" << endl;
	cout << "Draft: \t\t\t\t\t" << v.D << " m" << endl;
	file << "[tr][td]Draft: [/td][td]" << v.D << " m[/td][/tr]" << endl;
	cout << "Freeboard: \t\t\t\t" << v.fB << " m" << endl;
	file << "[tr][td]Freeboard: [/td][td]" << v.fB << " m[/td][/tr]" << endl;
	cout << setprecision(3) << "Block Coefficient: \t\t\t" << Cb() << endl;
	file << setprecision(3) << "[tr][td]Block Coefficient: [/td][td]" << Cb() << "[/td][/tr]" << endl;
	cout << setprecision(0) << "Displacement: \t\t\t\t" << Vol() << " t" << endl;
	file << setprecision(0) << "[tr][td]Displacement: [/td][td]" << Vol() << " t[/td][/tr]" << endl;
	cout << "Lightship: \t\t\t\t" << Wh() + Wwo() + Wm() + We() + Wspus() + Bunker() << " t" << endl;
	file << "[tr][td]Lightship: [/td][td]" << Lightship() << " t[/td][/tr]" << endl;

	cout << setprecision(1) << "\nMax Speed: \t\t\t\t" << v.Vk << " kn" << endl;
	file << setprecision(1) << "\n[tr][td]Max Speed: [/td][td]" << v.Vk << " kn[/td][/tr]" << endl;
	cout << "Cruise Speed: \t\t\t\t" << v.Vc << " kn / " << v.Range << " nm" << endl;
	file << "[tr][td]Cruise Speed: [/td][td]" << v.Vc << " kn / " << v.Range << " nm[/td][/tr]" << endl;

	cout << "Engine: \t\t\t\t";
	file << "[tr][td]Engine: [/td][td]";
	switch(e.Gear){
		case Direct:
            cout << "Direct ";
            file << "Direct ";
            break;
		case Geared:
		    cout << "Geared ";
		    file << "Geared ";
		    break;
		case Turbo_Electric:
		    cout << "Turbo-Electric ";
		    file << "Turbo-Electric ";
            break;
		default:
            cout << "Unknown";
            file << "Unknown";
	}
	switch(e.Eng){
		case Diesel2stk:
		    cout << "Two Stroke Diesel" << endl;
		    file << "Two Stroke Diesel";
		    break;
		case Diesel4stk:
		    cout << "Four Stroke Diesel" << endl;
		    file << "Four Stroke Diesel" << endl;
		    break;
		case QuadExp:
		    cout << "Quadruple Expansion Reciprocating Engine" << endl;
		    file << "Quadruple Expansion Reciprocating Engine";
		    break;
		case TripExp:
		    cout << "Triple Expansion Reciprocating Engine" << endl;
		    file << "Triple Expansion Reciprocating Engine";
		    break;
		case SimExp:
		    cout << "Simple Reciprocating Engine" << endl;
		    file << "Simple Reciprocating Engine";
		    break;
		case SteamTur:
		    cout << "Steam Turbine" << endl;
		    file << "Steam Turbine";
		    break;
		default:
            cout << endl;
	}
	file << "[/td][/tr]" << endl;

	cout << setprecision(0) << "Power Delivered: \t\t\t" << Pd(v.Vk) << " hp" << endl;
	file << setprecision(0) << "[tr][td]Power Delivered: [/td][td]" << Pd(v.Vk) << " hp[/td][/tr]" << endl;
	cout << setprecision(2) << "Total Efficiency: \t\t\t" << NUt()*100 << "%" << endl;
	file << setprecision(2) << "[tr][td]Total Efficiency: [/td][td]" << NUt()*100 << "%[/td][/tr]" << endl;
	cout << setprecision(3) << "Froude Number: \t\t\t\t" << Fn() << endl;
	file << setprecision(3) << "[tr][td]Froude Number: [/td][td]" << Fn()  << "[/td][/tr]" << endl;
	cout << setprecision(0) << "Bunker Size: \t\t\t\t" << Bunker() << " t" << endl;
	file << setprecision(0) << "[tr][td]Bunker Size: [/td][td]" << Bunker() << " t[/td][/tr]" << endl;
	cout << "Service Allowance: \t\t\t" << e.SA << "%" << endl;
	file << "[tr][td]Service Allowance: [/td][td]" << e.SA << "%[/td][/tr]" << endl;

	cout << setprecision(2);
	file << setprecision(2);
	cout << "Length of Superstructure: \t\t" << v.Lspus << " m" << endl;
	file << "[tr][td]Length of Superstructure: [/td][td]" << v.Lspus << " m[/td][/tr]" << endl;

	cout << "Aftbody Shape: \t\t\t\t";
	file << "[tr][td]Aftbody Shape: [/td][td]";
	switch(e.Faa){
		case V:
		    cout << "V" << endl;
		    file << "V";
		    break;
		case U:
		    cout << "U" << endl;
		    file << "U";
		    break;
		case N:
		    cout << "N" << endl;
		    file << "N";
		    break;
		default:
		    cout << "N" << endl;
		    file << "N";
	}
	file << "[/td][/tr]";

	cout << "\nLongitudinal Center of Buoyancy: \t" << lcb() << "%" << endl;
	file << "\n[tr][td]Longitudinal Center of Buoyancy: [/td][td]" << lcb() << "% / " << lcb()*v.Lpp << " m from midpoint[/td][/tr]" << endl;
	cout << "Longitudinal Center of Gravity: \t" << lcg() << "%" << endl;
	file << "[tr][td]Longitudinal Center of Gravity: [/td][td]" << lcg() << "% / " << lcg()*v.Lpp << " m from midpoint[/td][/tr]" << endl;

	cout << "Vertical Center of Gravity: \t\t" << KGh() << " m" << endl;
	file << "[tr][td]Vertical Center of Gravity: [/td][td]" << KGh() << " m[/td][/tr]" << endl;
	cout << "Metacentric Height: \t\t\t" << GM() << " m" << endl;
	file << "[tr][td]Metacentric Height: [/td][td]" << GM() << " m[/td][/tr]" << endl;
	cout << "Roll Period: \t\t\t\t" << TR() << " s" << endl;
	file << "[tr][td]Roll Period: [/td][td]" << TR() << " s[/td][/tr]" << endl;

	cout << "\nBow Entrance Angle: \t\t\t" << iE() << " deg" << endl;
	file << "\n[tr][td]Bow Entrance Angle: [/td][td]" << iE() << " deg[/td][/tr]" << endl;
	cout << "Length of Engine Room: \t\t\t" << Lcm() << " m" << endl;
	file << "[tr][td]Length of Engine Room: [/td][td]" << Lcm() << " m[/td][/tr]" << endl;

	cout << setprecision(0) << "\nMain Belt: \t\t\t\t" << arm.mb_Ttop << " / " << arm.mb_Tbot << " mm at " << arm.b_deg << " degrees, " << arm.b_L << " m long with " << arm.b_H << " m above and " << arm.b_Db << " m below water" << endl;
	file << setprecision(0) << "\n[tr][td]Main Belt: [/td][td]" << arm.mb_Ttop << " / " << arm.mb_Tbot << " mm, " << arm.b_L << " m long with " << arm.b_H << " m above and " << arm.b_Db << " m below water[/td][/tr]" << endl;

	cout << "End Belt: \t\t\t\t" << arm.eb_Ttop << " / " << arm.eb_Tbot << " mm" << endl;
	file << "[tr][td]End Belt: [/td][td]" << arm.eb_Ttop << " / " << arm.eb_Tbot << " mm[/td][/tr]" << endl;

	cout << "Upper Belt: \t\t\t\t" << arm.ub_Ttop << " / " << arm.ub_Tbot << " mm, " << arm.b_uL << " m long" << endl;
	file << "[tr][td]Upper Belt: [/td][td]" << arm.ub_Ttop << " / " << arm.ub_Tbot << " mm, " << arm.b_uL << " m long[/td][/tr]" << endl;

	cout << "Main Deck: \t\t\t\t" << arm.md_T << " mm covering " << arm.md_P << "% / " << arm.md_P * v.Lpp << " m of deck" << endl;
	file << "[tr][td]Main Deck: [/td][td]" << arm.md_T << " m covering " << arm.md_P << "% / " << arm.md_P * v.Lpp << " m of deck[/td][/tr]" << endl;
	cout << "Weather Deck: \t\t\t\t" << arm.wd_T << " mm covering " << arm.wd_P << "% / " << arm.wd_P * v.Lpp << " m of deck" << endl;
	file << "[tr][td]Weather Deck: [/td][td]" << arm.wd_T << " m covering " << arm.wd_P << "% / " << arm.wd_P * v.Lpp << " m of deck[/td][/tr]" << endl;
	cout << "Splinter Deck: \t\t\t\t" << arm.sd_T << " mm covering " << arm.sd_P << "% / " << arm.sd_P * v.Lpp << " m of deck" << endl;
	file << "[tr][td]Splinter Deck: [/td][td]" << arm.sd_T << " m covering " << arm.sd_P << "% / " << arm.sd_P * v.Lpp << " m of deck[/td][/tr]" << endl;
	cout << "Ends Deck: \t\t\t\t" << arm.ed_T << " mm" << endl;
	file << "[tr][td]Ends Deck: [/td][td]" << arm.ed_T << " mm[/td][/tr]" << endl;

	cout << "Bulkhead: \t\t\t\t" << arm.blk_T << " mm in " << arm.blk_Lct << "x" << arm.blk_D << " m layers, " << arm.blk_L << " m long, " << arm.blk_H << " m tall" << endl;
	file << "[tr][td]Bulkhead: [/td][td]" << arm.blk_T << " mm in " << arm.blk_Lct << "x" << arm.blk_D << " m layers, " << arm.blk_L << " m long, " << arm.blk_H << " m tall[/td][/tr]" << endl;

	file << "[/table]" << endl;

    file.close();
}

float Ship::Fn(){
	return v.Vk * KN2MS / sqrt(G * v.Lpp);
}

float Ship::Dprop(){
	return 0.395 * v.D + 1.3;
}

float Ship::Havg(){
	return ((0.22 * v.Lpp + 0.28 * pow(v.fB + v.D, 1.56) - 0.02 * pow(v.Lpp, 0.806) * pow(v.fB + v.D, 1.1)) - (v.fB + v.D)) / 2.0;
}

float Ship::Cb(){
	/* 	Watson-Gilfillan Line with mid-zone corrected by Kelsey Yuen
	 *	Developed independently by Yuen through regressive analysis of data from 50 ships, including tankers, bulk carriers, refrigerated containers. cargo-ships, frigates, corvettes, DDs, and BBs.
	 *	Corrects for Watson-Gilfillan along 0.25-0.54 Fn
	 */

	/*if(Fn() < 0.54262543 || Fn() > 0.25830128)
		return 0.7 + (1.0/8.0)*atan((23.0 - 100.0*Fn())/4.0);
	else
		return -1270.8*pow(Fn(), 5.0) + 2618.4*pow(Fn(), 4.0) - 2100.9*pow(Fn(), 3.0) + 822.31*pow(Fn(), 2.0) - 158.038*Fn() + 12.59;
    */
    return v.cB;
}

float Ship::Cm(){	// Kerlen 1970
	return 1.006 - 0.0056 * pow(Cb(), -3.56);
}

float Ship::Vol(){
	return v.Lpp * v.B * v.D * Cb();
}

float Ship::Cp(){
	return Cb()/Cm();
}

float Ship::Cw(){
	switch(e.Faa){
		case U: return 0.95 * Cp() + 0.17 * pow(1 - Cp(), 1./3.);
		case N: return (1. + 2. * Cb())/3.;
		case V: return pow(Cp(), 2./3.);
		default: return (1. + 2. * Cb())/3.;
	}
	return -1;
}

float Ship::Sw(){
	return 1.025 * 1.7 * v.Lpp * v.D + Vol()/v.D;
}

float Ship::WPA(){
	return v.Lpp * v.B * Cw();
}

float Ship::lcb(){
	return (8.8 - 38.9 * Fn());
}

float Ship::lcg(){
	float p = 0.0001, o = 0.0001;
	if(PAR)
		p = v.Lpp - v.r - v.e;
	else
		o = (v.Lpp - v.r - v.e) / 2. + v.r - (0.5 * v.Lpp);

	float base = (p*o + 0.778*v.r * (0.429*v.r + p/2. + o) - 0.745*v.e * (0.403*v.e + p/2. - o)) / (p + 0.778*v.r + 0.745*v.e);
	return base * Hullship() / Lightship();
}

float Ship::w(){
	float M = v.Lpp / pow(Vol(), 1./3.);

	int Fa;
	switch(e.Faa){
		case N: Fa = 0; break;
		case U: Fa = -2; break;
		case V: Fa = 2; break;
		default: Fa = 0;
	}

	float BL = v.B / v.Lpp;

	float a = 0.1 * BL + 0.149;
	float b = 0.05 * BL + 0.449;
	float c = 585. - 5027. * BL + 11700. * pow(BL, 2.);

	float w1 = a + b / (c * pow(0.98 - Cb(), 3.) + 1);
	float w2 = 0.025 * Fa / (100. * pow(Cb() - 0.7, 2.) + 1);
	float w3 = min(0.1, -0.18 + 0.00756 / (Dprop()/v.Lpp + 0.002));

	float S1 = e.Shafts > 1 ? 1. : 0.7;
	return 0.7 * (w1 + w2 + w3) - 0.45 + 0.08 * M * S1;
}

float Ship::t(){
	float M = v.Lpp / pow(Vol(), 1./3.);

	int Fa;
	switch(e.Faa){
		case N: Fa = 0; break;
		case U: Fa = -2; break;
		case V: Fa = 2; break;
		default: Fa = 0;
	}

	float BL = v.B / v.Lpp;

	float d = 0.625 * BL + 0.08;
	float e = 0.165 - 0.25 * BL;
	float f = 525. - 8060. * BL + 20300. * pow(BL, 2.);

	float t1 = d + e / (f * pow(0.98 - Cb(), 3.) + 1.);
	float t2 = -0.01 * Fa;
	float t3 = 2. * (Dprop()/v.Lpp - 0.04);

	return t1 + t2 + t3 - 0.26 + 0.04 * M;
}

float Ship::AeAo(){
	return (NUr - 0.9922 - 0.07424 * (Cp() - 0.0225 * lcb())) / -0.05908;
}

float Ship::Tprop(){
	float S2 = e.Shafts > 1 ? 0.2 : 1;
	return ((AeAo() - S2) * (99047 + 1.025 * G * v.D * 0.624516) * pow(Dprop(), 2.)) / ((1.3 + 0.3 * e.Z) * 1000);
}

float Ship::Va(){
	return (1 - w()) * v.Vk * KN2MS;
}

float Ship::Cth(){
	return (8./PI()) * Tprop() / (1.025 * pow(Va() * Dprop(), 2.));
}

float Ship::NUm(){
	return find(st, e.Gear).NUm;
}

float Ship::NUh(){
	return (1. - t()) / (1. - w());
}

float Ship::NUo(){
	return 2. / (1. + sqrt(Cth() + 1)) * max(0.65, 0.81 - 0.014 * Cth());
}

float Ship::NUt(){
	return NUg * NUm() * NUh() * NUr * NUo();
}

float Ship::Pe(float V){
	return ( Sw()/sqrt(Vol() * v.Lpp) * pow(Vol(), 2./3.) * pow(V, 3.) /580.) * (1 + e.SA/100.);
}

float Ship::Pd(float V){
	return Pe(V)/NUt();
}

float Ship::Bunker(){
	float b1 = v.Range / (1. + 0.4 * v.Coalpct);
	float b2 = 0.;
	float b3 = 1.8/Pd(v.Vc) * v.Range * v.Vc * 0.1;

	if (v.Year < 1898 || e.Eng == QuadExp || e.Eng == TripExp)
		b2 = 1. - (1910 - v.Year)/70.;
	else if (v.Year < 1920)
		b2 = 1. + (v.Year - 1910)/20.;
	else if( v.Year < 1950)
		b2 = 1.5 + (v.Year - 1920)/60.;
	else
		b2 = 2 + (v.Year - 1950)/60.;

	float c1 = (Pd(v.Vk)/Vol() > 15 && Pd(v.Vk)/Vol() < 18) ? 0.3 : 1;
	return (b1 / (b2 * b3) + 0.005 * Vol()) * c1 * find(et, e.Eng).FcE * find(st, e.Gear).FcT;
}

float Ship::Wh(){
	return pow(Cb()/0.8, 1./3.) * pow(10., -5.) * ((5.11 * pow(v.Lpp, 3.3) * v.B/v.D) + (2.56 * pow(v.Lpp, 2.) * pow(v.B + v.D + v.fB, 2.)));
}

float Ship::Wm(){
	float c1, c2;
	c1 = c2 = 0.;

	float PdV = Pd(v.Vk)/Vol();
	float c3 = pow(v.Year, 0.4) - 19;
	if (PdV > 40)
		c1 = 0.14 * c3;
	else if (PdV > 26)
		c1 = 0.13 * c3;
	else if (PdV > 21)
		c1 = 0.21 * c3;
	else if (PdV > 10)
		c1 = 0.22 * c3;
	else c1 = 1.;

	if (Vol() > 5000)
        c1 = 1.;

	if (v.Year < 1915)
		c2 = 1.9;
	else if(v.Year < 1933)
		c2 = 1.6;
	else c2 = 0.92;

	return find(et, e.Eng).K1 * pow(Pd(v.Vk), find(et, e.Eng).K2)* (pow((pow(v.Year, 0.45) - 29.3), 2.) + 0.45) * c1 * c2 * find(st, e.Gear).Wgear;
}

float Ship::aB(){
	return 0.9 * 68.7713 * exp(-2.18341 * v.Lpp * v.B / (Wh() + Wm()));
}

float Ship::Wwo(){
	return aB() * v.Lpp * v.B / 100.;
}

float Ship::We(){
	return (0.28 - v.Lpp/1620.) * v.Lpp * v.B;
}

float Ship::Wspus(){
	return Havg()/2.4 * 0.19 * (v.Lspus * v.B * 0.8 * (Cb() + Cm())/2.0);
}

float Ship::Lcm(){
	float Bmod = v.B - (2 * arm.blk_T/1000. * arm.blk_Lct * arm.blk_D);
    return Ve() / (Bmod * (v.D + v.fB) * Cb() * 0.85);
}

float Ship::Lcmi(){
	return (0.002 * Pd(v.Vk) + 5.5) / M2FT;
}

float Ship::Ve(){
    //  0.650 Cb
    return Lcmi() * v.B * (v.D + v.fB) * 0.650 * 0.85;
}

float Ship::TPC(){
	return WPA() / 97.56;
}

float Ship::MCTC(){
	return 7.31 * pow(TPC(), 2.) / v.B;
}

float Ship::lr(){
	return v.Lpp * (1 - Cp() + 0.06 * Cp() * lcb()) / (4 * Cp() - 1);
}

float Ship::iE(){
	float c1 = - pow(v.Lpp / v.B, 0.80856) * pow(1 - Cw(), 0.30484) * pow(1 - Cp() - 0.0225 * lcb(), 0.6367) * pow(lr() / v.B, 0.34574) * pow(100 * Vol() / pow(v.Lpp, 3.), 0.16302);
	return 1 + 89 * exp(c1);
}

float Ship::KGs(){
	float t = 0.01 * (v.D + v.fB) * (46.6 + 0.135 * (0.81 - Cb()) * pow(v.Lpp / v.D, 2.)) + 0.008 * (v.D + v.fB) * (v.Lpp / v.B - 6.5);

	if (v.Lpp >= 120.)
		return t;
	else
		return t + 0.001 * (v.D + v.fB) * (1. - (v.Lpp - 60.)/60.);
}

float Ship::KGe(){
	if (v.Lpp <= 125.)
		return (v.D + v.fB) + 1.25;
	else if (v.Lpp <= 250.)
		return (v.D + v.fB) + 1.25 + 0.01 * (v.Lpp - 125.);
	else
		return (v.D + v.fB) + 2.5;
}

float Ship::hDB(){
	return (250. + 20. * v.B + 50. * (v.D + v.fB)) / 1000.;
}

float Ship::KGm(){
	if (DB)
		return hDB() + 0.35 * ((v.D + v.fB) - hDB());
	else
		return 0.35 * (v.D + v.fB);
}

float Ship::KGspus(){
	return Havg() + (v.D + v.fB);
}

float Ship::KGh(){
	float hulltotal	= Wh() + Wm() + Wwo() + We() + Wspus() + Bunker();
	float WKGh		= (Wh() + Wwo()) * KGs();
	float WKGe		= We() * KGe();
	float WKGm		= (Wm() + Bunker()) * KGm();
	float WKGspus	= Wspus() * KGspus();

	float armortot	= Wmb() + Web() + Wub() + Wmd() + Wwd() + Wsd() + Wed() + Wblk();
	float WKGmb		= Wmb() * KGmb();
	float WKGeb		= Web() * KGeb();
	float WKGub		= Wub() * KGub();
	float WKGmd		= Wmd() * KGmd();
	float WKGwd		= Wwd() * KGwd();
	float WKGsd		= Wsd() * KGsd();
	float WKGed		= Wed() * KGed();
	float WKGblk	= Wblk() * KGblk();

	float total		= hulltotal + armortot;

	return (WKGh + WKGe + WKGm + WKGspus + WKGmb + WKGeb + WKGub + WKGmd + WKGwd + WKGsd + WKGed + WKGblk) / total;
}

float Ship::KM(){
	float Cbw = Cb() / Cw();
	return v.B * (13.61 - 45.4* Cbw + 52.17 * pow(Cbw, 2.) - 19.88 * pow(Cbw, 3.));
}

float Ship::GM(){
	return KM() - KGh();
}

float Ship::TR(){
	return 0.43 * v.B / sqrt(GM());
}

float Ship::Stability(){
	return 100. * GM() / pow(v.B, 1.5) + 0.5;
}

float Ship::Flotation(){
	float c1 = Stability() > 1 ? sqrt(Stability()) : pow(Stability(), 4.);
	float c4 = v.Year < 1850 ? 0.4 : (v.Year > 1890 ? 1 : 1 - 3. * (1890 - v.Year) / 200.);
	return (WPA() / 35. + Vol()) / 2. * c1 * c4;
}

/***** What follows is the armor section ****/

float Ship::Hullship(){
    return Wh() + Wwo() + Wm() + We() + Wspus() + Bunker();
}

float Ship::Lightship(){
    return Hullship() + Wmb() + Web() + Wub() + Wmd() + Wwd() + Wsd() + Wed();
}

float Ship::KGb(float Ttop, float Tbot, float H, float Db, float deg, float Height){
	if (Ttop == Tbot)
		return (H + Db) / 2.;

    float Tt = Ttop/1000.;
    float Tb = Tbot/1000.;
    float c = (pow(H, 2.) + pow(Db, 2.)) / 2.;
    float k = pow(H + Db, 2.) / (Tt - Tb);
    return (c * k + Tb) * cos(deg) / (k + 2*Tb) + Height - Db;
}

float Ship::Wbelt(float Tt, float Tb, float Lb, float H, float Db, float deg){
    return 2 * STEELDENSITY * (Tt + Tb)/2000 * v.Lpp * (H + Db) / cos(deg);
}

float Ship::Wmb(){
	return Wbelt(arm.mb_Ttop, arm.mb_Tbot, arm.b_L, arm.b_H, arm.b_Db, arm.b_deg);
}

float Ship::Web(){
	return Wbelt(arm.eb_Ttop, arm.eb_Tbot, v.Lpp - arm.b_L, arm.b_H, arm.b_Db, arm.b_deg);
}

float Ship::Wub(){
	return Wbelt(arm.ub_Ttop, arm.ub_Tbot, arm.b_uL, v.fB - arm.b_H, 0., arm.b_deg);
}

float Ship::KGmb(){
	return KGb(arm.mb_Ttop, arm.mb_Tbot, arm.b_H, arm.b_Db, arm.b_deg, v.D);
}

float Ship::KGeb(){
	return KGb(arm.eb_Ttop, arm.eb_Tbot, arm.b_H, arm.b_Db, arm.b_deg, v.D);
}

float Ship::KGub(){
	return KGb(arm.ub_Ttop, arm.ub_Tbot, v.fB - arm.b_H, 0., arm.b_deg, arm.b_H);
}

float Ship::Wdeck(float T, float perc){
	return STEELDENSITY * (T/1000.) * v.Lpp * v.B * Cb() * perc / 100.;
}

float Ship::Wmd(){
	return Wdeck(arm.md_T, arm.md_P);
}

float Ship::Wwd(){
	return Wdeck(arm.wd_T, arm.wd_P);
}

float Ship::Wsd(){
	return Wdeck(arm.sd_T, arm.sd_P);
}

float Ship::Wed(){
	return Wdeck(arm.ed_T, 100. - arm.md_P);
}

float Ship::KGmd(){
	return arm.md_H + v.D;
}

float Ship::KGwd(){
	return v.fB + v.D;
}

float Ship::KGsd(){
	return KGmd() - 2.;	// assumes average deck height is 2 m
}

float Ship::KGed(){
	return KGmd();
}

float Ship::Wblk(){
	return STEELDENSITY * arm.blk_L * arm.blk_H * (2 * arm.blk_T/1000. * arm.blk_Lct);
}

float Ship::KGblk(){
	return arm.blk_H / 2. + DB? hDB() : 0;
}

float Ship::Vblk(){
	return arm.blk_L * arm.blk_H * (2 * arm.blk_T/1000. * arm.blk_Lct) * (2*Cb() + Cm())/3;
}

/*
float compstr(){
	float vitalspace 	= Lcm() + Lguns() / ((Vol() - Vblk()) * 0.94);
	float ebelt			= 2. * v.Lpp * 0.35 * 1.2 * sqrt(v.B) * (arm.eb_Ttop + arm.eb_Tbot)/2. * 0.185 * (v.Lpp - arm.mb_P);
	// missing mb_sF, WgunMB(), sb_sF, WgunSB(), tb_sF, WgunTB()
	float superFactor	= (gun.mb_sF * WgunMB() + gun.sb_sF * WgunSB() + gun.tb_sF * WgunTB()) / (WgunMB() + WgunSB() + WgunTB());
	float lsuprfactor	= 2. * superfactor - 1.;
	// missing battwt, btarm
	float girder		= (Hullship() / (pow( v.Lpp / (v.D + v.fB), 2.) * (Vol() + ebelt * 3. + (gun.battwt + gun.btarm) * lsuprfactor * 2.)) * 850.) * v.year < 1900 ? 1. - (1900. - v.year) / 100. : 1.;

	// missing mainweight, broadside, mainturrets, midweight, broadside, midturrets
	float concentration	= mainweight / broadside * (pow(4. / mainturrets, 0.25) - 1.);
	concentration 		+= midweight / broadside * (pow(4. / midturrets, 0.25) - 1.);
	++concentration;
	// missing structwt, btarm, ct
	float scantlings	= structwt / sqrt(v.B * (v.D + v.fB))) / ((Vol() + ((9.*broadside/8. + btarm + ct) * (concentration * superFactor) * Pd / 100.)) / Vol()) * 0.6 * v.year < 1900 ? 1. - (1900. v.year) / 100. : 1.;

	return scantling <= girder ? scantlings * pow(girder / scantlings, 0.1) : girder * pow(scantlings / girder, 0.25);
    }
}
*/

// Warning: Here be dragons
// All in Imperial
/*
	float compstrCalc()
      return compstr = scantlings <= this.girder ? scantlings * pow( girder / scantlings, 0.1) : girder * pow(scantlings / girder, 0.25);
 */
 /*
	float submergenceCalc()
      submergence = Lpp * B * pow(cb, 0.67) / 35.;

	float vitalspaceCalc()
      vitalspace = (loadwt - bunker + broadside * 0.8 + engwt * 3.0 + miscwt) / (Vol * 0.94);
      if (tpbkd > 0.1)
        vitalspace *= B / (B - 20f);
      vitalspace /= 1f - ttunderspace;
      return vitalspace;
    }
 */
 /*
	float superfiringCalc(string checkString){
      return superfiring = integerCheck(superfiringBox.Text);
	float supermainCalc()
      return supermain = chkMainBarbette.Checked || year < 1880 && mainturrets < 1 ? 0.7f : mainturrets <= 0 ? 1f : (1. + superfiring / mainturrets * 0.3);
	float supersecCalc()
      return supersec = chkSecLow.Checked || chkSecBarbette.Checked || year < 1880 && midturrets < 1 ? 0.7f : 1f;
    float superqfCalc()
      return superqf = !chkThirdLow.Checked ? 1f : 0.7f;
	float superfactorCalc()
      return superfactor = (mbarmwt * supermain + ibarmwt * supersec + (qfarmwt * superqf) + ltarmwt) / btarm;
 */
 /*
	float lsuprfactorCalc(){
      lsuprfactor = vitalspace;
      if (chkTiger.Checked)
        lsuprfactor *= superfactor;
      else if (chkCentralcite.Checked || chkBroadside.Checked)
        lsuprfactor *= superfactor * 0.8f;
      else
        lsuprfactor *= 2. * superfactor - 1.;
      return lsuprfactor;
    }
 */
 /*
	float ctCalc()
	  ct = 10. * pow(Vol / 10000., 0.67) * conntower;
 */
 /*
	float scantlingsCalc(){
      if (broadside > 0.0){
        concentration = mainturrets <= 0 ? mainweight / broadside * -0.1 : mainweight / broadside * (pow(4. / mainturrets, 0.25) - 1.);
        if (this.midturrets > 0)
          concentration += midweight / broadside * (pow(4. / midturrets, 0.25) - 1.);
        else
          concentration += midweight / broadside * -0.1;
        concentration += qfweight / broadside * -0.1;
      }
      ++concentration;
      scantlings = structwt / sqrt(B * T) / ((Vol + ((broadside + (broadside/8) + btarm + ct) * (concentration * superfactor) + max(Pd, hpMax) / 100.)) / Vol) * 0.6;
      if (year < 1900)
        scantlings *= 1. - (1900. - date) / 100.;
      return scantlings;
    }
 */
 /*
	float girderCalc(){
      this.girder = hullwt / (pow( Lpp / (D + fB), 2.) * (Vol + ebelt * 3. + (battwt + btarm) * lsuprfactor * 2.)) * 850.;
      if (year < 1900)
        girder *= 1. - (1900. - year) / 100.;
      return girder;
    }
 */
 /*
	float ebeltCalc()
      return ebelt = 2.0 * Lpp * 0.35 * 1.2 * sqrt(B) * beltends * 0.0185000002384186 * coverage;
 */
