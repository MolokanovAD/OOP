#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <SFML/Graphics.hpp>
namespace AirBattle {
	class Button
	{
	protected:
		//sf::Sprite sprite;
		sf::RectangleShape sprite;
		sf::Text text;
		bool is_pressed;
	public:
		Button(const std::string&,const int&,const int&,sf::Font&);
		Button(Button&& B);

		const sf::RectangleShape& get_sprite() const{ return sprite; }
		const sf::Text& get_text() const{ return text; }
		const std::string get_string() const{ return text.getString(); }

		void press();

		bool is_being_pressed(const int&, const int&);

		bool isPressed() const{ return is_pressed; }
		void draw(sf::RenderWindow& window);
	};
}
#endif