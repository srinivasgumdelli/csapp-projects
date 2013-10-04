#ifndef ENUMPARSER_H_INCLUDED
#define ENUMPARSER_H_INCLUDED

#include <map>
#include <string>
#include <vector>

using namespace std;

/* Base Code Written by Eclipse     on StackOverflow.com
 * Editted by           bluish      on StackOverflow.com
 * Modified by          Kelsey Yuen
 */

enum AftShape { V, N, U };
enum Engin {Diesel2stk, Diesel4stk, QuadExp, TripExp, SimExp, SteamTur};
enum Gearbox { Direct, Geared, Turbo_Electric };
enum Service_Allowance { EurAus = 25, EurEas = 25, NAe = 25, NAw = 35, Pac = 30, Trial = 0};

enum MountType { placeholder };
enum Placement { f, m, a };

typedef struct{
    Gearbox g;
    float NUm;
    float FcT;
    float Wgear;
} ShaftType;

typedef struct{
    Engin e;
    float K1;
    float K2;
    float FcE;
} EngineType;

extern ShaftType Shaft[];
extern EngineType Engine[];

template <>
inline EnumParser<Placement>::Enumparser(){
	enumMap["Forward"] 	= f;
	enumMap["Midship"] 	= m;
	enumMap["Aft"] 		= a;
}

template <typename T>
class EnumParser{
    map <string, T> enumMap;

    public:
        EnumParser(){};

        T ParseEnum(const string &value){
            typename map <string, T>::const_iterator iValue = enumMap.find(value);
            /*if (iValue  == enumMap.end())
                throw runtime_error("");*/
            return iValue->second;
        }
};

template <>
inline EnumParser<AftShape>::EnumParser(){
    enumMap["V"] = V;
    enumMap["N"] = N;
    enumMap["U"] = U;
}

template <>
inline EnumParser<Engin>::EnumParser(){
    enumMap["Diesel-2stroke"] = Diesel2stk;
    enumMap["Diesel-4stroke"] = Diesel4stk;
    enumMap["Quad-Expansion"] = QuadExp;
    enumMap["Triple-Expansion"] = TripExp;
    enumMap["Simple-Expansion"] = SimExp;
    enumMap["Steam-Turbine"] = SteamTur;
}

template <>
inline EnumParser<Gearbox>::EnumParser(){
    enumMap["Direct"] = Direct;
    enumMap["Geared"] = Geared;
    enumMap["Turbo-Electric"] = Turbo_Electric;
}

template <>
inline EnumParser<Service_Allowance>::EnumParser(){
    enumMap["Europe-Australia"] = EurAus;
    enumMap["Europe-EastAsia"] = EurEas;
    enumMap["NAeast"] = NAe;
    enumMap["NAwest"] = NAw;
    enumMap["Pacific"] = Pac;
    enumMap["Trial"] = Trial;
}

#endif // ENUMPARSER_H_INCLUDED
