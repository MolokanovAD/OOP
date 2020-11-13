#ifndef _PLANE_H_
#define _PLANE_H_
#include <iostream>

namespace AirBattle {
	class Weapon;
	class Plane {
	protected:
		int hp;
		int max_hp;
		int speed;
		int weapons_total;
		double x;
		double y;
		Weapon** weapon;
		double radio_detection;
		virtual std::ostream& show(std::ostream&) const = 0;
	public:
		const int get_hp()const { return hp; }
		const int get_max_hp()const { return max_hp; }
		const int get_speed()const { return speed; }
		const int get_weapons_total()const { return weapons_total; }
		const double get_x()const { return x; }
		const double get_y()const { return y; }
		const double get_radio_detection()const { return radio_detection; }

		void set_hp(int&);
		void set_max_hp(int&);
		void set_speed(int&);
		void set_weapons_total(int&);
		void set_x(double&);
		void set_y(double&);
		void set_radio_detection(double&);

		int get_fire_range() const;

		void Fire(Plane*);
		virtual void Free() = 0;
		virtual Plane* clone() const = 0;
		virtual int iam() = 0;
		virtual void getDamage(int,int,double) = 0;
		friend std::ostream& operator <<(std::ostream&, const Plane&);
	};
}
#endif