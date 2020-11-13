#include "Table.h"
namespace AirBattle {
	/*std::ostream& operator <<(std::ostream& os, const std::pair<std::string,Squad*>& p) {
		return os << p.first << " - " << p.second;
	}*/
	Table::Table(const Table& a) {
		std::map<const std::string, Squad*>::const_iterator p;
		for (p = a.arr.begin(); p != a.arr.end(); ++p)
			arr.insert(make_pair(p->first, p->second));
	}
	Table& Table::operator =(const Table& a) {
		std::map<const std::string, Squad*>::const_iterator p;
		if (this != &a) {
			arr.clear();
			for (p = a.arr.begin(); p != a.arr.end(); ++p)
				arr.insert(make_pair(p->first, p->second));
		}
		return *this;
	}
	Squad*& Table::operator[] (const std::string& s) {
		std::map<const std::string, Squad*>::iterator p = arr.find(s);
		if (p == arr.end()) {
			std::pair<std::map<const std::string, Squad*>::iterator, bool> pp = arr.insert(make_pair(s, new Squad));                          //вставка звена
			if (!pp.second)
				throw std::exception("can't insert new item into map");
			p = pp.first;
		}
		return p->second; 
	}
	std::map<const std::string, Squad*>::const_iterator Table::find(const std::string& s) {
		std::map<const std::string, Squad*>::iterator p = arr.find(s);
		return std::map<const std::string, Squad*>::const_iterator(p);
	}
	bool Table::Delete(const std::string& s) {
		std::map<const std::string, Squad*>::iterator p = arr.find(s);
		if (p == arr.end()) {
			return false;
		}
		Squad* a = (*p).second;
		a->~Squad();
		arr.erase(p);
		return true;
	}
	Squad* Table::operator[] (const std::string& s) const {
		std::map<const std::string, Squad*>::const_iterator p = arr.find(s);
		if (p == arr.end()) 
			throw std::exception("illegal index");
		return p->second;
	}
	std::ostream& operator<<(std::ostream& s, const Table& a)
	{
		s << "===== Table of squads =====" << std::endl;
		std::map<const std::string, Squad*>::const_iterator it;
		for (it = a.arr.begin(); it != a.arr.end(); ++it)
			std::cout << (*it).first << std::endl << *(*it).second << std::endl;
		return s;
	}
	Table::ConstIterator Table::begin() {
		return ConstTableIt(arr.begin());
	}
	Table::ConstIterator Table::end() {
		return ConstTableIt(arr.end());
	}
	int ConstTableIt::operator !=(const ConstTableIt& it) const {
		return current != it.current;
	}
	int ConstTableIt::operator ==(const ConstTableIt& it) const {
		return current == it.current;
	}
	std::pair<const std::string, Squad*>& ConstTableIt::operator *() {
		return *current;
	}
	std::pair<const std::string, Squad*>* ConstTableIt::operator ->() {
		return &(*current);
	}
	ConstTableIt& ConstTableIt::operator ++() {
		++current;
		return *this;
	}
	ConstTableIt ConstTableIt::operator ++(int) {
		ConstTableIt res(*this);
		++current;
		return res;
	}
}