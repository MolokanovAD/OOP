#ifndef _TABLE_H_
#define _TABLE_H_
#include "Squad.h"
#include <iostream>
#include <map>

namespace AirBattle {
	/*!
		\brief �������.
		�������� ������ �������.
	*/
	class Table {
	protected:
		/*!
			\brief ������������� ������, � ������� �������� ����� - ������, � ��������� �� ����� - ����������
		*/
		std::map<const std::string, Squad*> arr;
	public:
		Table() {}
		Table(const Table&);
		~Table();

		int get_size() const { return arr.size(); }
		/*!
			\brief ����������� ���������� ������� ����������� ���������� � �������� �����, ������������ ���� �������� ������������.
			\param[in] ����������
		*/
		double get_det_decr(const double&, const double&) const;
		/*!
			\brief ����������� ���������� ������ ��� ���������� � �������� �����, ������������ ���� �������� ������������.
			\param[in] ����������
		*/
		double get_pro_decr(const double&, const double&) const;
		/*!
			\brief ����������� ���������� ���������� ���������� � �������� �����, ������������ ���� �������� ������������.
			\param [in] ����������
		*/
		double get_disg_decr(const double&, const double&) const;
		/*!
			\brief ����� �������� ������� ������������ �� �����������.
			\param[in] ����������
		*/
		Plane& find_by_coordinates(const double&, const double&) const;
		/*!
			\brief ����� ��������� ������ ��������� �� ������� ����������.
			\param[in] ����� �� ������� ������� ����������, ������ �� ������� ����������
		*/
		bool noticed(Table&, Plane&);

		Table& operator =(const Table&);
		Squad& operator [](const std::string&);
		const Squad& operator [](const std::string&) const;
		/*!
			\brief ���������� ����� � �������.
			\param[in] ��������� �� �����, �������� ������ �����
		*/
		void Add(Squad*, const std::string&);
		/*!
			\brief �������� �����
			\param[in]�������� �����
		*/
		bool Delete(const std::string&);
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