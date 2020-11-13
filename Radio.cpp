#include "Radio.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"

namespace AirBattle {

	Radio::Radio() {
		max_hp = 1400;
		hp = 1400;
		pro_decr = 0.8;
		det_decr = 0.8;
		disguise_decr = 0.8;
		speed = 1000;
		weapons_total = L;
		radio_detection = 500;
		weapon = new Weapon * [L];
		for (int i = 0; i < G; i++) {
			weapon[i] = new Gun;
		}
		for (int i = G; i < L; i++) {
			weapon[i] = new Launcher;
		}
	}
	Radio::Radio(const Radio& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		pro_decr = a.pro_decr;
		disguise_decr = a.disguise_decr;
		det_decr = a.det_decr;
		weapon = new Weapon * [L];
		for (int i = 0; i < L; i++) {
			weapon[i] = a.weapon[i]->clone();
		}
	}
	Radio::Radio(Radio&& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		pro_decr = a.pro_decr;
		disguise_decr = a.disguise_decr;
		det_decr = a.det_decr;
		weapon = a.weapon;
		for (int i = 0; i < L; i++)
			weapon[i] = nullptr;
	}
	Radio::~Radio() {
		for (int i = 0; i < L; i++)
			delete weapon[i];
		delete[] weapon;
	}


	void Radio::getDamage(int dmg, int type, double acc) {
		//if (type == 1) {
			std::srand(time(0));
			int val = rand() % 100;
			if (val > acc * 100) {
				return;
			}
		//}
		if (hp > dmg)
			hp -= dmg;
		else
			hp = 0;
	}
	void Radio::set_pro_decr(double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::exception("Invalid pro coefficient");
		pro_decr = a;
	}
	void Radio::set_disguise_decr(double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::exception("Invalid disguise coefficient");
		disguise_decr = a;
	}
	void Radio::set_det_decr(double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::exception("Invalid detection coefficient");
		det_decr = a;
	}

	void Radio::Free() {
		Radio::~Radio();
	}
	std::ostream& Radio::show(std::ostream& c)const {
		return c << "Radio-fighter plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "Disguise supression coefficient: " << disguise_decr << std::endl << "PRO supression coefficient: " << pro_decr  << std::endl << "Detection supression coefficient: " << det_decr << std::endl << std::endl;
	}
	Radio* Radio::clone() const {
		return new Radio(*this);
	}
}