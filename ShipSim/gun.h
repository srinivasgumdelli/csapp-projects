#ifndef GUN_H
#define GUN_H

#include "enumparser.h"
#include "main.h"
#include "ballistic.h"

class Gun{
	public:	
		struct Data{
			float d;
			float L;
			//float W;	// not in current use
			int	  Y;
			float SpB;
		};
	
		Gun(placement _l, bool _b, bool _e, float _s, gunData _g, mount _m) : loc(_l), beam(_b), echelon(_e), spread(_s), g(_g), head(_m), next(NULL);
		
		~Gun();
		Gun(const Gun &other);
		const Gun &operator=(const Gun &src);
		
		float Dbarb(float barrelMounts);
		float Wshell();
		float Wgun();
		float _Wgun(unsigned int bM);
		float Wammo();
		shell Range();

		Placement 		loc;
		bool 			beam;
		bool			echelon;
		float			spread;	
		float			maxAngle;
		Data			g;
		extern Mount	*head;
		Gun				*next;
	private:
		void copyB(const Gun &src);
		void clear();
		
		class Mount{
			public:
				Mount() : barrel_ct(0), mount_H(0), next(NULL);
				inline ~Mount(){
					delete next;
				} /* Correct this! Untested and unreasonable! */
			
				unsigned int 	barrel_ct;
				unsigned int 	mount_H;	// height relative to deck
				//MountType 		mT;		// currently assume Turret
				Mount 			*next;
			private:
		};
};

#endif	// GUN_H