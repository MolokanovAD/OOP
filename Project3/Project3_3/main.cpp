#include <iostream>
#include "Hex.h"
#include "f.h"

int main() {
	H16_3::Hex a, b;
	bool flag = false;
	while (!flag) {
		std::cout << "Enter first hexadecimal value" << std::endl;
		std::cin >> a;
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = true;
			continue;
		}
		std::cout << "Enter second hexadecimal value" << std::endl;
		std::cin >> b;
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = true;
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
		std::cout << "Press 0 to enter new numbers and any other button to exit" << std::endl;
		std::cin >> flag;
		scanf_s("%*c");
	}
}
