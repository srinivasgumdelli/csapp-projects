#ifndef GUN_H
#define GUN_H

#include "enumparser.h"

class Gun{
	public:	
		Battery(placement _l, bool _b, bool _e, float _s, gunData _g, mount _m) : loc(_l), beam(_b), echelon(_e), spread(_s), g(_g), head(_m), next(NULL);
		
		~Battery();
		Battery(const Battery &other);
		const Battery &operator=(const Battery &src);
		
		float BarbetteDiameter(float barrelMounts, float gunDiameter);
		float Shellweight(float gunYear, float gunDiameter, float gunCaliber);
		float Wammo();
	
		Placement 		loc;
		bool 			beam;
		bool			echelon;
		float			spread;	
		extern Data		g;
		extern Mount	*head;
	private:
		void copyB(const Battery &src);
		
		class Mount{
			public:
				unsigned int 	barrel_ct;
				unsigned int 	mount_H;	// height relative to deck
				MountType 		mT;
				Mount 			*next;
			private:
		};
		class Data{
			float d;
			float L;
			float W;
			float Y;
			float SpB;
		};
};

#endif	// GUN_H