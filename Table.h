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
		~Table() {};
		Table& operator =(const Table&);
		Squad*& operator [](const std::string&);
		Squad* operator [](const std::string&) const;
		bool Delete(const std::string&);
		friend std::ostream& operator <<(std::ostream&, const Table&);
		friend class ConstTableIt;
		typedef ConstTableIt ConstIterator;
		ConstTableIt begin();
		ConstIterator end();
		std::map<const std::string, Squad*>::const_iterator find(const std::string&);
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