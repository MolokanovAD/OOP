#include "Weapon.h"

namespace AirBattle {

	void Weapon::set_range(int r) {
		if (r < 0)
			throw std::exception("Invalid radius");
		range = r;
	}
	void Weapon::set_fire_rate(double f) {
		if (f < 0.0)
			throw std::exception("Invalid fire rate");
		fire_rate = f;
	}
	void Weapon::set_damage(int d) {
		if (d < 0.0)
			throw std::exception("Invalid fire rate");
		damage = d;
	}
	std::ostream& operator <<(std::ostream& os, const Weapon& Obj) {
		return Obj.show(os);
	}
}