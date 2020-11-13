#ifndef _RADIO_H_
#define _RADIO_H_
#include "Plane.h"
#define G 3
#define L 6
namespace AirBattle {
	class Radio :public Plane {
	protected:
		double pro_decr;
		double disguise_decr;
		double det_decr;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Radio();
		Radio(const Radio&);
		Radio(Radio&&);
		~Radio();

		double get_pro_decr() const { return pro_decr; }
		double get_disguise_decr() const { return disguise_decr; }
		double get_det_decr() const { return det_decr; }

		void set_pro_decr(double&);
		void set_disguise_decr(double&);
		void set_det_decr(double&);

		virtual void Free();
		virtual Radio* clone() const;
		virtual int iam() { return 3; }
		virtual void getDamage(int dmg, int type, double acc = 1.0);
	};
}
#endif