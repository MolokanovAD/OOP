#ifndef _SQUAD_H_
#define _SQUAD_H_
#include "Plane.h"
#include <iostream>
#include "other_vector.h"
namespace AirBattle {
	/*!
		\brief Звено.
		Содержит приказ звена, количество самолетов в звене(не больше 4), координаты и вектор самолетов.
	*/
	class Squad{
	protected:
		/*!
			\brief Приказ звена
		*/
		int command;
		/*!
			\brief Текущее количество самолетов
		*/
		unsigned char N;
		double x;
		double y;
		other_vector<Plane*> plane;
	public:
		Squad(const int& x0 = 0, const int& y0 = 0, const int& command = 0 , const int& anti_rocket = 0, const int& radio = 0, const int& disguise = 0, const int& scout = 0);
		Squad(const Squad&);
		Squad(Squad&&);
		~Squad();

		int get_command() const { return command; }
		double getx()const { return x; }
		double gety()const { return y; }
		unsigned char get_N()const { return N; }
		/*!
			\brief Возвращает радиус обнаружения звена.
			Радиус обнаружения звена равен наибольшему из радиусов обнаружения самолетов этого звена.
		*/
		double get_det_range()const;
		/*!
			\brief Возвращает маскировку звена.
			Маскировка звена равна наименьшей из маскировок самолетов этого звена.
		*/
		double get_disguise()const;
		/*!
			\brief Возвращает скорость звена.
			Скорость звена равна наименьшей из скоростей самолетов этого звена.
		*/
		int get_speed() const;
		/*!
			\brief Возвращает коэффициент уменьшения радиуса обнаружения врага, обеспеченный самолетами звена.
			Коэффициент равен произведению коэффициентов всех самолетов звена.
		*/
		double get_det_decr(const double&, const double&) const;
		/*!
			\brief Возвращает коэффициент подавления систем ПРО врага, обеспеченный самолетами звена.
			Коэффициент равен произведению коэффициентов всех самолетов звена.
		*/
		double get_pro_decr(const double&, const double&) const;
		/*!
			\brief Возвращает коэффициент уменьшения маскировки врага, обеспеченный самолетами звена.
			Коэффициент равен произведению коэффициентов всех самолетов звена.
		*/
		double get_disg_decr(const double&, const double&) const;
		/*!
			\brief Получения самолета по индексу.
		*/
		Plane*& get_plane(const int&);
		/*!
			\brief Метод позволяет узнать видит ли звено вражеский самолет.
			\param[in] Ссылка на вражеский самолет, таблица эскадры пользователя, таблица эскадры противника
			\return true - звено видит самолет, false - не видит.
		*/
		bool noticed(Plane&, Table&, Table&)const;

		void set_N(const unsigned char&);
		void set_command(const int&);
		other_vector<Plane*>::iterator begin() const { return plane.begin(); }
		other_vector<Plane*>::iterator end() const { return plane.end(); }

		/*!
			\brief Метод движения звена.
			\param[in] Координаты, время, множитель скорости
			\return Расстояние до конца маршрута.
			Вычисляется расстояние до конца маршрута, скорость звена и координаты меняются на новые.
			\code
				x += speed*time*(goal_x - current_x) / distance * multiplier;
				double new_y = speed*time*(goal_y - current_y) / distance * multiplier;
				y += new_y;
			\endcode
		*/
		double go(const double& x, const double& y, float& time, const double& m = 1.0);
		/*!
			\brief Атака вражеского звена.
			\param[in] Ссылка на вражеское звено, таблица эскадры пользователя, таблица эскадры противника, время
			Сначала случайно выбирается индекс вражеского самолета и происходит попытка выстрела.
			Если выстрел не был совершен происходит попытка выстрела по каждому самолету до первого совершенного выстрела. 
			Так по очереди каждый самолет звена совершает свою атаку.
		*/
		void attack_squad(Squad&, Table&, Table&, const int&);
		/*!
			\brief Атака вражеского самолета.
			\param[in] Ссылка на вражеский самолет, таблица эскадры пользователя, таблица эскадры противника, время
			Каждый самолет звена по очереди атакует цель.
		*/
		void attack_plane(Plane&, Table&, Table&, const int&);

		/*!
			\brief Поиск самолета звена по координатам.
			\param[in] Координаты
		*/
		Plane*& find_by_xy(const int&, const int&);
		/*!
			\brief Удаление самолета из звена
			\param[in] Ссылка на самолет
		*/
		void Delete(Plane&);
		/*!
			\brief Добавление копии самолета в звено
			\param[in] Указатель на самолет
		*/
		void Add(Plane*);
		
	};
}
#endif