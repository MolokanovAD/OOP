#ifndef _ANTI_ROCKET_H_
#define _ANTI_ROCKET_H_
#include "Plane.h"
#define G 3
#define L 6
namespace AirBattle {
	class Anti_Rocket : public Plane {
	protected:
		int pro;
		int pro_max;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Anti_Rocket(const double& xx = 0, const double& yy = 0, const int& max_hp_ = 1400, const int& hp_ = 1400, const int& pro_max_ = 5, const int& pro_ = 5, const int& speed_ = 1000, const int& guns = G, const int& weapons_total_ = L, const double& radio_detection_ = 500.0);
		Anti_Rocket(const Anti_Rocket&);
		Anti_Rocket(Anti_Rocket&&);
		virtual ~Anti_Rocket();

		int get_pro()const { return pro; }
		int get_pro_max()const { return pro_max; }

		void set_pro(const int&);
		void set_pro_max(const int&);

		virtual double accuracy_decrease() const { return 1.0; }
		virtual double detection_decrease() const { return 1.0; }
		virtual double pro_decrease() const { return 1.0; }
		virtual double disguise_decrease() const { return 1.0; }
		virtual double disguise_increase() const { return 1.0; }

		virtual Anti_Rocket* clone() const;
		virtual void getDamage(const int&, const double&, bool, const double&);
		virtual int iam() { return 1; }
	};
}
#endif