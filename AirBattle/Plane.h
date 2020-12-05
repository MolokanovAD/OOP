#ifndef _PLANE_H_
#define _PLANE_H_
#include <iostream>
#include <vector>
#include "Weapon.h"
#define systems_workrange 1000

namespace AirBattle {
	class Table;
	class Plane {
	protected:
		int hp;
		int max_hp;
		int speed;
		int weapons_total;
		double x;
		double y;
		int last_shot;
		std::vector<Weapon*> weapon;
		double radio_detection;
		virtual std::ostream& show(std::ostream&) const = 0;
	public:
		Plane(const int& HP,const int& MAXHP,const int& SPEED,const int& w_t,const double& x,const double& y,const double& r_d,const int& guns);
		Plane(const Plane&);
		Plane(Plane&& a);
		virtual ~Plane(){}

		int get_hp()const { return hp; }
		int get_max_hp()const { return max_hp; }
		int get_speed()const { return speed; }
		int get_weapons_total()const { return weapons_total; }
		double get_x()const { return x; }
		double get_y()const { return y; }
		double get_radio_detection()const { return radio_detection; }
		const int get_fire_range() const;
		bool is_reloading(const int& time) const { return ((time - last_shot) < 1000); }
		bool is_spotted(Plane& ,Table& , Table&, const double&) const;//spotter,my,enemy,detection
		double get_distance(const int&, const int&)const;

		std::vector<Weapon*>::const_iterator begin() const{ return weapon.begin(); }
		std::vector<Weapon*>::const_iterator end() const{ return weapon.end(); }

		void set_hp(const int&);
		void set_max_hp(const int&);
		void set_speed(const int&);
		void set_weapons_total(const int&);
		void set_x(const double&);
		void set_y(const double&);
		void set_radio_detection(const double&);
		void set_last_shot(const int& time);

		void Add_weapon(Weapon*);
		void Delete_weapon(const int& index);
		bool Fire(Plane*,Table&,Table&,const int&, const double&);//goal,my,enemy,time, detection

		
		virtual double accuracy_decrease() const = 0;
		virtual double detection_decrease() const = 0;
		virtual double pro_decrease() const = 0;
		virtual double disguise_decrease() const = 0;
		virtual double disguise_increase() const = 0;

		virtual Plane* clone() const = 0;
		virtual void getDamage(const int&, const double&, bool, const double&) = 0;//dmg,accuracy,type,pro decrease
		virtual int iam() = 0;
		friend std::ostream& operator <<(std::ostream&, const Plane&);

	};
}
#endif