#ifndef _RADIO_H_
#define _RADIO_H_
#include "Plane.h"
#define G 3
#define L 6
#define pro_d 0.92
#define disguise_d 0.97
#define detection_d 0.97
namespace AirBattle {
	/*!
		\brief Самолет радиоэлектронной борьбы.
		Содержит коэффициенты подавления вражеских систем ПРО, максировки и радиообнаружения. Такой самолет поможет обнаружить врага с хорошей маскировкой, уменьшая при этом вероятность обнаружения союзныъ самолетов. Также увеличивает вероятность нанесения урона ракетой по самолетам с системами ПРО.
	*/
	class Radio :public Plane {
	protected:
		/*!
			\brief Коэффициент подавления вражеских систем ПРО
		*/
		double pro_decr;
		/*!
			\brief Коэффициент подавления вражеских систем маскировки
		*/
		double disguise_decr;
		/*!
			\brief Коэффициент подавления вражеских систем радиообнаружения
		*/
		double det_decr;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Radio(const double& xx = 0, const double& yy = 0, const int& max_hp_ = 1400, const int& hp_ = 1400, const double& p_d = pro_d, const double& disg_d = disguise_d, const double& det_d = detection_d, const int& speed_ = 1000, const int& guns = G, const int& weapons_total_ = L, const double& radio_detection_ = 500.0);
		Radio(const Radio&);
		Radio(Radio&&);
		virtual ~Radio();

		double get_pro_decr() const { return pro_decr; }
		double get_disguise_decr() const { return disguise_decr; }
		double get_det_decr() const { return det_decr; }

		void set_pro_decr(const double&);
		void set_disguise_decr(const double&);
		void set_det_decr(const double&);

		virtual double accuracy_decrease() const { return 1.0; }
		virtual double detection_decrease() const { return det_decr; }
		virtual double pro_decrease() const { return pro_decr; }
		virtual double disguise_decrease() const { return disguise_decr; }
		virtual double disguise_increase() const { return 1.0; }

		virtual Radio* clone() const;
		virtual void getDamage(const int&, const double&, bool, const double&);
		virtual int iam() { return 3; }
	};
}
#endif