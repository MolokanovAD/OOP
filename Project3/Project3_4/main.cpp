#include "biglong.h"
#include <iostream>
#pragma warning(disable : 4996)


void out_up(const char* msg){
        std::cout << " _______________________________________________" <<
        std::endl << "|" << msg << "                                   |" << std::endl;
}
void out_down() {
        std::cout << "|_______________________________________________|" <<
        std::endl << "|           |           |           |           |" <<
        std::endl << "|     7     |     8     |     9     |     +     |" <<
        std::endl << "|___________|___________|___________|___________|" <<
        std::endl << "|           |           |           |           |" <<
        std::endl << "|     4     |     5     |     6     |     -     |" <<
        std::endl << "|___________|___________|___________|___________|" <<
        std::endl << "|           |           |           |           |" <<
        std::endl << "|     1     |     2     |     3     |      /    |" <<
        std::endl << "|___________|___________|___________|___________|" <<
        std::endl << "|           |           |           |           |" <<
        std::endl << "|     ~     |     0     |     ++    |      *    |" <<
        std::endl << "|___________|___________|___________|___________|" << std::endl;
}
int main() {
    
	laba3bit1::Biglong a, b,c;
	bool flag = false;
	while (!flag) {
        out_up("Enter number");
        std::cout << "|                                               |" <<std::endl;
        out_down();
        try {
            std::cin >> a;
        }
        catch (std::exception & a) {
            flag = true;
            continue;
        }
        out_up("Enter sign  ");
        std::cout << "|                                   ";
        if (a.get_one_char(0) == '0')
            std::cout << " ";
        std::cout << a << " |" << std::endl;
        out_down();
        char sign;
        std::cin >> sign;
        switch (sign) {
        case '~':
            c = ~a;
            out_up("            ");
            std::cout << "|                   ~";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << "  = " << c << " |" << std::endl;
            out_down();
            break;
        case '*':
            out_up("            ");
            std::cout << "|               ";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << " * 10  = ";
            a.multi10();
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << " |" << std::endl;
            out_down();
            break;
        case '/':
            out_up("            ");
            std::cout << "|               ";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << " / 10  = ";
            a.div10();
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << " |" << std::endl;
            out_down();
            break;
        case '+':
            if (std::cin.rdbuf()->in_avail() > 1) {
                std::cin >> sign;
                if (sign == '+') {
                    out_up("            ");
                    std::cout << "|              ";
                    if (a.get_one_char(0) == '0')
                        std::cout << " ";
                    std::cout << a << "  +  1  = ";
                    ++a;
                    if(a.get_one_char(0) == '0')
                        std::cout << " ";
                    std::cout << a << " |" << std::endl;
                    out_down();
                    break;
                }
            }
            out_up("Enter number");
            std::cout << "|                                 ";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << " + |" << std::endl;
            out_down();
            try {
               std::cin >> b;
            }
            catch (std::exception & a) {
               flag = true;
               continue;
            }
            out_up("            ");
            std::cout << "|  ";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a;
            if (b.get_one_char(0) == '0') {
                std::cout << "  +  ";
                std::cout << b << "  =  ";
            }
            else {
                std::cout << "  +(";
                std::cout << b << ") =  ";
            }
            c = a + b;
            if (c.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << c << "   |" << std::endl;
            out_down();
            break;
        case '-':
            out_up("Enter number");
            std::cout << "|                                 ";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a << " + |" << std::endl;
            out_down();
            try {
                std::cin >> b;
            }
            catch (std::exception & a) {
                flag = true;
                continue;
            }
            out_up("            ");
            std::cout << "|  ";
            if (a.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << a;
            if (b.get_one_char(0) == '0') {
                std::cout << "  -  ";
                std::cout << b << "  =  ";
            }
            else {
                std::cout << "  -(";
                std::cout << b << ") =  ";
            }
            c = a - b;
            if (c.get_one_char(0) == '0')
                std::cout << " ";
            std::cout << c << "   |" << std::endl;
            out_down();
            break;
        default:
            std::cout << "Wrong sign, repeat please!" << std::endl;
        }
        std::cout << "Press 0 to enter new numbers and any other button to exit" << std::endl;
        std::cin >> flag;
	}
	return 0;
}
