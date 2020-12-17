#include "pch.h"
#include "Scout.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"
namespace AirBattle {


	Scout::Scout(const double& xx, const double& yy, const int& max_hp_, const int& hp_, const double& i_d, const int& speed_, const int& guns, const int& weapons_total_, const double& radio_detection_) :Plane(hp_, max_hp_, speed_, weapons_total_, xx, yy, radio_detection_, guns) {
		ignore_coef = i_d;
	}
	Scout::Scout(const Scout& a) : Plane(a) {
		ignore_coef = a.ignore_coef;
		for (other_vector<Weapon*>::iterator i = a.weapon.begin(); i != a.weapon.end(); i++)
			weapon.push_back((*i)->clone());
	}
	Scout::Scout(Scout&& a) : Plane(a) {
		ignore_coef = a.ignore_coef;
		weapon = std::move(a.weapon);
	}
	Scout::~Scout() {
		while (!weapon.empty()) {
			other_vector<Weapon*>::iterator i = weapon.end() - 1;
			delete (*i);
			weapon.erase(i);
		}
	}


	void Scout::set_ignore_coef(const double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid detection coefficient");
		ignore_coef = a;
	}


	void Scout::getDamage(const int& dmg, const double& acc, bool type, const double& pro_coef) {
		if (type) {
			std::srand(time(0));
			int val = rand() % 100;
			if (val > acc * 100) {
				return;
			}
		}
		if (hp > dmg)
			hp -= dmg;
		else
			hp = 0;
	}
	std::ostream& Scout::show(std::ostream& c)const {
		return c << "Scout plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "Disguise ignoring coefficient: " << ignore_coef << std::endl << std::endl;
	}
	Scout* Scout::clone() const {
		return new Scout(*this);
	}
}