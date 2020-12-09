#ifndef _DISGUISE_H_
#define _DISGUISE_H_
#include "Plane.h"
#define G 3
#define L 6
#define dc 1.4
#define ac 0.85
namespace AirBattle {
	/*!
		\brief Самолет маскировки.
		Содержит коэффициенты уменьшения точности вражеских пушек и маскировки данного самолета. Обладает повышенной маскировкой.
	*/
	class Disguise :public Plane {
	protected:
		/*!
			\brief Коэффициент маскировки
		*/
		double disg_coef;
		/*!
			\brief Коэффициент уменьшения точности вражеских пушек
		*/
		double acc_coef;
		virtual std::ostream& show(std::ostream&) const;
	public:
		Disguise(const double& xx = 0, const double& yy = 0, const int& max_hp_ = 1400, const int& hp_ = 1400, const double& a_c = ac,const double& d_c = dc, const int& speed_ = 1000, const int& guns = G, const int& weapons_total_ = L,const double& radio_detection_ = 500.0);
		Disguise(const Disguise&);
		Disguise(Disguise&&);
		virtual ~Disguise();

		double get_det_coef()const { return disg_coef; }
		double get_acc_coef() const { return acc_coef; }

		void set_det_coef(const int&);
		void set_acc_coef(const int&);

		virtual double accuracy_decrease() const { return acc_coef; }
		virtual double detection_decrease() const { return 1.0; }
		virtual double pro_decrease() const { return 1.0; }
		virtual double disguise_decrease() const { return 1.0; }
		virtual double disguise_increase() const { return disg_coef; }

		virtual Disguise* clone() const;
		virtual void getDamage(const int&, const double&, bool, const double&);
		virtual int iam() { return 2; }
	};
}
#endif