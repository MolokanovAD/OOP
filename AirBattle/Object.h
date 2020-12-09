#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <SFML/Graphics.hpp>
#include "Plane.h"
namespace AirBattle{
	/*!
		\brief Класс, отвечающий за графическую составляющую самолета.
		Содержит в себе спрайт, отображение текущей прочности самолета, ссылку на самолет, который изображает данный объект, информацию о том, в какую сторону направлен самолет и обнаружен ли он вражеской эскадрой.
	*/
	class Object
	{
	protected:
		/*!
			\brief Текстура(спрайт) самолета
		*/
		sf::Sprite sprite;
		/*!
			\brief Текст(прочность)
		*/
		sf::Text text;
		Plane& plane;
		bool direction;
		bool spotted;
	public:
		Object(sf::Texture*, Plane&,sf::Font&,const bool&);
		Object(const Object& a) :plane(a.plane) {}
		const bool is_spotted() const{ return spotted; }
		const bool is_alive() const { return plane.get_hp(); }
		Plane& get_plane() const{ return plane; }

		void set_spotted(const bool&);

		/*!
			\brief Метод позволяет узнать обнаружен ли самолет вражеской эскадрой.
			\return true - самолет обнаружен, false - не обнаружен.
		*/
		bool is_spotted(Table& my, Table& enemy) const;
		/*!
			\brief Метод позволяет узнать находится ли курсор игрока на текстуре самолета.
			\param[in] Координаты курсора
			\return true - находится, false - не находится.
		*/
		bool is_being_pressed(const int&,const int&)const;
		/*!
			\brief Метод отрисовки самолета на карте.
		*/
		void draw(sf::RenderWindow& window);
		/*!
			\brief Поворот самолета в противоположную сторону.
		*/
		void rotate(sf::Texture* T);
		/*!
			\brief Обновление информации о координатах и прочности самолета.
		*/
		void update(sf::Texture*);
	};
}
#endif