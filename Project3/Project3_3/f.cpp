#include <iostream>
#include "f.h"

char Interprete(int k) { // функция для трактовки результата сравнения
	switch (k) {
	case -1:
		return '<';
	case 0:
		return '=';
	case 1:
		return '>';
	}
}
void dialog(H16_3::Hex& a, H16_3::Hex& b) {
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
			try {
				a >>= r;
			}
			catch (std::exception & b) {
				std::cout << b.what() << std::endl;
				continue;
			}
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
			try {
				a <<= r;
			}
			catch (std::exception & b) {
				std::cout << b.what() << std::endl;
				continue;
			}
			std::cout << a << std::endl;
			break;
		case 3:
			std::cout << a << " " << Interprete(a.Compare(b)) << " " << b << std::endl;
			break;
		case 4:
			if (!a.Check())
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
}
H16_3::Hex f(const H16_3::Hex& b) {
	H16_3::Hex c(b);
	return c;
}
H16_3::Hex FF(const H16_3::Hex& m){
	H16_3::Hex dd = f(m);
	return dd;
}
