#ifndef _PLANE_H_
#define _PLANE_H_
#include <iostream>
#include "other_vector.h"
#include "Weapon.h"
#define systems_workrange 1000

namespace AirBattle {
	class Table;
	/*!
		\brief Самолет.
		Содержит в себе различные поля и методы, присущие всем самолетам.
	*/
	class Plane {
	protected:
		int hp;
		int max_hp;
		int speed;
		/*!
			\brief Максимальное уоличество оружия
		*/
		int weapons_total;
		double x;
		double y;
		/*!
			\brief Время последнего выстрела
		*/
		int last_shot;
		other_vector<Weapon*> weapon;
		/*!
			\brief Радиус обнаружения
		*/
		double radio_detection;
		virtual std::ostream& show(std::ostream&) const = 0;
	public:
		Plane(const int& HP, const int& MAXHP, const int& SPEED, const int& w_t, const double& x, const double& y, const double& r_d, const int& guns);
		Plane(const Plane&);
		Plane(Plane&& a);
		virtual ~Plane() {}

		int get_hp()const { return hp; }
		int get_max_hp()const { return max_hp; }
		int get_speed()const { return speed; }
		int get_weapons_total()const { return weapons_total; }
		double get_x()const { return x; }
		double get_y()const { return y; }
		double get_radio_detection()const { return radio_detection; }
		const int get_fire_range() const;
		/*!
			\brief Функция позволяющая узнать, перезаряжается ли самолёт.
			\param[in] Время
			\return true - перезаряжается, false - готов к стрельбе.
		*/
		bool is_reloading(const int& time) const { return ((time - last_shot) < 1000); }
		/*!
			\brief Функция позволяющая узнать, обнаружен ли самолет вражеским самолётом.
			\param[in] Самолет противника, таблица эскадры пользователя, таблица эскадры противника, радиус обнаружения противника
			\return true - самолет в области видимости врага, false - самолет не обнаружен противником.
		*/
		bool is_spotted(Plane&, Table&, Table&, const double&) const;//spotter,my,enemy,detection
		double get_distance(const int&, const int&)const;

		other_vector<Weapon*>::iterator begin() const { return weapon.begin(); }
		other_vector<Weapon*>::iterator end() const { return weapon.end(); }

		void set_hp(const int&);
		void set_max_hp(const int&);
		void set_speed(const int&);
		void set_weapons_total(const int&);
		void set_x(const double&);
		void set_y(const double&);
		void set_radio_detection(const double&);
		void set_last_shot(const int& time);
		/*!
			\brief Добавление оружия.
		*/
		void Add_weapon(Weapon*);
		/*!
			\brief Удаление оружия по индексу.
		*/
		void Delete_weapon(const int& index);
		/*!
			\brief Выстрел по вражескому самолету.
			\param[in] Цель(самолет), таблица эскадры пользователя, таблица эскадры противника, радиус обнаружения атакующего самолёта(зависит от других самолетов в звене)
			\return true - Выстрел был совершён(без гарантии попадания и нанесения урона), false - Выстрел не произошел(оружие перезаряжается, самолет не готов к выстрелу или цель не была обнаружена).
		*/
		bool Fire(Plane*, Table&, Table&, const int&, const double&);//goal,my,enemy,time, detection

		/*!
			\brief Возвращает показатель, отвечающий за уменьшение точности вражеских пушек
		*/
		virtual double accuracy_decrease() const = 0;
		/*!
			\brief Возвращает показатель, отвечающий за уменьшение радиуса обнаружения вражеских самолетов
		*/
		virtual double detection_decrease() const = 0;
		/*!
			\brief Возвращает показатель, отвечающий за подавление вражеских систем ПРО
		*/
		virtual double pro_decrease() const = 0;
		/*!
			\brief Возвращает показатель, отвечающий за уменьшение действия маскировки вражеских самолетов
		*/
		virtual double disguise_decrease() const = 0;
		/*!
			\brief Возвращает показатель, отвечающий за маскировку самолета
		*/
		virtual double disguise_increase() const = 0;

		virtual Plane* clone() const = 0;
		/*!
			\brief Функция получения урона.
			\param[in] Урон, точность, тип оружия, коэффициент подавления систем ПРО.
			Различается в зависимости от типа самолёта, по которому ведётся огонь.
		*/
		virtual void getDamage(const int&, const double&, bool, const double&) = 0;
		virtual int iam() = 0;
		friend std::ostream& operator <<(std::ostream&, const Plane&);

	};
}
#endif
