#include "Plane.h"
namespace AirBattle {
	void Plane::set_hp(int& a) { 
		if (a < 0)
			throw std::exception("Invalid hp");
		hp = a;
	}
	void Plane::set_max_hp(int& a) {
		if (a < 0)
			throw std::exception("Invalid max hp");
		max_hp = a;
	}
	void Plane::set_speed(int& a) {
		if (a < 0)
			throw std::exception("Invalid speed");
		speed = a; 
	}
	void Plane::set_weapons_total(int& a) {
		if (a < 0)
			throw std::exception("Invalid amount of weapons");
		weapons_total = a; 
	}
	void Plane::set_x(double& a) {
		if (a < 0)
			throw std::exception("Invalid x");
		x = a;
	}
	void Plane::set_y(double& a) {
		if (a < 0)
			throw std::exception("Invalid y");
		y = a; 
	}
	void Plane::set_radio_detection(double& a) {
		if (a < 0)
			throw std::exception("Invalid radio detection");
		radio_detection = a;
	}


	int Plane::get_fire_range()const {
		return 0;
	}


	std::ostream& operator <<(std::ostream& c, const Plane& Obj) {
		return Obj.show(c);
	}
}