#ifndef _MISSION_H_
#define _MISSION_H_
#include <iostream>
#include "Table.h"

namespace AirBattle {
	class Mission
	{
	protected:
		Table a;
		Table b;
	public:
		Mission();
		Mission(const int&, const int&, std::string*, std::string*, const int&, const int&);

		~Mission(){}

		Table& get_table(const bool&);
		Squad& find_squad(const std::string&, bool);
		Plane& find_plane(const std::string&,const int&,bool);//позывной, индекс, свой-чужой

		void save(const std::string&);
		void load(const std::string&);
	};
}
#endif