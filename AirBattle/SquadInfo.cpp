#include "SquadInfo.h"
namespace AirBattle {
	SquadInfo::SquadInfo(Squad& s,std::string& n) :squad(s),name(n) {
		is_ready = false;
		i_p_a = false;
		i_s_a = false;
		s_goal = nullptr;
		p_goal = nullptr;
		X = s.getx();
		Y = s.gety();
	}
	SquadInfo::SquadInfo(Squad& s, std::string& n, sf::Texture* T, sf::Font& font,const bool& f):SquadInfo(s,n) {
		for (int i = 0; i < s.get_N(); i++) {
			objects.push_back(new Object(T, *s.get_plane(i), font, f));
		}
	}

	Object& SquadInfo::get_object(const int& k) {
		if (k >= objects.size() || k < 0)
			throw std::runtime_error("Wrong index");
		std::vector<Object*>::iterator i = objects.begin();
		return *(*(i + k));
	}

	bool SquadInfo::monster_kill() const {
		if (s_goal->size() == 1 && !(s_goal->objects[0]->get_plane().get_hp()))
			return true;
		return false;
	}

	void SquadInfo::Delete(const int& index) {
		if (index < 0 || index > size())
			throw std::runtime_error("Wrong index");
		std::vector<Object*>::iterator i = objects.begin();
		squad.Delete((*(i + index))->get_plane());
		objects.erase(i + index);
	}

	void SquadInfo::set_command(const int& c) {
		try {
			squad.set_command(c);
		}
		catch (std::runtime_error& k) {
			throw k;
		}
	}
	void SquadInfo::set_X(const int& x) {
		if (x < 0)
			throw std::runtime_error("Wrong X");
		X = x;
	}
	void SquadInfo::set_Y(const int& y) {
		if (y < 0)
			throw std::runtime_error("Wrong X");
		Y = y;
	}
	void SquadInfo::set_is_ready(const bool& b) {
		is_ready = b;
	}
	void SquadInfo::set_squad_attack(const bool& b) {
		i_s_a = b;
	}
	void SquadInfo::set_plane_attack(const bool& b) {
		i_p_a = b;
	}
	void SquadInfo::set_s_goal(SquadInfo* sq) {
		s_goal = sq;
	}
	void SquadInfo::set_p_goal(Object* sq) {
		p_goal = sq;
	}


	void SquadInfo::update(sf::Texture* T) {
		for (auto i : objects) {
			i->update(T);
		}
	}

	void SquadInfo::s_attack(Table& my,Table& enemy, const int& t) const {
		squad.attack_squad(s_goal->squad, my, enemy, t);
	}
	void SquadInfo::p_attack(Table& my, Table& enemy, const int& t) const {
		squad.attack_plane(p_goal->get_plane(), my, enemy, t);
	}
	void SquadInfo::stop_fire() {
		i_s_a = false;
		i_p_a = false;
		s_goal = nullptr;
		p_goal = nullptr;
	}
	bool SquadInfo::is_being_pressed(const int& x,const int& y) {
		double x0 = squad.getx();
		double x1 = x0 + 24;
		double y0 = squad.gety();
		double y1 = y0 + squad.get_N() * 36;
		if (x >= x0 && x <= x1 && y >= y0 && y <= y1)
			return true;
		return false;
	}
	void  SquadInfo::correct(int& x, int& y,const int& l,const int& w) const {
		if (x > (l - 24))
			x = l - 24;
		if (x < 0)
			x = 0;
		int ww = w - squad.get_N() * 36 - 195;
		if (y > ww)
			y = ww;
		if (y < 0)
			y = 0;
	}
	void SquadInfo::move(float& time, const double& mult) {
		if (squad.go(X, Y, time, mult) < 2) {
			set_command(0);
			set_is_ready(false);
		}
	}
}