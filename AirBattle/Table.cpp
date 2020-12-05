#include "Table.h"
namespace AirBattle {
	
	Table::Table(const Table& a) {
		std::map<const std::string, Squad*>::const_iterator p;
		for (p = a.arr.begin(); p != a.arr.end(); ++p)
			arr.insert(make_pair(p->first, p->second));
	}
	Table::~Table() {
		while (!arr.empty()) {
			std::map<const std::string, Squad*>::const_iterator i = arr.begin();
			delete (*i).second;
			arr.erase(i);
		}
	}


	double Table::get_det_decr(const double& xx, const double& yy) const{
		double res = 1.0;
		for (std::map<const std::string,Squad*>::const_iterator i = arr.begin(); i != arr.end(); i++) {
			res *= (*i).second->get_det_decr(xx,yy);
		}
		return res;
	}
	double Table::get_pro_decr(const double& x, const double& y) const{
		double res = 1.0;
		for (std::map<const std::string, Squad*>::const_iterator i = arr.begin(); i != arr.end(); i++) {
			res *= (*i).second->get_pro_decr(x,y);
		}
		return res;
	}
	double Table::get_disg_decr(const double& x, const double& y) const {
		double res = 1.0;
		for (std::map<const std::string, Squad*>::const_iterator i = arr.begin(); i != arr.end(); i++) {
			res *= (*i).second->get_disg_decr(x, y);
		}
		return res;
	}


	Plane& Table::find_by_coordinates(const double& x, const double& y) const {
		for (std::map<const std::string, Squad*>::const_iterator i = arr.begin(); i != arr.end(); i++)
			if ((abs(i->second->getx() - x) < 0.5) && (abs(i->second->gety() - y) < 120.5)) {
				Plane* res = nullptr;
				try {
					res = i->second->find_by_xy(x, y);
				}
				catch (std::runtime_error& a) {

				}
				if (res)
					return *res;
			}
		throw std::runtime_error("Miss");
	}

	bool Table::noticed(Table& planes_table, Plane& pl) {
		for (std::map<const std::string, Squad*>::const_iterator i = arr.begin(); i != arr.end(); i++) {
			if ((*i).second->noticed(pl, *this, planes_table))
				return true;
		}
		return false;
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
	ConstTableIt Table::find(const std::string& s) {
		ConstTableIt p = arr.find(s);
		return p;
	}
	Squad& Table::operator[] (const std::string& s) {
		std::map<const std::string, Squad*>::iterator p = arr.find(s);
		/*if (p == arr.end()) {
			std::pair<std::map<const std::string, Squad*>::iterator, bool> pp = arr.insert(make_pair(s, new Squad));                          //вставка звена
			if (!pp.second)
				throw std::exception("can't insert new item into map");
			p = pp.first;
		}*/
		return *(p->second); 
	}
	const Squad& Table::operator[] (const std::string& s) const {
		std::map<const std::string, Squad*>::const_iterator p = arr.find(s);
		if (p == arr.end()) 
			throw std::runtime_error("illegal index");
		return *(p->second);
	}
	std::ostream& operator<<(std::ostream& s, const Table& a)
	{
		s << "===== Table of squads =====" << std::endl;
		std::map<const std::string, Squad*>::const_iterator it;
		for (it = a.arr.begin(); it != a.arr.end(); ++it)
			std::cout << (*it).first << std::endl << *(*it).second << std::endl;
		return s;
	}
	
	
	void Table::Add(Squad* N,const std::string& s) {
		Squad* NN = new Squad(*N);
		std::pair<std::map<const std::string, Squad*>::iterator, bool> pp = arr.insert(make_pair(s, NN));                          //вставка звена
		if (!pp.second)
			throw std::runtime_error("can't insert new item into map");
	}
	bool Table::Delete(const std::string& s) {
		std::map<const std::string, Squad*>::const_iterator p = arr.find(s);
		if (p == arr.end()) 
			throw std::runtime_error("Invalid index");
		delete (*p).second;
		arr.erase(p);
		return true;
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