#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <SFML/Graphics.hpp>
#include "Plane.h"
namespace AirBattle{
	/*!
		\brief �����, ���������� �� ����������� ������������ ��������.
		�������� � ���� ������, ����������� ������� ��������� ��������, ������ �� �������, ������� ���������� ������ ������, ���������� � ���, � ����� ������� ��������� ������� � ��������� �� �� ��������� ��������.
	*/
	class Object
	{
	protected:
		/*!
			\brief ��������(������) ��������
		*/
		sf::Sprite sprite;
		/*!
			\brief �����(���������)
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
			\brief ����� ��������� ������ ��������� �� ������� ��������� ��������.
			\return true - ������� ���������, false - �� ���������.
		*/
		bool is_spotted(Table& my, Table& enemy) const;
		/*!
			\brief ����� ��������� ������ ��������� �� ������ ������ �� �������� ��������.
			\param[in] ���������� �������
			\return true - ���������, false - �� ���������.
		*/
		bool is_being_pressed(const int&,const int&)const;
		/*!
			\brief ����� ��������� �������� �� �����.
		*/
		void draw(sf::RenderWindow& window);
		/*!
			\brief ������� �������� � ��������������� �������.
		*/
		void rotate(sf::Texture* T);
		/*!
			\brief ���������� ���������� � ����������� � ��������� ��������.
		*/
		void update(sf::Texture*);
	};
}
#endif