#include "pch.h"
#include "Plane.h"
#include "Table.h"
#include "Gun.h"
#include "Launcher.h"
#include "Anti_Rocket.h"
namespace AirBattle {
	Plane::Plane(const int& HP, const int& MAXHP, const int& SPEED, const int& w_t, const double& xx, const double& yy, const double& r_d, const int& guns) {
		if (MAXHP < 0)
			throw std::runtime_error("Wrong max hp");
		max_hp = MAXHP;
		if (HP < 0 || HP > MAXHP)
			throw std::runtime_error("Wrong hp");
		hp = HP;
		if (SPEED < 0)
			throw std::runtime_error("Wrong speed");
		speed = SPEED;
		if (w_t < 0)
			throw std::runtime_error("Wrong weapons total");
		weapons_total = w_t;
		if (r_d < 0)
			throw std::runtime_error("Wrong weapons total");
		radio_detection = r_d;
		x = xx;
		y = yy;
		for (int i = 0; i < guns; i++) {
			weapon.push_back(new Gun);
		}
		for (int i = guns; i < w_t; i++) {
			weapon.push_back(new Launcher);
		}
	}
	Plane::Plane(const Plane& a) :x(a.x), y(a.y), max_hp(a.max_hp), hp(a.hp), speed(a.speed), weapons_total(a.weapons_total), radio_detection(a.radio_detection) {

	}
	Plane::Plane(Plane&& a) : x(a.x), y(a.y), max_hp(a.max_hp), hp(a.hp), speed(a.speed), weapons_total(a.weapons_total), radio_detection(a.radio_detection) {

	}


	const int Plane::get_fire_range()const {
		int r = 0;
		for (other_vector<Weapon*>::iterator i = weapon.begin(); i != weapon.end(); i++) {
			int t = (*i)->get_range();
			if (t > r)
				r = t;
		}
		return r;
	}
	bool Plane::is_spotted(Plane& spotter, Table& planes_table, Table& players_table, const double& radio_detection_) const {
		double det_decrease = planes_table.get_det_decr(spotter.x, spotter.y);
		double disg_decr = players_table.get_disg_decr(x, y);
		double disg = disguise_increase() * disg_decr;
		if (disg < 1.0)
			disg = 1.0;
		double res_detection = radio_detection_ * det_decrease / disg;
		double distance = get_distance(spotter.x, spotter.y);
		if (distance < res_detection)
			return true;
		return false;
	}

	double Plane::get_distance(const int& xx, const int& yy) const {
		return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
	}



	void Plane::set_hp(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid hp");
		hp = a;
	}
	void Plane::set_max_hp(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid max hp");
		max_hp = a;
	}
	void Plane::set_speed(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid speed");
		speed = a;
	}
	void Plane::set_weapons_total(const int& a) {
		if (a < 0)
			throw std::runtime_error("Invalid amount of weapons");
		weapons_total = a;
	}
	void Plane::set_x(const double& a) {
		if (a < 0)
			throw std::runtime_error("Invalid x");
		x = a;
	}
	void Plane::set_y(const double& a) {
		if (a < 0)
			throw std::runtime_error("Invalid y");
		y = a;
	}
	void Plane::set_radio_detection(const double& a) {
		if (a < 0)
			throw std::runtime_error("Invalid radio detection");
		radio_detection = a;
	}
	void Plane::set_last_shot(const int& time) {
		if (time < 0)
			throw std::runtime_error("Time < 0");
		last_shot = time;
	}

	void Plane::Add_weapon(Weapon* w) {
		if (weapon.size() >= weapons_total)
			throw std::runtime_error("Overload");
		weapon.push_back(w->clone());
	}
	void Plane::Delete_weapon(const int& b) {
		other_vector<Weapon*>::iterator i = weapon.begin();
		if (b >= weapon.size() || b < 0)
			throw std::runtime_error("Wrong index");
		delete* (i + b);
		weapon.erase(i + b);
	}
	bool Plane::Fire(Plane* goal, Table& my, Table& enemy, const int& time, const double& radio_detection_) {//радиус обнаружения брать у звена
		if (!is_reloading(time)) {
			double acc = goal->accuracy_decrease();
			double distance = get_distance(goal->get_x(), goal->get_y());
			double pro_decr = 1.0;
			Anti_Rocket* ptr = dynamic_cast<Anti_Rocket*>(this);
			if (ptr)
				pro_decr = enemy.get_pro_decr(x, y);
			for (other_vector<Weapon*>::iterator i = weapon.begin(); i != weapon.end(); i++) {
				if (!(*i)->is_reloading(time) && distance < (*i)->get_range() && goal->is_spotted(*this, enemy, my, radio_detection_)) {
					Gun* g = dynamic_cast<Gun*>(*i);
					if (g) {
						g->set_last_shot(time);
						goal->getDamage(g->get_damage(), acc * g->get_accuracy(), true, pro_decr);
					}
					else {
						Launcher* l = dynamic_cast<Launcher*>(*i);
						l->set_last_shot(time);
						goal->getDamage(l->get_damage(), 1.0, false, pro_decr);
					}
					set_last_shot(time);
					return true;
				}
			}
		}
		return false;
	}


	std::ostream& operator <<(std::ostream& c, const Plane& Obj) {
		return Obj.show(c);
	}
}