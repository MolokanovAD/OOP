#include "Strophoid.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Project2::Strophoid STR;
	int fl1 = 1;
	double A;
	char* s = NULL;
	while (fl1) {
		std::cout << "Your strophoid is:" << std::endl;
		s = STR.formula();
		std::cout << s << std::endl;
		delete[] s;
		std::cout << "Radius of curvature in (0,0) is " << STR.curv_rad() << std::endl;
		std::cout << "Loop area is " << STR.S(Project2::minus) << std::endl;
		std::cout << "Area between asymptote and branches of the strophoid is " << STR.S(Project2::plus) << std::endl;
		std::cout << "The volume of figure produced by rotating the loop around the Ox axis is " << STR.V() << std::endl;
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter x to calculate value y(x) or press ctrl+Z to quit:" << std::endl;
			double x;
			std::cin >> x;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			try {
				double res = STR.findY(x);
				std::cout << "y1 = " << res;
				if (res)
					std::cout << ", y2 = " << (-1)*res;
				std::cout << std::endl;
			}
			catch (std::exception & ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		std::cin.clear();
		fl2 = 1;
		while (fl2) {
			std::cout << "Enter angle to calculate the distance from the center in polar coordinate system or press ctrl+Z to quit:" << std::endl;
			double x;
			std::cin >> x;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			try {
				double res = STR.dist(x);
				std::cout << "L = " << res << std::endl;;
			}
			catch (std::exception & ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		std::cin.clear();
		A = 0;
		do {
			std::cout << "Enter new coefficient to continue or press ctrl+Z to quit:" << std::endl;
			std::cin >> A;
			fl2 = 0;
			if (std::cin.good()) {
				try {
					STR.setA(A);
				}
				catch (std::exception & ex) {
					std::cout << ex.what() << std::endl;
					fl2 = 1;
				}
			}
			else
				fl1 = 0;
		} while (fl2);
	}
	return 0;
}
