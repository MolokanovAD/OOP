#include "Gun.h"
#include "Table.h"
#include "Plane.h"
#include <time.h>
namespace AirBattle {
	Gun::Gun(int r, double a, double f, int d):Weapon(r,f,d) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid accuracy");
		accuracy = a;
	}
	Gun::Gun(const Gun& a):Weapon(a) {
		accuracy = a.accuracy;
		damage = a.damage;
		range = a.range;
		fire_rate = a.fire_rate;
	}
	void Gun::set_accuracy(const double& a) {
		if (a < 0.0)
			throw std::runtime_error("Invalid accuracy");
		accuracy = a;
	}
	Gun* Gun::clone() const {
		return new Gun(*this);
	}
	std::ostream& Gun::show(std::ostream& os)const {
		return os;
	}
	bool Gun::shot(const double& x, const double& y,const double& distance,Table& enemy, const int& time) {
		if (distance > range || is_reloading(time))
			return false;
		set_last_shot(time);
		try {
			enemy.find_by_coordinates(x, y).getDamage(damage, accuracy, true, 1.0);
			return true;
		}
		catch (std::runtime_error& a) {
			return false;
		}
	}
}