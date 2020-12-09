#include "Launcher.h"
#include "Table.h"
#include "Plane.h"
#include <time.h>
namespace AirBattle {
	Launcher::Launcher(int r, double f, int d, int a, int m_a):Weapon(r,f,d) {
		if (a < 0 || a > m_a)
			throw std::runtime_error("Invalid ammo");
		ammo = a;
		if (a < 0)
			throw std::runtime_error("Invalid max ammo");
		max_ammo = m_a;
	}
	void Launcher::set_ammo(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid fire rate");
		ammo = a;
	}
	void Launcher::set_max_ammo(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid fire rate");
		max_ammo = a;
	}
	Launcher* Launcher::clone() const {
		return new Launcher(*this);
	}
	std::ostream& Launcher::show(std::ostream& os)const {
		return os;
	}
	bool Launcher::shot(const double& x, const double& y, const double& distance, Table& enemy, const int& time) {
		if (distance > range || is_reloading(time) || ammo == 0)
			return false;
		set_last_shot(time);
		ammo--;
		try {
			double pro_decr = enemy.get_pro_decr(x, y);
			enemy.find_by_coordinates(x, y).getDamage(damage, 1.0, false, pro_decr);
			return true;
		}
		catch (std::runtime_error& a) {
			return false;
		}
	}
}