#ifndef _MISSION_H_
#define _MISSION_H_
#include <iostream>
#include "Table.h"

namespace AirBattle {
	/*!
		\brief Миссия
		Содержит информацию о текущей игровой сессии.
	*/
	class Mission
	{
	protected:
		/*!
			\brief Таблица эскадры пользователя
		*/
		Table a;
		/*!
			\brief Таблица вражеской эскадры
		*/
		Table b;
	public:
		Mission();
		Mission(const int&, const int&, std::string*, std::string*, const int&, const int&);

		~Mission() {}

		Table& get_table(const bool&);
		/*!
			\brief Поиск звена по позывному.
		*/
		Squad& find_squad(const std::string&, bool);
		/*!
			\brief Поиск самолета по индексу.
			\param[in] Позывной, индекс, своя или вражеская эскадра
		*/
		Plane& find_plane(const std::string&, const int&, bool);

		/*!
			\brief Загрузка игровой сессии из файла.
		*/
		void save(const std::string&);
		/*!
			\brief Сохранение информации об игровой сессии в файл.
		*/
		void load(const std::string&);
	};
}
#endif