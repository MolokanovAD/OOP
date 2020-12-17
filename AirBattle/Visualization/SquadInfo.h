#ifndef _SQUADINFO_
#define _SQUADINFO_
#include "..\ProjectOOP4lib\Squad.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
namespace AirBattle {
	/*!
		\brief Информация о звене.
		Класс содержит информацию о целях, по которым ведется огонь, координатах к которым движется звено, позывной звена, ссылку на соответствующее данному объекту звено и вектор графических объектов, изображающих самолеты данного звена.
	*/
	class SquadInfo
	{
	protected:
		/*!
			\brief Готово ли звено перемещаться
		*/
		bool is_ready;
		/*!
			\brief Готово ли звено открыть огонь по звену
		*/
		bool i_s_a;
		/*!
			\brief Готово ли звено открыть огонь по самолету
		*/
		bool i_p_a;
		/*!
			\brief Координата Х точки назначения
		*/
		int X;
		/*!
			\brief Координата Y точки назначения
		*/
		int Y;
		/*!
			\brief Цель(звено)
		*/
		SquadInfo* s_goal;
		/*!
			\brief Цель(самолет)
		*/
		Object* p_goal;
		/*!
			\brief Позывной звена
		*/
		std::string name;
		Squad& squad;
		/*!
			\brief Графические объекты самолетов звена
		*/
		other_vector<Object*> objects;
	public:
		SquadInfo(Squad& s,std::string& n);
		SquadInfo(Squad& s, std::string& n, sf::Texture* T,sf::Font& font,const bool& f);
		const int& get_X() const { return X; }
		const int& get_Y() const { return Y; }
		const int& get_coord_x() const { return squad.getx(); }
		const int& get_coord_y() const { return squad.gety(); }
		Squad& get_squad() { return squad; }
		SquadInfo* get_s_goal() const{ return s_goal; }
		Object* get_p_goal()const { return p_goal; }
		
		int get_command()const { return squad.get_command(); }
		bool is_ready_to_move() const { return is_ready; }
		bool is_attacking_squad() const { return i_s_a; }
		bool is_attacking_plane() const { return i_p_a; }
		const std::string& get_name() { return name; }
		Object& get_object(const int&);
		int size()const { return objects.size(); }
		bool frag() { return !p_goal->is_alive(); }
		bool monster_kill()const;

		/*!
			\brief удаление объекта по индексу.
		*/
		void Delete(const int& index);

		
		void set_command(const int&);
		void set_X(const int&);
		void set_Y(const int&);
		void set_is_ready(const bool&);
		void set_squad_attack(const bool&);
		void set_plane_attack(const bool&);
		void set_s_goal(SquadInfo* sq);
		void set_p_goal(Object* sq);

		/*!
			\brief Обновление информации о координатах и прочности самолетов звена.
		*/
		void update(sf::Texture*);
		/*!
			\brief Атака вражеского звена.
			\param[in] Таблица эскадры пользователя, таблица вражеской эскадры, время
			Используется соответствующий метод(attack_plane) класса AirBattle::Squad.
		*/
		void s_attack(Table&,Table&,const int&)const;
		/*!
			\brief Атака вражеского самолета.
			\param[in] Таблица эскадры пользователя, таблица вражеской эскадры, время
			Используется соответствующий метод класса(attack_squad) AirBattle::Squad.
		*/
		void p_attack(Table&, Table&, const int&)const;
		/*!
			\brief Остановка огня, приказ - сохранять позицию.
		*/
		void stop_fire();
		/*!
			\brief Метод позволяет узнать находится ли курсор игрока в пределах данного звена.
			\param[in] Координаты курсора
			\return true - находится, false - не находится.
		*/
		bool is_being_pressed(const int&, const int&);
		/*!
			\brief Метод позволяет исправить координаты точки назначения чтобы самолеты звена не улетело за пределы карты.
			\param[in] Координаты курсора, длина и высота окна с игрой
		*/
		void correct(int&, int&, const int&, const int&) const;
		/*!
			\brief Движение звена.
			\param[in] Время, множитель скорости
			Вызывается соответствующий метод(go) класса Squad
		*/
		void move(float&, const double&);
	};
}
#endif