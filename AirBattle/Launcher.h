#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_
#include "Weapon.h"
namespace AirBattle {
	
	class Launcher : public Weapon
	{
	protected:
		int max_ammo;
		int ammo;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Launcher(int r = 1000, double f = 3000.0, int d = 100, int a = 4, int m_a = 4);

		int get_ammo() const { return ammo; }
		int get_max_ammo() { return max_ammo; }

		void set_ammo(const int& a);
		void set_max_ammo(const int& a);

		virtual ~Launcher() {}
		virtual Launcher* clone()const;
		virtual bool iam()const { return false; }
		virtual bool shot(const double&, const double&, const double&, Table&, const int&);//x,y,distance,enemy,time
	};
}
#endif