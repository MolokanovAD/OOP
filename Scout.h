#ifndef _SCOUT_H_
#define _SCOUT_H_
#include "Plane.h"
#define G 3
#define L 4
namespace AirBattle {
	class Scout :public Plane {
	protected:
		double ignore_coef;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Scout();
		Scout(const Scout&);
		Scout(Scout&&);
		~Scout();

		double get_ignore_coef() const { return ignore_coef; }

		void set_ignore_coef(double&);

		virtual void Free();
		virtual Scout* clone() const;
		virtual int iam() { return 4; }
		virtual void getDamage(int dmg, int type, double acc = 1.0);
	};
}
#endif