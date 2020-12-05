#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <SFML/Graphics.hpp>
#include "Plane.h"
namespace AirBattle{
	class Object
	{
	protected:
		sf::Sprite sprite;
		sf::Text text;
		Plane& plane;
		bool direction;
		bool spotted;
	public:
		Object(sf::Texture*, Plane&,sf::Font&,const bool&);
		Object(const Object&);
		const bool is_spotted() const{ return spotted; }
		const bool is_alive() const { return plane.get_hp(); }
		Plane& get_plane() const{ return plane; }

		void set_spotted(const bool&);

		bool is_spotted(Table& my, Table& enemy) const;
		bool is_being_pressed(const int&,const int&)const;
		void draw(sf::RenderWindow& window);
		void rotate(sf::Texture* T);
		void update(sf::Texture*);
	};
}
#endif