#ifndef _DISGUISE_H_
#define _DISGUISE_H_
#include "Plane.h"
#define G 3
#define L 6
namespace AirBattle {
	class Disguise :public Plane {
	protected:
		double det_coef;
		double acc_coef;
		virtual std::ostream& show(std::ostream&) const;
	public:
		Disguise();
		Disguise(const Disguise&);
		Disguise(Disguise&&);
		~Disguise();

		double get_det_coef()const { return det_coef; }
		double get_acc_coef()const { return acc_coef; }

		void set_det_coef(int&);
		void set_acc_coef(int&) ;

		virtual void Free();
		virtual Disguise* clone() const;
		virtual int iam() { return 2; }
		virtual void getDamage(int dmg, int type, double acc = 1.0);
	};
}
#endif