#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <SFML/Graphics.hpp>
namespace AirBattle {
	/*!
		\brief ������.
		����� �������� �������� ������, ����� � ���������� � ���, ������ �� ���.
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
			\brief ������� ������.
			����� ������� ����� �� ������ ���������� ������ ��� �������, � ����������� �� ��������� ����� ��������.
		*/
		void press();
		/*!
			\brief ����� ��������� ������ ��������� �� ������ ������ � �������� ������.
			\param[in] ���������� �������
			\return true - ���������, false - �� ���������.
		*/
		bool is_being_pressed(const int&, const int&);
		/*!
			\brief ����� ��������� ������ ������ �� ������.
			\return true - ������, false - �� ������.
		*/
		bool isPressed() const{ return is_pressed; }
		/*!
			\brief ����� ��������� ������.
		*/
		void draw(sf::RenderWindow& window);
	};
}
#endif