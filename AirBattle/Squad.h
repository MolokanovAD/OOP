#ifndef _SQUAD_H_
#define _SQUAD_H_
#include "Plane.h"
#include <iostream>
#include "other_vector.h"
namespace AirBattle {
	/*!
		\brief �����.
		�������� ������ �����, ���������� ��������� � �����(�� ������ 4), ���������� � ������ ���������.
	*/
	class Squad{
	protected:
		/*!
			\brief ������ �����
		*/
		int command;
		/*!
			\brief ������� ���������� ���������
		*/
		unsigned char N;
		double x;
		double y;
		other_vector<Plane*> plane;
	public:
		Squad(const int& x0 = 0, const int& y0 = 0, const int& command = 0 , const int& anti_rocket = 0, const int& radio = 0, const int& disguise = 0, const int& scout = 0);
		Squad(const Squad&);
		Squad(Squad&&);
		~Squad();

		int get_command() const { return command; }
		double getx()const { return x; }
		double gety()const { return y; }
		unsigned char get_N()const { return N; }
		/*!
			\brief ���������� ������ ����������� �����.
			������ ����������� ����� ����� ����������� �� �������� ����������� ��������� ����� �����.
		*/
		double get_det_range()const;
		/*!
			\brief ���������� ���������� �����.
			���������� ����� ����� ���������� �� ���������� ��������� ����� �����.
		*/
		double get_disguise()const;
		/*!
			\brief ���������� �������� �����.
			�������� ����� ����� ���������� �� ��������� ��������� ����� �����.
		*/
		int get_speed() const;
		/*!
			\brief ���������� ����������� ���������� ������� ����������� �����, ������������ ���������� �����.
			����������� ����� ������������ ������������� ���� ��������� �����.
		*/
		double get_det_decr(const double&, const double&) const;
		/*!
			\brief ���������� ����������� ���������� ������ ��� �����, ������������ ���������� �����.
			����������� ����� ������������ ������������� ���� ��������� �����.
		*/
		double get_pro_decr(const double&, const double&) const;
		/*!
			\brief ���������� ����������� ���������� ���������� �����, ������������ ���������� �����.
			����������� ����� ������������ ������������� ���� ��������� �����.
		*/
		double get_disg_decr(const double&, const double&) const;
		/*!
			\brief ��������� �������� �� �������.
		*/
		Plane*& get_plane(const int&);
		/*!
			\brief ����� ��������� ������ ����� �� ����� ��������� �������.
			\param[in] ������ �� ��������� �������, ������� ������� ������������, ������� ������� ����������
			\return true - ����� ����� �������, false - �� �����.
		*/
		bool noticed(Plane&, Table&, Table&)const;

		void set_N(const unsigned char&);
		void set_command(const int&);
		other_vector<Plane*>::iterator begin() const { return plane.begin(); }
		other_vector<Plane*>::iterator end() const { return plane.end(); }

		/*!
			\brief ����� �������� �����.
			\param[in] ����������, �����, ��������� ��������
			\return ���������� �� ����� ��������.
			����������� ���������� �� ����� ��������, �������� ����� � ���������� �������� �� �����.
			\code
				x += speed*time*(goal_x - current_x) / distance * multiplier;
				double new_y = speed*time*(goal_y - current_y) / distance * multiplier;
				y += new_y;
			\endcode
		*/
		double go(const double& x, const double& y, float& time, const double& m = 1.0);
		/*!
			\brief ����� ���������� �����.
			\param[in] ������ �� ��������� �����, ������� ������� ������������, ������� ������� ����������, �����
			������� �������� ���������� ������ ���������� �������� � ���������� ������� ��������.
			���� ������� �� ��� �������� ���������� ������� �������� �� ������� �������� �� ������� ������������ ��������. 
			��� �� ������� ������ ������� ����� ��������� ���� �����.
		*/
		void attack_squad(Squad&, Table&, Table&, const int&);
		/*!
			\brief ����� ���������� ��������.
			\param[in] ������ �� ��������� �������, ������� ������� ������������, ������� ������� ����������, �����
			������ ������� ����� �� ������� ������� ����.
		*/
		void attack_plane(Plane&, Table&, Table&, const int&);

		/*!
			\brief ����� �������� ����� �� �����������.
			\param[in] ����������
		*/
		Plane*& find_by_xy(const int&, const int&);
		/*!
			\brief �������� �������� �� �����
			\param[in] ������ �� �������
		*/
		void Delete(Plane&);
		/*!
			\brief ���������� ����� �������� � �����
			\param[in] ��������� �� �������
		*/
		void Add(Plane*);
		
	};
}
#endif