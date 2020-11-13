#ifndef _ANTI_ROCKET_H_
#define _ANTI_ROCKET_H_
#include "Plane.h"
#define G 3
#define L 6
namespace AirBattle {
	class Anti_Rocket : public Plane {
	protected:
		int pro;
		int pro_max;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Anti_Rocket();
		Anti_Rocket(const Anti_Rocket&);
		Anti_Rocket(Anti_Rocket&&);
		~Anti_Rocket();

		int get_pro()const { return pro; }
		int get_pro_max()const { return pro_max; }

		void set_pro(int&);
		void set_pro_max(int&);

		virtual void Free();
		virtual Anti_Rocket* clone() const;
		virtual int iam() { return 1; }
		virtual void getDamage(int dmg, int type, double acc = 1.0);
	};
}
#endif