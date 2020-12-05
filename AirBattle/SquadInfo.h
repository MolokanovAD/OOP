#ifndef _SQUADINFO_
#define _SQUADINFO_
#include "Squad.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
namespace AirBattle {
	class SquadInfo
	{
	protected:
		bool is_ready;
		bool i_s_a;
		bool i_p_a;
		int X;
		int Y;
		SquadInfo* s_goal;
		Object* p_goal;
		std::string name;
		Squad& squad;
		std::vector<Object*> objects;
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
		
		const int& get_command()const { return squad.get_command(); }
		bool is_ready_to_move() const { return is_ready; }
		bool is_attacking_squad() const { return i_s_a; }
		bool is_attacking_plane() const { return i_p_a; }
		const std::string& get_name() { return name; }
		Object& get_object(const int&);
		const int& size()const { return objects.size(); }
		bool frag() { return !p_goal->is_alive(); }
		bool monster_kill()const;


		void Delete(const int& index);

		
		void set_command(const int&);
		void set_X(const int&);
		void set_Y(const int&);
		void set_is_ready(const bool&);
		void set_squad_attack(const bool&);
		void set_plane_attack(const bool&);
		void set_s_goal(SquadInfo* sq);
		void set_p_goal(Object* sq);

		void update(sf::Texture*);
		void s_attack(Table&,Table&,const int&)const;//a,b,time
		void p_attack(Table&, Table&, const int&)const;
		void stop_fire();
		bool is_being_pressed(const int&, const int&);
		void correct(int&, int&, const int&, const int&) const;//x,y,l,w
		void move(float&, const double&);
	};
}
#endif