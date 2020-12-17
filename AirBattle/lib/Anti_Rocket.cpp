#include "pch.h"
#include "Anti_Rocket.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"
namespace AirBattle {

	Anti_Rocket::Anti_Rocket(const double& xx, const double& yy, const int& max_hp_, const int& hp_, const int& pro_max_, const int& pro_, const int& speed_, const int& guns, const int& weapons_total_, const double& radio_detection_) :Plane(hp_, max_hp_, speed_, weapons_total_, xx, yy, radio_detection_, guns) {
		pro_max = pro_max_;
		pro = pro_;
	}
	Anti_Rocket::Anti_Rocket(const Anti_Rocket& a) : Plane(a) {
		pro = a.pro;
		pro_max = a.pro_max;
		for (other_vector<Weapon*>::iterator i = a.weapon.begin(); i != a.weapon.end(); i++)
			weapon.push_back((*i)->clone());
	}
	Anti_Rocket::Anti_Rocket(Anti_Rocket&& a) :Plane(a) {
		pro = a.pro;
		pro_max = a.pro_max;
		weapon = std::move(a.weapon);
	}
	Anti_Rocket::~Anti_Rocket() {
		while (!weapon.empty()) {
			other_vector<Weapon*>::iterator i(weapon.end() - 1);
			delete (*i);
			weapon.erase(i);
		}
	}



	void Anti_Rocket::set_pro_max(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid max hp");
		pro_max = a;
	}
	void Anti_Rocket::set_pro(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid max hp");
		pro = a;
	}


	void Anti_Rocket::getDamage(const int& dmg, const double& acc, bool type, const double& pro_coef) {
		if (!type && pro) {
			std::srand(time(0));
			int val = rand() % 100;
			if (val <= pro_coef * 100) {
				pro--;
				return;
			}
		}
		if (type) {
			int val = rand() % 100;
			if (val > acc * 100) {
				return;
			}
		}
		if (hp > dmg) {
			hp -= dmg;
		}
		else
			hp = 0;
	}
	std::ostream& Anti_Rocket::show(std::ostream& c)const {
		return c << "Anti-Rocket plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "PRO: " << pro << "/" << pro_max << std::endl << std::endl;
	}
	Anti_Rocket* Anti_Rocket::clone() const {
		return new Anti_Rocket(*this);
	}
}