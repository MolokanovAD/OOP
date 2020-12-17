#ifndef _GUN_H_
#define _GUN_H_
#include "Weapon.h"

namespace AirBattle {
	/*!
		\brief Пушка.
		Содержит коэффициент точности. Пушка имеет ограниченную дальность стрельбы и неограниченный боезапас.
	*/
	class Gun : public Weapon
	{
	protected:
		/*!
			\brief Коэффициент точности
		*/
		double accuracy;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Gun(int r = 300, double a = 0.9, double f = 1500.0, int d = 150);
		Gun(const Gun&);

		double get_accuracy() const { return accuracy; }

		void set_accuracy(const double&);

		virtual ~Gun() {}
		virtual Gun* clone() const;
		virtual bool iam()const { return true; }
		/*!
			\brief Выстрел из пушки по координатам.
			\param[in] Координаты, расстояние до цели,таблица вражеской эскадры, время
			\return true - цель обнаружена и выстрел произошел, false - выстрел не произошел(из-за того что цель по данным координатам не обнаружена, либо пушка перезаряжается).
		*/
		virtual bool shot(const double&, const double&, const double&, Table&, const int&);
	};
}
#endif