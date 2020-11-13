#ifndef _SQUAD_H_
#define _SQUAD_H_
#include "Anti_Rocket.h"
#include "Disguise.h"
#include "Radio.h"
#include "Scout.h"
#include <iostream>
namespace AirBattle {

	class Squad{
	protected:
		int command;
		unsigned char N;
		double x;
		double y;
		/*inf_det
		inf_disg
		inf_pro*/
		Plane** plane;
	public:
		Squad(double x0 = 0.0, double y0 = 0.0,int anti_rocket = 1,int radio = 1,int disguise = 1, int scout = 1);
		Squad(const Squad&);
		Squad(Squad&&);
		~Squad();

		unsigned char get_N()const { return N; }
		int get_det_range()const;

		bool Delete(int&);
		bool Add(int&);

		friend std::ostream& operator <<(std::ostream&, const Squad&);
	};
}
#endif