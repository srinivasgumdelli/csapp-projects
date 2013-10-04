#include "shipsim.h"
#include <iostream>
#include <string>

using namespace std;

string VERSIONNUMBER = "0.3a";

int main(){
	vitalParams x;
	engineParams y;
	armorParams z;
	bool _db, _par;

	cout << "Welcome to the Command Line version of Ship Sim\nDeveloped by Staedler aka Logi\nThis is version " <<  VERSIONNUMBER << endl;
	cout << "The ability to place guns as well as simulate longitudinal / cross-sectional strength is not included in this version!" << endl ;
	cout << "Inputs and other items are not sanitized so please don't purposefully try to break the program. It will break!" << endl;
	cout << endl << endl;
	cout << "You will be prompted for many different values, please fill them all in. If you don't know the terms, look at the README!" << endl;

	cout << "\nEnter Lpp in m: ";
	cin >> x.Lpp;
	cout << "\nEnter Bwl in m: ";
	cin >> x.B;
	cout << "\nEnter D in m: ";
	cin >> x.D;
	cout << "\nEnter fB in m: ";
	cin >> x.fB;
	cout << "\nEnter cB: ";
	cin >> x.cB;
	cout << "\nEnter Vk in kn: ";
	cin >> x.Vk;
	cout << "\nEnter Vc in kn: ";
	cin >> x.Vc;
	cout << "\nEnter the range in nm: ";
	cin >> x.Range;
	cout << "\nEnter the percentage of coal in the fuel (0 to 100): ";
	cin >> x.Coalpct;
	cout << "\nEnter the year the hull and engine is laid down: ";
	cin >> x.Year;
	cout << "\nEnter Lspus in m: ";
	cin >> x.Lspus;
	cout << "\nEnter e as % of L in m (0 to 100): ";
	cin >> x.e;
	x.e *= x.Lpp / 100.;
	cout << "\nEnter r as % of L in m: ";
	cin >> x.r;
	x.r *= x.Lpp / 100.;

	cout << "\nEnter the number of propeller shafts: ";
	cin >> y.Shafts;
	cout << "\nEnter Z: ";
	cin >> y.Z;

	cout << "\nEnter Faa:";
	string sFaa;
	cin >> sFaa;
	EnumParser<AftShape> _as;
	y.Faa = _as.ParseEnum(sFaa);

	cout << "\nEnter the engine type as one of the following; 'Diesel-2stroke', 'Diesel-4stroke', 'Quad-Expansion', 'Triple-Expansion', 'Simple-Expansion', 'Steam-Turbine': ";
	string sEng;
	cin >> sEng;
	EnumParser<Engin> _e;
	y.Eng = _e.ParseEnum(sEng);

	cout << "\nEnter the transmission type as one of the following, { 'Direct', 'Geared', 'Turbo-Electric' } : ";
	string sGear;
	cin >> sGear;
	EnumParser<Gearbox> _g;
	y.Gear = _g.ParseEnum(sGear);

	cout << "\nEnter the operating area/route as one of the following, { 'Europe-Australia', 'Europe-EastAsia', 'NAeast', 'NAwest', 'Pacific', 'Trial' }: ";
	string sSA;
	cin >> sSA;
	EnumParser<Service_Allowance> _sa;
	y.SA = _sa.ParseEnum(sSA);

	cout << "\ndB? Enter 0 for no and 1 for yes: ";
	cin >> _db;
	cout << "\nParallel mid-body (1) or continuously curving (0)?:";
	cin >> _par;

	cout << "\nEnter the upper T of the main belt in mm: ";
	cin >> z.mb_Ttop;
	cout << "\nEnter the lower T of the main belt in mm: ";
	cin >> z.mb_Tbot;
	cout << "\nEnter the length of the main belt in mm: ";
	cin >> z.b_L;
	cout << "\nEnter the height above water of the main belt in m: ";
	cin >> z.b_H;
	cout << "\nEnter the depth underwater of the main belt in m: ";
	cin >> z.b_Db;
	cout << "\nEnter the slope of the main belt in degrees: ";
	cin >> z.b_deg;
	z.b_deg = DEGREE_RADIANS(z.b_deg);
	cout << "\nEnter the upper T of the end belt in mm: ";
	cin >> z.eb_Ttop;
	cout << "\nEnter the lower T of the end belt in mm: ";
	cin >> z.eb_Tbot;
	cout << "\nEnter the upper T of the upper belt in mm: ";
	cin >> z.ub_Ttop;
	cout << "\nEnter the lower T of the upper belt in mm: ";
	cin >> z.ub_Tbot;
	cout << "\nEnter the length of the upper belt in m: ";
	cin >> z.b_uL;
	cout << "\nEnter the T of the main deck in mm: ";
	cin >> z.md_T;
	cout << "\nEnter the height above water of the main deck in m: ";
	cin >> z.md_H;
	cout << "\nEnter the percentage covered by the main deck (0 to 100): ";
	cin >> z.md_P;
	cout << "\nEnter the T of the weather deck in mm: ";
	cin >> z.wd_T;
	cout << "\nEnter the percentage covered by the weather deck (0 to 100): ";
	cin >> z.wd_P;
	cout << "\nEnter the T of the splinter deck in mm: ";
	cin >> z.sd_T;
	cout << "\nEnter the percentage covered by the splinter deck (0 to 100): ";
	cin >> z.sd_P;
	cout << "\nEnter the T of the ends deck in mm: ";
	cin >> z.ed_T;
	cout << "\nEnter the T of the Torpedo Bulkhead in mm: ";
	cin >> z.blk_T;
	cout << "\nEnter the length of the Torpedo Bulkhead in m: ";
	cin >> z.blk_L;
	cout << "\nEnter the height of the Torpedo Bulkhead in m: ";
	cin >> z.blk_H;
	cout << "\nEnter the number of layers in the Torpedo Bulkhead: ";
	cin >> z.blk_Lct;
	cout << "\nEnter the depth of each layer in the Torpedo Bulkhead: ";
	cin >> z.blk_D;

	Ship cur(x, y, z, _db, _par);

	cout << "\n\nHere is the detailed report: " << endl;
	cur.output();

	bool change = false;

	cout << "\nDo you wish to change one of the variables you set? Enter 0 for no (and exit) and 1 for yes: ";
	cin >> change;

	while (change){
		cout << "What do you want to change? Enter the number corresponding to the category you want to change." << endl;
		cout << "1. Length, Beam, Draft, Freeboard, Year Laid Down, Block Coefficient" << endl;
		cout << "2. Max Speed, Cruise Speed, Range, Coal Percentage" << endl;
		cout << "3. Length of Superstructure, Number of Shafts, Number of Propeller Blades" << endl;
		cout << "4. Aftbody Shape, Engine Type, Transmission Type, Operating Region" << endl;
		cout << "5. Double Bottom, Parallel Mid-body, Length of Entrance, Length of Run" << endl;
		cout << "6. Main Belt Upper Thickness, Main Belt Lower Thickness, Main Belt Length, Main Belt Height, Main Belt Depth" << endl;
		cout << "7. End Belt Upper Thickness, End Belt Lower Thickness, Upper Belt Upper Thickness, Upper Belt Lower Thickness, Upper Belt Length" << endl;
		cout << "8. Main Deck Thickness, Main Deck Height, Main Deck Coverage" << endl;
		cout << "9. Weather Deck Thickness, Weather Deck Coverage, Splinter Deck Thickness, Splinter Deck Coverage, End Deck Thickness" << endl;
		cout << "10. Bulkhead Length, Bulkhead Height, Bulkhead Layer Numbers, Bulkhead Layer Depth" << endl;

		int i, j;
		cin >> i;
		cout << "What in this category do you want to change? Enter the number corresponding to the item you want to change. If you pick the first item in the category that would be 1 and the next would be 2, and so on." << endl;
		cin >> j;
		cout << "Input the new value: ";

		switch(i){
			case 1:
				switch(j){
					case 1: cin >> x.Lpp; goto esc;
					case 2: cin >> x.B; goto esc;
					case 3: cin >> x.D; goto esc;
					case 4: cin >> x.fB; x.fB -= x.D; goto esc;
					case 5: cin >> x.Year; goto esc;
					case 6: cin >> x.cB; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 2:
				switch(j){
					case 1: cin >> x.Vk; goto esc;
					case 2: cin >> x.Vc; goto esc;
					case 3: cin >> x.Range; goto esc;
					case 4: cin >> x.Coalpct; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 3:
				switch(j){
					case 1: cin >> x.Lspus; goto esc;
					case 2: cin >> y.Shafts; goto esc;
					case 3: cin >> y.Z; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 4:
				switch(j){
					case 1: cin >> sFaa; y.Faa = _as.ParseEnum(sFaa); goto esc;
					case 2: cin >> sEng; y.Eng = _e.ParseEnum(sEng); goto esc;
					case 3: cin >> sGear; y.Gear = _g.ParseEnum(sGear); goto esc;
					case 4: cin >> sSA; y.SA = _sa.ParseEnum(sSA); goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 5:
				switch(j){
					case 1: cin >> _db; goto esc;
					case 2: cin >> _par; goto esc;
					case 3: cin >> x.e; goto esc;
					case 4: cin >> x.r; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 6:
				switch(j){
					case 1: cin >> z.mb_Ttop; goto esc;
					case 2: cin >> z.mb_Tbot; goto esc;
					case 3: cin >> z.b_L; goto esc;
					case 4: cin >> z.b_H; goto esc;
					case 5: cin >> z.b_Db; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 7:
				switch(j){
					case 1: cin >> z.eb_Ttop; goto esc;
					case 2: cin >> z.eb_Tbot; goto esc;
					case 3: cin >> z.ub_Ttop; goto esc;
					case 4: cin >> z.ub_Tbot; goto esc;
					case 5: cin >> z.b_uL; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 8:
				switch(j){
					case 1: cin >> z.md_T; goto esc;
					case 2: cin >> z.md_H; goto esc;
					case 3: cin >> z.md_P; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 9:
				switch(j){
					case 1: cin >> z.wd_T; goto esc;
					case 2: cin >> z.wd_P; goto esc;
					case 3: cin >> z.sd_T; goto esc;
					case 4: cin >> z.sd_P; goto esc;
					case 5: cin >> z.ed_T; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			case 10:
				switch(j){
					case 1: cin >> z.blk_L; goto esc;
					case 2: cin >> z.blk_H; goto esc;
					case 3: cin >> z.blk_Lct; goto esc;
					case 4: cin >> z.blk_D; goto esc;
					default: cout << "Invalid Item Number!" << endl; continue;
				}
			default: cout << "Invalid Category Number!" << endl; continue;
		}

		esc:

		cur = Ship(x, y, z, _db, _par);

		cout << "\n\nHere is the detailed report: " << endl;
        cur.output();

		cout << "\nDo you wish to change one of the twenty-one variables you set? Enter 0 for no (and exit) and 1 for yes: ";
		cin >> change;

	}

	return 0;
}
