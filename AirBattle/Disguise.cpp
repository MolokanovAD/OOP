#include "Disguise.h"
#include <time.h>
#include "Weapon.h"
#include "Gun.h"
#include "Launcher.h"

namespace AirBattle {

	Disguise::Disguise(const double& xx, const double& yy,const int& max_hp_, const int& hp_, const double& a_c, const double& d_c, const int& speed_, const int& guns, const int& weapons_total_, const double& radio_detection_):Plane(hp_,max_hp_,speed_,weapons_total_,xx,yy,radio_detection_,guns) {
		acc_coef = a_c;
		disg_coef = d_c;
	}
	Disguise::Disguise(const Disguise& a):Plane(a) {
		disg_coef = a.disg_coef;
		acc_coef = a.acc_coef;
		for (other_vector<Weapon*>::iterator i = a.weapon.begin(); i != a.weapon.end(); i++)
			weapon.push_back((*i)->clone());
	}
	Disguise::Disguise(Disguise&& a):Plane(a) {
		disg_coef = a.disg_coef;
		acc_coef = a.acc_coef;
		weapon = std::move(a.weapon);
	}

	Disguise::~Disguise() {
		while (!weapon.empty()) {
			other_vector<Weapon*>::iterator i = weapon.end() - 1;
			delete (*i);
			weapon.erase(i);
		}
	}




	void Disguise::set_det_coef(const int& a) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid detection coefficient");
		disg_coef = a;
	}
	void Disguise::set_acc_coef(const int&a) {
		if (a < 0.0 || a > 1.0)
			throw std::runtime_error("Invalid accuracy coefficient");
		acc_coef = a;
	}


	void Disguise::getDamage(const int& dmg,const double& acc, bool type, const double& pro_coef) {
		if (type) {
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
	std::ostream& Disguise::show(std::ostream& c)const {
		return c << "Disguise plane" << std::endl << "HP: " << hp << "/" << max_hp << std::endl << "speed: " << speed << std::endl << "Radio detection radius: " << radio_detection << std::endl << "Weapons on board: " << weapons_total << std::endl
			<< "Hidding coefficient: " << disg_coef << std::endl << "Accuracy reduction coefficient" << acc_coef << std::endl << std::endl;
	}
	Disguise* Disguise::clone() const{
		return new Disguise(*this);
	}
}