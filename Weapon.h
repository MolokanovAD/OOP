#ifndef _WEAPON_H_
#define _WEAPON_H_
#include <iostream>

namespace AirBattle {
	class Plane;
	class Weapon {
	protected:
		int range;
		double fire_rate;
		int damage;
		virtual std::ostream& show(std::ostream&)const = 0;
	public:
		int get_range() const { return range; }
		double get_fire_rate() const { return fire_rate; }
		int get_damage() const { return damage; }

		void set_range(int);
		void set_fire_rate(double);
		void set_damage(int);

		virtual Weapon* clone() const = 0;
		virtual int iam()const = 0;
		virtual void shot(Plane&) = 0;
		friend std::ostream& operator <<(std::ostream&, const Weapon&);
	};
}
#endif