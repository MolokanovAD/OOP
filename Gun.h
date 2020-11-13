#ifndef _GUN_H_
#define _GUN_H_
#include "Weapon.h"
namespace AirBattle {
	class Gun : public Weapon
	{
	protected:
		double accuracy;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Gun(int r = 200, double a = 0.9, double f = 3.0, int d = 150);
		Gun(const Gun&);

		double get_accuracy() const { return accuracy; }

		void set_accuracy(double);

		virtual Gun* clone() const;
		virtual int iam()const { return 1; }
		virtual void shot(Plane&);
	};
}
#endif