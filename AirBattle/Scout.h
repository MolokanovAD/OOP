#ifndef _SCOUT_H_
#define _SCOUT_H_
#include "Plane.h"
#define G 3
#define L 4
#define ig 0.95
namespace AirBattle {
	class Scout :public Plane {
	protected:
		double ignore_coef;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Scout(const double& xx = 0, const double& yy = 0, const int& max_hp_ = 1000, const int& hp_ = 1000, const double& i_d = ig, const int& speed_ = 1600, const int& guns = G, const int& weapons_total_ = L,const double& radio_detection_ = 650.0);
		Scout(const Scout&);
		Scout(Scout&&);
		virtual ~Scout();

		double get_ignore_coef() const { return ignore_coef; }

		void set_ignore_coef(const double&);

		virtual double accuracy_decrease() const { return 1.0; }
		virtual double detection_decrease() const { return 1.0; }
		virtual double pro_decrease() const { return 1.0; }
		virtual double disguise_decrease() const { return ignore_coef; }
		virtual double disguise_increase() const { return 1.0; }

		virtual Scout* clone() const;
		virtual void getDamage(const int&, const double&, bool, const double&);
		virtual int iam() { return 4; }
	};
}
#endif