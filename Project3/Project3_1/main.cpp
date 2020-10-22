#include <iostream>
#include "Hex.h"
#include <stdio.h>

void dialog(H16_1::Hex& a, H16_1::Hex& b) {
	int k = 0;
	while (k != 5) {
		std::cout << "1) Move first operand to the right" << std::endl << "2) Move first operand to the left" << std::endl << "3) Compare operands" << std::endl << "4) Check parity of first operand" << std::endl << "5) Exit" << std::endl;
		std::cin >> k;
		if (!std::cin.good()) {
			std::cout << "Invalid input" << std::endl;
			k = 5;
			continue;
		}
		switch (k) {
		case 1:
			int r;
			std::cout << "Enter number of digits" << std::endl;
			std::cin >> r;
			if (!std::cin.good()) {
				std::cout << "Invalid input" << std::endl;
				k = 5;
				continue;
			}
			try {
				a.Move_r(r);
			}
			catch (std::exception & b) {
				std::cout << b.what() << std::endl;
				continue;
			}
			a.Print(std::cout);
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "Enter number of digits" << std::endl;
			std::cin >> r;
			if (!std::cin.good()) {
				std::cout << "Invalid input" << std::endl;
				k = 5;
				continue;
			}
			try {
				a.Move_l(r);
			}
			catch (std::exception & b) {
				std::cout << b.what() << std::endl;
				continue;
			}
			a.Print(std::cout);
			std::cout << std::endl;
			break;
		case 3:
			a.Print(std::cout);
			std::cout << " " << a.Compare(b) << " ";
			b.Print(std::cout);
			std::cout << std::endl;
			break;
		case 4:
			if (!a.Check()) {
				a.Print(std::cout);
				std::cout << " is an even number" << std::endl;
			}
			else {
				a.Print(std::cout);
				std::cout << " isn't an even number" << std::endl;
			}
			break;
		case 5:
			continue;
		default:
			std::cout << "You are wrong, repeat please" << std::endl;
		}
	}
}
void out(H16_1::Hex& a, H16_1::Hex& b, H16_1::Hex& c, const char* msg) {
	if (b.getSign() == 'F') {
		a.Print(std::cout);
		std::cout << msg << "(";
		b.Print(std::cout);
		std::cout << ") = ";
		c.Print(std::cout);
		std::cout << std::endl;
	}
	else {
		a.Print(std::cout);
		std::cout << msg;
		b.Print(std::cout);
		std::cout << " = ";
		c.Print(std::cout);
		std::cout << std::endl;
	}
}

int main() {
	H16_1::Hex a, b;
	int flag = 1;
	while (flag) {
		std::cout << "Enter first hexadecimal value" << std::endl;
		a.Input(std::cin);
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		std::cout << "Enter second hexadecimal value" << std::endl;
		b.Input(std::cin);
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		try {
			H16_1::Hex c(a.Add(b));
			out(a, b, c, " + ");
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		try {
			H16_1::Hex c(a.Decrease(b));
			out(a, b, c, " - ");
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		dialog(a, b);
		std::cout << "Press 0 if you want to exit or any other number to continue" << std::endl;
		std::cin >> flag;
		scanf_s("%*c");
	}
}
