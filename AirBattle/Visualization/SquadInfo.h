#ifndef _SQUADINFO_
#define _SQUADINFO_
#include "..\ProjectOOP4lib\Squad.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
namespace AirBattle {
	/*!
		\brief ���������� � �����.
		����� �������� ���������� � �����, �� ������� ������� �����, ����������� � ������� �������� �����, �������� �����, ������ �� ��������������� ������� ������� ����� � ������ ����������� ��������, ������������ �������� ������� �����.
	*/
	class SquadInfo
	{
	protected:
		/*!
			\brief ������ �� ����� ������������
		*/
		bool is_ready;
		/*!
			\brief ������ �� ����� ������� ����� �� �����
		*/
		bool i_s_a;
		/*!
			\brief ������ �� ����� ������� ����� �� ��������
		*/
		bool i_p_a;
		/*!
			\brief ���������� � ����� ����������
		*/
		int X;
		/*!
			\brief ���������� Y ����� ����������
		*/
		int Y;
		/*!
			\brief ����(�����)
		*/
		SquadInfo* s_goal;
		/*!
			\brief ����(�������)
		*/
		Object* p_goal;
		/*!
			\brief �������� �����
		*/
		std::string name;
		Squad& squad;
		/*!
			\brief ����������� ������� ��������� �����
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
			\brief �������� ������� �� �������.
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
			\brief ���������� ���������� � ����������� � ��������� ��������� �����.
		*/
		void update(sf::Texture*);
		/*!
			\brief ����� ���������� �����.
			\param[in] ������� ������� ������������, ������� ��������� �������, �����
			������������ ��������������� �����(attack_plane) ������ AirBattle::Squad.
		*/
		void s_attack(Table&,Table&,const int&)const;
		/*!
			\brief ����� ���������� ��������.
			\param[in] ������� ������� ������������, ������� ��������� �������, �����
			������������ ��������������� ����� ������(attack_squad) AirBattle::Squad.
		*/
		void p_attack(Table&, Table&, const int&)const;
		/*!
			\brief ��������� ����, ������ - ��������� �������.
		*/
		void stop_fire();
		/*!
			\brief ����� ��������� ������ ��������� �� ������ ������ � �������� ������� �����.
			\param[in] ���������� �������
			\return true - ���������, false - �� ���������.
		*/
		bool is_being_pressed(const int&, const int&);
		/*!
			\brief ����� ��������� ��������� ���������� ����� ���������� ����� �������� ����� �� ������� �� ������� �����.
			\param[in] ���������� �������, ����� � ������ ���� � �����
		*/
		void correct(int&, int&, const int&, const int&) const;
		/*!
			\brief �������� �����.
			\param[in] �����, ��������� ��������
			���������� ��������������� �����(go) ������ Squad
		*/
		void move(float&, const double&);
	};
}
#endif