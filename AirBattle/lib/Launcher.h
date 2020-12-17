#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_
#include "Weapon.h"
namespace AirBattle {
	/*!
		\brief Ракетница.
		Содержит текущее количество ракет и максимальное  количество ракет. Ракетница имеет неограниченную дальность стрельбы и ограниченный боезапас.
	*/
	class Launcher : public Weapon
	{
	protected:
		/*!
			\brief Максимальное количество ракет
		*/
		int max_ammo;
		/*!
			\brief Текущее количество ракет
		*/
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
		/*!
			\brief Выстрел из ракетницы по координатам.
			\param[in] Координаты, расстояние до цели,таблица вражеской эскадры, время
			\return true - цель обнаружена и выстрел произошел, false - выстрел не произошел(из-за того что цель по данным координатам не обнаружена, ракетница перезаряжается или ракеты закончились).
		*/
		virtual bool shot(const double&, const double&, const double&, Table&, const int&);
	};
}
#endif