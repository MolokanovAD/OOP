include <iostream>
#include "Hex.h"
#include <stdio.h>
int main() {
	Project3_1::Hex a, b;
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
			Project3_1::Hex c(a.Add(b));
			out(a, b, c, " + ");
		}
		catch (std::exception & b) {
			std::cout << b.what() << std::endl;
		}
		try {
			Project3_1::Hex c(a.Decrease(b));
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
