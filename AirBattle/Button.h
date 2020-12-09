#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <SFML/Graphics.hpp>
namespace AirBattle {
	/*!
		\brief Кнопка.
		Класс содержит текстуру кнопки, текст и информацию о там, нажата ли она.
	*/
	class Button
	{
	protected:
		sf::RectangleShape sprite;
		sf::Text text;
		bool is_pressed;
	public:
		Button(const std::string&,const int&,const int&,sf::Font&);
		Button(Button&& B);

		const sf::RectangleShape& get_sprite() const{ return sprite; }
		const sf::Text& get_text() const{ return text; }
		const std::string get_string() const{ return text.getString(); }

		/*
			\brief Нажатие кнопки.
			После нажатия текст на кнопке становится жирным или обычным, в зависимости от состояния перед нажатием.
		*/
		void press();
		/*!
			\brief Метод позволяет узнать находится ли курсор игрока в пределах кнопки.
			\param[in] Координаты курсора
			\return true - находится, false - не находится.
		*/
		bool is_being_pressed(const int&, const int&);
		/*!
			\brief Метод позволяет узнать нажата ли кнопка.
			\return true - нажата, false - не нажата.
		*/
		bool isPressed() const{ return is_pressed; }
		/*!
			\brief Метод отрисовки кнопки.
		*/
		void draw(sf::RenderWindow& window);
	};
}
#endif