#include "Squad.h"
#include "Anti_Rocket.h"
#include "Disguise.h"
#include "Radio.h"
#include "Scout.h"
#include <iostream>
#include <math.h>
#include <time.h>
namespace AirBattle {
	Squad::Squad(const int& x0, const int& y0, const int& command, const int& anti_rocket, const int& radio, const int& disguise, const int& scout) {
		if (anti_rocket < 0 || anti_rocket > 4)
			throw std::runtime_error("Invalid amount of anti-rocket planes");
		if (radio < 0 || radio > 4)
			throw std::runtime_error("Invalid amount of radio planes");
		if (disguise < 0 || disguise > 4)
			throw std::runtime_error("Invalid amount of disguise planes");
		if (scout < 0 || scout > 4)
			throw std::runtime_error("Invalid amount of scout planes");
		if (command < 0 || command > 4)
			throw std::runtime_error("Invalid amount of scout planes");
		this->command = command;
		N = anti_rocket + radio + disguise + scout;
		if (N > 4)
			throw std::runtime_error("Too much planes");
		int i = 0;
		int cur = anti_rocket;
		
		for (; i < cur; i++)
			plane.push_back(new Anti_Rocket(x0,y0+12.0));
		cur += radio;
		for (; i < cur; i++)
			plane.push_back(new Radio(x0,y0+48.0));
		cur += disguise;
		for (; i < cur; i++)
			plane.push_back(new Disguise(x0,y0+84.0));
		cur += scout;
		for (; i < cur; i++)
			plane.push_back(new Scout(x0,y0+ 120.0));
		x = x0;
		y = y0;
	}
	Squad::Squad(const Squad& a) {
		command = a.command;
		N = a.N;
		x = a.x;
		y = a.y;
		for (int i = 0; i < N; i++)
			plane.push_back(a.plane[i]->clone());
	}
	Squad::Squad(Squad&& a) {
		command = a.command;
		N = a.N;
		x = a.x;
		y = a.y;
		plane = std::move(a.plane);
	}
	Squad::~Squad() {
		while (!plane.empty()) {
			std::vector<Plane*>::const_iterator i = plane.end() - 1;
			delete (*i);
			plane.erase(i);
		}
	}


	double Squad::get_det_range()const {
		double r = 0;
		for (auto i :plane) {
			double k = i->get_radio_detection();
			if (k > r)
				r = k;
		}
		return r;
	}
	double Squad::get_disguise()const {
		double r = 0.0;
		for (std::vector<Plane*>::const_iterator i = plane.begin(); i != plane.end(); i++) {
			double k = (*i)->disguise_increase();
			if (r < k)
				r = k;
		}
		return r;
	}
	int Squad::get_speed() const {
		int speed = INT_MAX;
		for (std::vector<Plane*>::const_iterator i = plane.begin(); i != plane.end(); i++) {
			int k = (*i)->get_speed();
			if (k < speed)
				speed = k;
		}
		return speed;
	}


	double& Squad::get_det_decr(const double& xx, const double& yy)const{
		double r = 1.0;
		for (std::vector<Plane*>::const_iterator i = plane.begin(); i != plane.end(); i++) {
			if ((*i)->get_distance(xx,yy) < systems_workrange)
				r *= (*i)->detection_decrease();
		}
		return r;
	}
	double& Squad::get_pro_decr(const double& xx, const double& yy) const {
		double r = 1.0;
		for (std::vector<Plane*>::const_iterator i = plane.begin(); i != plane.end(); i++) {
			if ((*i)->get_distance(xx, yy) < systems_workrange)
				r *= (*i)->pro_decrease();
		}
		return r;
	}
	double& Squad::get_disg_decr(const double& xx, const double& yy) const{
		double r = 1.0;
		for (std::vector<Plane*>::const_iterator i = plane.begin(); i != plane.end(); i++) {
			if ((*i)->get_distance(xx, yy) < systems_workrange)
				r *= (*i)->disguise_decrease();
		}
		return r;
	}
	Plane*& Squad::get_plane(const int& index) {
		if(index >= plane.size() || index < 0)
			throw std::runtime_error("Invalid index");
		std::vector<Plane*>::iterator i = plane.begin();
		i += index;
		return *i;
	}


	bool Squad::noticed(Plane& pl, Table& players_table, Table& planes_table) const {
		double r = get_det_range();
		for (auto i : plane)
			if (pl.is_spotted((*i), planes_table, players_table, r))
				return true;
		return false;
	}
	

	void Squad::set_N(const unsigned char& a) {
		if (a < 0 || a > 4)
			throw std::runtime_error("Wrong number of planes");
		N = a;
	}
	void Squad::set_command(const int& c) {
		command = c;
	}

	

	double& Squad::go(const double& xx, const double& yy,float& time,const double& multiplier) {
		int speed = get_speed();
		double dist = sqrt((xx - x) * (xx - x) + (yy - y) * (yy - y));
		x += speed*time*(xx - x) / dist * multiplier;
		double new_y = speed*time*(yy - y) / dist * multiplier;
		y += new_y;
		for (std::vector<Plane*>::const_iterator i = plane.begin(); i != plane.end(); i++) {
			(*i)->set_x(x);
			(*i)->set_y((*i)->get_y() + new_y);
		}
		return dist;
	}
	void Squad::attack_squad(Squad& s, Table& my, Table& enemy, const int& t) {
		srand(time(0));
		std::vector<Plane*>::iterator j = s.plane.begin();
		for (auto i : plane) {
			if (!i->Fire(*(j + rand() % s.get_N()), my, enemy,t,get_det_range()))
				for (auto k : s.plane) {
					if (i->Fire(k, my, enemy,t, get_det_range()))
						break;
				}
		}
	}
	void Squad::attack_plane(Plane& p, Table& my, Table& enemy,const int& t) {
		for (auto i : plane) {
			i->Fire(&p, my, enemy,t, get_det_range());
		}
	}


	Plane*& Squad::find_by_xy(const int& x, const int& y){
		for (std::vector<Plane*>::iterator i = plane.begin(); i != plane.end(); i++)
			if ((abs((*i)->get_x() - x) < 0.1) && (abs((*i)->get_y() - y) < 0.1))
				return *i;
		throw std::runtime_error("Miss");
	}
	void Squad::Delete(Plane& pl) {	
		bool flag = false;
		for (std::vector<Plane*>::iterator i = plane.begin(); i != plane.end(); i++) {
			if (&pl == *i) {
				delete* i;
				plane.erase(i);
				N--;
				flag = true;
				break;
			}
		}
		if (!flag)
			throw std::runtime_error("Wrong plane");
		if (N) {
			x = (*plane.begin())->get_x();
			y = (*plane.begin())->get_y();
		}
	}
	void Squad::Add(Plane* P) {
		if (plane.size() >= 4)
			throw std::runtime_error("Overload");
		plane.push_back(P->clone());
		P->set_x(get_plane(0)->get_x());
		P->set_y(get_plane(get_N())->get_y() + 24.0);
		N++;
	}

	std::ostream& operator <<(std::ostream& c, const Squad& a){
		for (int i = 0; i < a.N; i++)
			c << *a.plane[i];
		c << std::endl << std::endl;
		return c;
	}
}