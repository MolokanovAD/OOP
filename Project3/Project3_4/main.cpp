#include "biglong.h"
#include <iostream>
#pragma warning(disable : 4996)
int main() {
	laba3bit1::Biglong a, b,c;
	bool flag = false;
	while (!flag) {
		std::cout << "Enter first value" << std::endl;
        try {
            std::cin >> a;
        }
        catch (std::exception & a) {
            flag = true;
            continue;
        }
		std::cout << "Enter second value" << std::endl;
        try {
            std::cin >> b;
        }
        catch (std::exception & a) {
            flag = true;
            continue;
        }
        try {
            c = a + b;
            std::cout << "First + Second:" << std::endl << a << b << c;
        }
        catch (std::exception & a) {
            std::cout << a.what() << std::endl;
        }
        try {
            c = a - b;
            std::cout << "First - Second:" << std::endl << a << b << c;
        }
        catch (std::exception & a) {
            std::cout << a.what() << std::endl;
        }
        int k = 0;
        while (k != 5) {
            std::cout << "Here are your options" << std::endl << "Press 1 to get additional code of first operand" << std::endl << "Press 2 to add 1 to first operand" << std::endl << "Press 3 to move first operand to the left" << std::endl <<  "Press 4 to move first operand to the right" << std::endl << "Press 5 to exit" << std::endl;
            std::cin >> k;
            switch (k) {
            case 1:
                c = ~a;
                std::cout << c;
                break;
            case 2:
                std::cout << ++a;
                break;
            case 3:
                a.multi10();
                std::cout << a;
                break;
            case 4:
                a.div10();
                std::cout << a;
                break;
            case 5:
                break;
            default:
                std::cout << "Wrong number, repeat please!" << std::endl;
            }
        }
        std::cout << "Press 0 to enter new numbers and any other button to exit" << std::endl;
        std::cin >> flag;
	}
	return 0;
}