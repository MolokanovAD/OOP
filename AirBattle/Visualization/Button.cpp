#include "Button.h"
namespace AirBattle {
	Button::Button(const std::string& S,const int& x,const int& y,sf::Font& font) {
		sprite.setSize(sf::Vector2f(120, 40));
		sprite.setOutlineThickness(1);
		sprite.setOutlineColor(sf::Color::Black);
		sprite.setPosition(x, y);
		text.setString(S);
		text.setFont(font);
		text.setPosition(x+10, y + 5);
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::Black);
		is_pressed = false;
	}
	Button::Button(Button&& B) {
		sprite = std::move(B.sprite);
		text = std::move(B.text);
		is_pressed = B.is_pressed;
	}
	void Button::press() {
		if (is_pressed)
			text.setStyle(sf::Text::Regular);
		else
			text.setStyle(sf::Text::Bold);
		is_pressed = !is_pressed;
	}
	bool Button::is_being_pressed(const int& x, const int& y) {
		return sprite.getGlobalBounds().contains(x, y);
	}

	void Button::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}
}