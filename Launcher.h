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
		Launcher(int r = 1000, double f = 5.0, int d = 100, int a = 4, int m_a = 4);

		int get_ammo() const { return ammo; }
		int get_max_ammo() { return max_ammo; }

		void set_ammo(int& a);
		void set_max_ammo(int& a);

		virtual Launcher* clone()const;
		virtual int iam()const { return 2; }
		virtual void shot(Plane&);
	};
}
#endif