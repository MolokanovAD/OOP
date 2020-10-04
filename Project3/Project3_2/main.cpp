#include <iostream>
#include "Hex.h"

int main() {
	Project3_2::Hex a, b;
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
			Project3_2::Hex c = a + b;
			if (b.getSign() == 'F')
				std::cout << a << " + (" << b << ") = " << c << std::endl;
			else
				std::cout << a << " + " << b << " = " << c << std::endl;
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		try {
			Project3_2::Hex c = a - b;
			if (b.getSign() == 'F')
				std::cout << a << " - (" << b << ") = " << c << std::endl;
			else
				std::cout << a << " - " << b << " = " << c << std::endl;
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		int k = 0;
		while (k != 5) {
			std::cout << "1) Move first operand to the right" << std::endl << "2) Move first operand to the left" << std::endl << "3) Compare operands" << std::endl << "4) Check parity of first operand" << std::endl << "5) Exit" << std::endl;
			try {
				std::cin >> k;
			}
			catch (std::exception & b) {
				std::cout << b.what() << std::endl;
			}
			switch (k) {
			case 1:
				int r;
				std::cout << "Enter number of digits" << std::endl;
				try {
					std::cin >> r;
				}
				catch (std::exception & b) {
					std::cout << b.what() << std::endl;
					continue;
				}
				a >>= r;
				std::cout << a << std::endl;
				break;
			case 2:
				std::cout << "Enter number of digits" << std::endl;
				try {
					std::cin >> r;
				}
				catch (std::exception & b) {
					std::cout << b.what() << std::endl;
					continue;
				}
				a <<= r;
				std::cout << a << std::endl;
				break;
			case 3:
				std::cout << a << " " << a.Compare(b) << " " << b << std::endl;
				break;
			case 4:
				if (a.Check())
					std::cout << a << " is an even number" << std::endl;
				else
					std::cout << a << " isn't an even number" << std::endl;
				break;
			case 5:
				continue;
			default:
				std::cout << "You are wrong, repeat please" << std::endl;
			}
		}
		std::cout << "Press 0 if you want to exit or any other number" << std::endl;
		std::cin >> flag;
		scanf_s("%*c");
	}
}