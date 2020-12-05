#ifndef _SQUAD_H_
#define _SQUAD_H_
#include "Plane.h"
#include <iostream>
namespace AirBattle {
	class Squad{
	protected:
		int command;
		unsigned char N;
		double x;
		double y;
		std::vector<Plane*> plane;
	public:
		Squad(const int& x0 = 0, const int& y0 = 0, const int& command = 0 , const int& anti_rocket = 0, const int& radio = 0, const int& disguise = 0, const int& scout = 0);
		Squad(const Squad&);
		Squad(Squad&&);
		~Squad();

		int get_command() const { return command; }
		double getx()const { return x; }
		double gety()const { return y; }
		unsigned char get_N()const { return N; }
		double get_det_range()const;
		double get_disguise()const;
		int get_speed() const;
		double& get_det_decr(const double&, const double&) const;
		double& get_pro_decr(const double&, const double&) const;
		double& get_disg_decr(const double&, const double&) const;
		Plane*& get_plane(const int&);
		bool noticed(Plane&, Table&, Table&)const;

		void set_N(const unsigned char&);
		void set_command(const int&);
		std::vector<Plane*>::const_iterator begin() const { return plane.begin(); }
		std::vector<Plane*>::const_iterator end() const { return plane.end(); }

		double& go(const double& x, const double& y, float& time, const double& m = 1.0);//x,y,time,multiplier
		void attack_squad(Squad&, Table&, Table&, const int&);
		void attack_plane(Plane&, Table&, Table&, const int&);

		Plane*& find_by_xy(const int&, const int&);
		void Delete(Plane&);
		void Add(Plane*);
		

		friend std::ostream& operator <<(std::ostream&, const Squad&);
	};
}
#endif