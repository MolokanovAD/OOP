#ifndef _GUN_H_
#define _GUN_H_
#include "Weapon.h"

namespace AirBattle {
	/*!
		\brief �����.
		�������� ����������� ��������. ����� ����� ������������ ��������� �������� � �������������� ��������.
	*/
	class Gun : public Weapon
	{
	protected:
		/*!
			\brief ����������� ��������
		*/
		double accuracy;
		virtual std::ostream& show(std::ostream&)const;
	public:
		Gun(int r = 300, double a = 0.9, double f = 1500.0, int d = 150);
		Gun(const Gun&);

		double get_accuracy() const { return accuracy; }

		void set_accuracy(const double&);

		virtual ~Gun() {}
		virtual Gun* clone() const;
		virtual bool iam()const { return true; }
		/*!
			\brief ������� �� ����� �� �����������.
			\param[in] ����������, ���������� �� ����,������� ��������� �������, �����
			\return true - ���� ���������� � ������� ���������, false - ������� �� ���������(��-�� ���� ��� ���� �� ������ ����������� �� ����������, ���� ����� ��������������).
		*/
		virtual bool shot(const double&, const double&, const double&, Table&, const int&);
	};
}
#endif