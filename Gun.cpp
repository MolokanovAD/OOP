#include "Gun.h"
namespace AirBattle {
	Gun::Gun(int r, double a, double f, int d) {
		if (r < 0)
			throw std::exception("Invalid radius");
		range = r;
		if (a < 0.0)
			throw std::exception("Invalid accuracy");
		accuracy = a;
		if (f < 0.0)
			throw std::exception("Invalid fire rate");
		fire_rate = f;
		if (d < 0)
			throw std::exception("Invalid damage");
		damage = d;
	}
	Gun::Gun(const Gun& a) {
		accuracy = a.accuracy;
		damage = a.damage;
		range = a.range;
		fire_rate = a.fire_rate;
	}
	void Gun::set_accuracy(double a) {
		if (a < 0.0)
			throw std::exception("Invalid accuracy");
		accuracy = a;
	}
	Gun* Gun::clone() const {
		return new Gun(*this);
	}
	std::ostream& Gun::show(std::ostream& os)const {
		return os;
	}
	void Gun::shot(Plane& Goal) {
		int x, y;
		int factor = iam();
		//Goal.getCoordinates(x,y);

	}
}