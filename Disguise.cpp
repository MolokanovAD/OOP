#include "Disguise.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"

namespace AirBattle {

	Disguise::Disguise() {
		max_hp = 1200;
		hp = 1200;
		det_coef = 0.8;
		acc_coef = 0.75;
		speed = 1200;
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
	Disguise::Disguise(const Disguise& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		det_coef = a.det_coef;
		acc_coef = a.acc_coef;
		weapon = new Weapon * [L];
		for (int i = 0; i < L; i++) {
			weapon[i] = a.weapon[i]->clone();
		}
	}
	Disguise::Disguise(Disguise&& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		det_coef = a.det_coef;
		acc_coef = a.acc_coef;
		weapon = a.weapon;
		for (int i = 0; i < L; i++)
			weapon[i] = nullptr;
	}
	Disguise::~Disguise() {
		for (int i = 0; i < L; i++)
			delete weapon[i];
		delete[] weapon;
	}


	void Disguise::getDamage(int dmg, int type, double acc) {
		if (type == 1) {
			std::srand(time(0));
			int val = rand() % 100;
			if (val > acc * acc_coef * 100)
				return;
		}
		if (hp > dmg)
			hp -= dmg;
		else
			hp = 0;
	}


	void Disguise::set_det_coef(int& a) {
		if (a < 0.0 || a > 1.0)
			throw std::exception("Invalid detection coefficient");
		det_coef = a;
	}
	void Disguise::set_acc_coef(int&a) {
		if (a < 0.0 || a > 1.0)
			throw std::exception("Invalid accuracy coefficient");
		acc_coef = a;
	}


	void Disguise::Free() {
		Disguise::~Disguise();
	}
	std::ostream& Disguise::show(std::ostream& c)const {
		return c << "Disguise plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "Hidding coefficient: " << det_coef << std::endl << "Accuracy reduction coefficient" << acc_coef << std::endl << std::endl;
	}
	Disguise* Disguise::clone() const{
		return new Disguise(*this);
	}
}