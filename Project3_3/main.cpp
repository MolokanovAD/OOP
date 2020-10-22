#include <iostream>
#include "Hex.h"
#include "f.h"


int main() {
	H16_3::Hex a, b,m;
	m = FF(a);
	int flag = 1;
	while (flag) {
		std::cout << "Enter first hexadecimal value" << std::endl;
		std::cin >> a;
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		std::cout << "Enter second hexadecimal value" << std::endl;
		std::cin >> b;
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		try {
			H16_3::Hex c = a + b;
			if (b.getSign() == 'F')
				std::cout << a << " + (" << b << ") = " << c << std::endl;
			else
				std::cout << a << " + " << b << " = " << c << std::endl;
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		try {
			H16_3::Hex c;
			c = a - b;
			if (b.getSign() == 'F')
				std::cout << a << " - (" << b << ") = " << c << std::endl;
			else
				std::cout << a << " - " << b << " = " << c << std::endl;
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		dialog(a, b);
		std::cout << "Press 0 if you want to exit or any other number" << std::endl;
		std::cin >> flag;
		scanf_s("%*c");
	}
}