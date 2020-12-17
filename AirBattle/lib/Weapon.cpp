#include "pch.h"
#include "Weapon.h"
#include <math.h>

namespace AirBattle {
	Weapon::Weapon(const double& r, const double& f_r, const int& dmg) {
		if (r < 0)
			throw std::runtime_error("Invalid radius");
		range = r;
		if (f_r < 0.0)
			throw std::runtime_error("Invalid fire rate");
		fire_rate = f_r;
		if (dmg < 0)
			throw std::runtime_error("Invalid damage");
		damage = dmg;
		last_shot = 0;
	}
	Weapon::Weapon(const Weapon& a) : range(a.range), fire_rate(a.fire_rate), damage(a.damage), last_shot(a.last_shot) {

	}


	void Weapon::set_range(const int& r) {
		if (r < 0)
			throw std::runtime_error("Invalid radius");
		range = r;
	}
	void Weapon::set_fire_rate(const double& f) {
		if (f < 0.0)
			throw std::runtime_error("Invalid fire rate");
		fire_rate = f;
	}
	void Weapon::set_damage(const int& d) {
		if (d < 0.0)
			throw std::runtime_error("Invalid fire rate");
		damage = d;
	}
	void Weapon::set_last_shot(const int& t) {
		if (t < 0)
			throw std::runtime_error("Invalid time");
		last_shot = t;
	}


	bool Weapon::is_reloading(const int& t) const {
		return (t - last_shot) < fire_rate;
	}


	std::ostream& operator <<(std::ostream& os, const Weapon& Obj) {
		return Obj.show(os);
	}
}