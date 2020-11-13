#include "Scout.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"
namespace AirBattle {

	Scout::Scout() {
		max_hp = 800;
		hp = 800;
		ignore_coef = 0.8;
		speed = 1600;
		weapons_total = L;
		radio_detection = 900;
		weapon = new Weapon * [L];
		for (int i = 0; i < G; i++) {
			weapon[i] = new Gun;
		}
		for (int i = G; i < L; i++) {
			weapon[i] = new Launcher;
		}
	}
	Scout::Scout(const Scout& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		ignore_coef = a.ignore_coef;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		weapon = new Weapon * [L];
		for (int i = 0; i < L; i++) {
			weapon[i] = a.weapon[i]->clone();
		}
	}
	Scout::Scout(Scout&& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		ignore_coef = a.ignore_coef;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		weapon = a.weapon;
	}
	Scout::~Scout() {
		if(weapon)
			for (int i = 0; i < L; i++)
				delete weapon[i];
		delete[] weapon;
	}

	void Scout::set_ignore_coef(double& a) {
		if (a < 0.0 || a > 1.0)
			throw std::exception("Invalid detection coefficient");
		ignore_coef = a;
	}

	void Scout::getDamage(int dmg, int type, double acc) {
		if (type == 1) {
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


	void Scout::Free(){
		Scout::~Scout();
	}
	std::ostream& Scout::show(std::ostream& c)const {
		return c << "Scout plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "Disguise ignoring coefficient: " << ignore_coef << std::endl << std::endl;
	}
	Scout* Scout::clone() const {
		return new Scout(*this);
	}
}