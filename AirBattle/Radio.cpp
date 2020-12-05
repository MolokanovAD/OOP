#include "Radio.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"

namespace AirBattle {


	Radio::Radio(const double& xx, const double& yy, const int& max_hp_,const int& hp_, const double& p_d, const double& disg_d, const double& det_d, const int& speed_, const int& guns, const int& weapons_total_,const double& radio_detection_) :Plane(hp_, max_hp_, speed_, weapons_total_, xx, yy, radio_detection_,guns) {
		pro_decr = p_d;
		disguise_decr = disg_d;
		det_decr = det_d;
	}
	Radio::Radio(const Radio& a):Plane(a) {
		pro_decr = a.pro_decr;
		disguise_decr = a.disguise_decr;
		det_decr = a.det_decr;
		for (std::vector<Weapon*>::const_iterator i = a.weapon.begin(); i != a.weapon.end(); i++)
			weapon.push_back((*i)->clone());
	}
	Radio::Radio(Radio&& a):Plane(a) {
		pro_decr = a.pro_decr;
		disguise_decr = a.disguise_decr;
		det_decr = a.det_decr;
		weapon = std::move(a.weapon);
	}
	Radio::~Radio() {
		while (!weapon.empty()) {
			std::vector<Weapon*>::const_iterator i = weapon.end() - 1;
			delete (*i);
			weapon.erase(i);
		}
	}


	
	void Radio::set_pro_decr(const double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid pro coefficient");
		pro_decr = a;
	}
	void Radio::set_disguise_decr(const double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid disguise coefficient");
		disguise_decr = a;
	}
	void Radio::set_det_decr(const double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid detection coefficient");
		det_decr = a;
	}

	void Radio::getDamage(const int& dmg, const double& acc, bool type, const double& pro_coef) {
		if (type) {
		srand(time(0));
		int val = rand() % 100;
		if (val > acc * 100)
			return;
		}
		if (hp > dmg)
			hp -= dmg;
		else
			hp = 0;
	}
	std::ostream& Radio::show(std::ostream& c)const {
		return c << "Radio-fighter plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "Disguise supression coefficient: " << disguise_decr << std::endl << "PRO supression coefficient: " << pro_decr  << std::endl << "Detection supression coefficient: " << det_decr << std::endl << std::endl;
	}
	Radio* Radio::clone() const {
		return new Radio(*this);
	}
}