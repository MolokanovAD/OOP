#ifndef _TABLE_H_
#define _TABLE_H_
#include "Squad.h"
#include <iostream>
#include <map>

namespace AirBattle {
	/*!
		\brief Таблица.
		Содержит звенья эскадры.
	*/
	class Table {
	protected:
		/*!
			\brief Ассоциативный массив, в котором позывной звена - индекс, а указатель на звено - информация
		*/
		std::map<const std::string, Squad*> arr;
	public:
		Table() {}
		Table(const Table&);
		~Table();

		int get_size() const { return arr.size(); }
		/*!
			\brief Коэффициент уменьшения радиуса обнаружения противника в заданной точке, обеспеченный всей эскадрой пользователя.
			\param[in] Координаты
		*/
		double get_det_decr(const double&, const double&) const;
		/*!
			\brief Коэффициент подавления систем ПРО противника в заданной точке, обеспеченный всей эскадрой пользователя.
			\param[in] Координаты
		*/
		double get_pro_decr(const double&, const double&) const;
		/*!
			\brief Коэффициент уменьшения маскировки противника в заданной точке, обеспеченный всей эскадрой пользователя.
			\param [in] Координаты
		*/
		double get_disg_decr(const double&, const double&) const;
		/*!
			\brief Поиск самолета эскадры пользователя по координатам.
			\param[in] Координаты
		*/
		Plane& find_by_coordinates(const double&, const double&) const;
		/*!
			\brief Метод позволяет узнать обнаружен ли самолет противника.
			\param[in] Сылка на таблицу эскадры противника, ссылка на самолет противника
		*/
		bool noticed(Table&, Plane&);

		Table& operator =(const Table&);
		Squad& operator [](const std::string&);
		const Squad& operator [](const std::string&) const;
		/*!
			\brief Добавление звена в таблицу.
			\param[in] Указатель на звено, позывной нового звена
		*/
		void Add(Squad*, const std::string&);
		/*!
			\brief Удаление звена
			\param[in]Позывной звена
		*/
		bool Delete(const std::string&);
		friend class ConstTableIt;
		typedef ConstTableIt ConstIterator;
		ConstIterator begin();
		ConstIterator end();
		ConstTableIt find(const std::string&);
	};
	class ConstTableIt {
	private:
		std::map<const std::string, Squad*>::iterator current;
	public:
		ConstTableIt() {}
		ConstTableIt(std::map<const std::string, Squad*>::iterator it) :current(it) {}
		int operator !=(const ConstTableIt&) const;
		int operator ==(const ConstTableIt&) const;
		std::pair<const std::string, Squad*>& operator *();
		std::pair<const std::string, Squad*>* operator ->();
		ConstTableIt& operator ++();
		ConstTableIt operator ++(int);
		
	};
}
#endif