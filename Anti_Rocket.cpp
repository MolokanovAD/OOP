#include "Anti_Rocket.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"
namespace AirBattle {

	Anti_Rocket::Anti_Rocket() {
		max_hp = 1400;
		hp = 1400;
		pro_max = 5;
		pro = 5;
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
	Anti_Rocket::Anti_Rocket(const Anti_Rocket& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		pro = a.pro;
		pro_max = a.pro_max;
		weapon = new Weapon * [L];
		for (int i = 0; i < L; i++) {
			weapon[i] = a.weapon[i]->clone();
		}
	}
	Anti_Rocket::Anti_Rocket(Anti_Rocket&& a) {
		max_hp = a.max_hp;
		hp = a.hp;
		speed = a.speed;
		weapons_total = a.weapons_total;
		radio_detection = a.radio_detection;
		pro = a.pro;
		pro_max = a.pro_max;
		weapon = a.weapon;
		for (int i = 0; i < L; i++)
			weapon[i] = nullptr;
	}
	Anti_Rocket::~Anti_Rocket() {
		for (int i = 0; i < L; i++)
			delete weapon[i];
		delete[] weapon;
	}


	void Anti_Rocket::set_pro_max(int& a) {
		if (a < 0)
			throw std::exception("Invalid max hp");
		pro_max = a;
	}
	void Anti_Rocket::set_pro(int& a) {
		if (a < 0)
			throw std::exception("Invalid max hp");
		pro = a;
	}


	void Anti_Rocket::getDamage(int dmg,int type,double acc) {
		if (type == 2 && pro) {
			std::srand(time(0));
			int val = rand() % 100;
			if (val <= /*pro_coef **/ 100) { //воздействие РЭБ
				pro--;
				return;
			}
		}
		if (type == 1) {
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

	void Anti_Rocket::Free() {
		Anti_Rocket::~Anti_Rocket();
	}
	std::ostream& Anti_Rocket::show(std::ostream& c)const {
		return c << "Anti-Rocket plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "PRO: " << pro << "/" << pro_max << std::endl << std::endl;
	}
	Anti_Rocket* Anti_Rocket::clone() const {
		return new Anti_Rocket(*this);
	}
}