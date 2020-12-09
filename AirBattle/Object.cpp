#include "Object.h"
#include "Anti_Rocket.h"
#include "Disguise.h"
#include "Scout.h"
#include "Radio.h"
#include "Table.h"
namespace AirBattle {
	Object::Object(sf::Texture* T, Plane& pl,sf::Font& font,const bool& b): plane(pl){
		Anti_Rocket* a = dynamic_cast<Anti_Rocket*>(&pl);
		if (a) {
			if (pl.get_x() < 10)
				sprite.setTexture(T[0]);
			else
				sprite.setTexture(T[1]);
		}
		else {
			Radio* b = dynamic_cast<Radio*>(&pl);
			if (b) {
				if (pl.get_x() < 10)
					sprite.setTexture(T[4]);
				else
					sprite.setTexture(T[5]);
			}
			else {
				Disguise* c = dynamic_cast<Disguise*>(&pl);
				if (c) {
					if (pl.get_x() < 10)
						sprite.setTexture(T[2]);
					else
						sprite.setTexture(T[3]);
				}
				else {
					Scout* d = dynamic_cast<Scout*>(&pl);
					if (pl.get_x() < 10)
						sprite.setTexture(T[6]);
					else
						sprite.setTexture(T[7]);
				}
			}
		}
		sprite.setPosition(pl.get_x(), pl.get_y());
		text.setString(std::to_string(pl.get_hp()));
		text.setFont(font);
		text.setPosition(pl.get_x(), pl.get_y() - 12.0);
		text.setCharacterSize(10);
		if(b)
			text.setFillColor(sf::Color::Green);
		else
			text.setFillColor(sf::Color::Red);
		spotted = false;
	}

	void Object::set_spotted(const bool& b) {
		spotted = b;
	}



	bool Object::is_spotted(Table& planes_table, Table& players_table) const {
		return players_table.noticed(planes_table,plane);
	}

	bool Object::is_being_pressed(const int& xx, const int& yy) const {
		double x0 = plane.get_x();
		double y0 = plane.get_y();
		double x1 = x0 + 24;
		double y1 = y0 + 24;
		if (xx >= x0 && xx <= x1 && yy >= y0 && yy <= y1)
			return true;
		return false;
	}
	void Object::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}
	void Object::rotate(sf::Texture* T) {
		Anti_Rocket* a = dynamic_cast<Anti_Rocket*>(&plane);
		if (a) {
			if (!direction)
				sprite.setTexture(T[0]);
			else
				sprite.setTexture(T[1]);
		}
		else {
			Radio* b = dynamic_cast<Radio*>(&plane);
			if (b) {
				if (!direction)
					sprite.setTexture(T[4]);
				else
					sprite.setTexture(T[5]);
			}
			else {
				Disguise* c = dynamic_cast<Disguise*>(&plane);
				if (c) {
					if (!direction)
						sprite.setTexture(T[2]);
					else
						sprite.setTexture(T[3]);
				}
				else {
					Scout* d = dynamic_cast<Scout*>(&plane);
					if (!direction)
						sprite.setTexture(T[6]);
					else
						sprite.setTexture(T[7]);
				}
			}
		}
		direction = !direction;
	}
	void Object::update(sf::Texture* T) {
		float xx = plane.get_x();
		float yy = plane.get_y();
		double old_x = sprite.getPosition().x;
		if ((old_x < xx && !direction) || (old_x > xx && direction))
			rotate(T);
		sprite.setPosition(xx,yy);
		text.setPosition(xx, yy - 12.0);
		text.setString(std::to_string(plane.get_hp()));
	}
}