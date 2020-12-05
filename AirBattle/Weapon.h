#ifndef _WEAPON_H_
#define _WEAPON_H_
#include <iostream>

namespace AirBattle {
	class Table;
	class Weapon {
	protected:
		double range;
		double fire_rate;
		int last_shot;
		int damage;
		virtual std::ostream& show(std::ostream&)const = 0;
	public:
		Weapon(const double& r, const double& f_r,const int& dmg);
		Weapon(const Weapon&);

		double get_range() const { return range; }
		double get_fire_rate() const { return fire_rate; }
		int get_damage() const { return damage; }

		void set_range(const int&);
		void set_fire_rate(const double&);
		void set_damage(const int&);
		void set_last_shot(const int&);

		bool is_reloading(const int&)const;

		virtual ~Weapon() {}
		virtual Weapon* clone() const = 0;
		virtual bool iam()const = 0;
		virtual bool shot(const double&,const double&,  const double&, Table&,const int&) = 0;
		friend std::ostream& operator <<(std::ostream&, const Weapon&);
	};
}
#endif