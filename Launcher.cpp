#include "Launcher.h"
namespace AirBattle {
	Launcher::Launcher(int r, double a, int f, int d, int m_a) {
		if (r < 0)
			throw std::exception("Invalid radius");
		range = r;
		if (f < 0.0)
			throw std::exception("Invalid fire rate");
		fire_rate = f;
		if (a < 0)
			throw std::exception("Invalid ammo");
		ammo = a;
		if (d < 0)
			throw std::exception("Invalid damage");
		damage = d;
		if (a < 0)
			throw std::exception("Invalid max ammo");
		max_ammo = m_a;
	}
	void Launcher::set_ammo(int& a) {
		if (a < 0)
			throw std::exception("Invalid fire rate");
		ammo = a;
	}
	void Launcher::set_max_ammo(int& a) {
		if (a < 0)
			throw std::exception("Invalid fire rate");
		max_ammo = a;
	}
	Launcher* Launcher::clone() const {
		return new Launcher(*this);
	}
	std::ostream& Launcher::show(std::ostream& os)const {
		return os;
	}
	void Launcher::shot(Plane& Goal) {
		int x, y;
		//Goal.getCoordinates(x,y);

	}
}