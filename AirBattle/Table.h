#ifndef _TABLE_H_
#define _TABLE_H_
#include "Squad.h"
#include <iostream>
#include <map>

namespace AirBattle {
	class Table {
		friend class Iterator;
	protected:
		std::map<const std::string, Squad*> arr;
	public:
		Table() {}
		Table(const Table&);
		~Table();

		int get_size() const { return arr.size(); }
		double get_det_decr(const double&, const double&) const;//без маскировки
		double get_pro_decr(const double&, const double&) const;
		double get_disg_decr(const double&, const double&) const;

		Plane& find_by_coordinates(const double&, const double&) const;

		bool noticed(Table&, Plane&);

		Table& operator =(const Table&);
		Squad& operator [](const std::string&);
		const Squad& operator [](const std::string&) const;
		void Add(Squad*, const std::string&);
		bool Delete(const std::string&);
		friend std::ostream& operator <<(std::ostream&, const Table&);
		friend class ConstTableIt;
		typedef ConstTableIt ConstIterator;
		ConstIterator begin();
		ConstIterator end();
		ConstTableIt find(const std::string&);
	};
	class ConstTableIt {
	private:
		std::map<const std::string, Squad*>::iterator current;
	public:
		ConstTableIt() {}
		ConstTableIt(std::map<const std::string, Squad*>::iterator it) :current(it) {}
		int operator !=(const ConstTableIt&) const;
		int operator ==(const ConstTableIt&) const;
		std::pair<const std::string, Squad*>& operator *();
		std::pair<const std::string, Squad*>* operator ->();
		ConstTableIt& operator ++();
		ConstTableIt operator ++(int);
		
	};
}
#endif