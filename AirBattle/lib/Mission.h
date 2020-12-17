#ifndef _MISSION_H_
#define _MISSION_H_
#include <iostream>
#include "Table.h"

namespace AirBattle {
	/*!
		\brief ������
		�������� ���������� � ������� ������� ������.
	*/
	class Mission
	{
	protected:
		/*!
			\brief ������� ������� ������������
		*/
		Table a;
		/*!
			\brief ������� ��������� �������
		*/
		Table b;
	public:
		Mission();
		Mission(const int&, const int&, std::string*, std::string*, const int&, const int&);

		~Mission() {}

		Table& get_table(const bool&);
		/*!
			\brief ����� ����� �� ���������.
		*/
		Squad& find_squad(const std::string&, bool);
		/*!
			\brief ����� �������� �� �������.
			\param[in] ��������, ������, ���� ��� ��������� �������
		*/
		Plane& find_plane(const std::string&, const int&, bool);

		/*!
			\brief �������� ������� ������ �� �����.
		*/
		void save(const std::string&);
		/*!
			\brief ���������� ���������� �� ������� ������ � ����.
		*/
		void load(const std::string&);
	};
}
#endif