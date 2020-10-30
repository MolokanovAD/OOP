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
        std::endl << "|     1     |     2     |     3     |    /10    |" <<
        std::endl << "|___________|___________|___________|___________|" <<
        std::endl << "|           |           |           |           |" <<
        std::endl << "|     ~     |     0     |     ++    |    *10    |" <<
        std::endl << "|___________|___________|___________|___________|" << 
	std::endl << "|                    _______                    |" <<
        std::endl << "|                    _______                    |" <<
        std::endl << "|_______________________________________________|" <<std::endl;
}
void out(laba3bit1::Biglong a,const char* m) {
    if (a.get_one_char(0) == '0')
        std::cout << " ";
    std::cout << a << m;
}
void fix_length_1_operand(laba3bit1::Biglong a,const char* msg) {
    out_up(msg);
    std::cout << "|                                   ";
    out(a, " |");
    std::cout << std::endl;
    out_down();
}

void multi_f(laba3bit1::Biglong a,int k) {
    out_up("            ");
    std::cout << "|               ";
    if (k == 1) {
        out(a, " * 10  = ");
        a.multi10();
    }
    else {
        out(a, " / 10  = ");
        a.div10();
    }
    out(a, " |");
    std::cout << std::endl;
    out_down();
}
int main() {
    
	laba3bit1::Biglong a, b,c;
	bool flag = false, flag2 = false;
    while (!flag) {
        out_up("Enter number");
        std::cout << "|                                               |" << std::endl;
        out_down();
        try {
            std::cin >> a;
        }
        catch (std::exception & a) {
            flag = true;
            continue;
        }
        while (!flag2){
        fix_length_1_operand(a, "Enter sign  ");
        char sign;
        std::cin >> sign;
        switch (sign) {
        case '~':
            c = ~a;
            out_up("            ");
            std::cout << "|                   ~";
            out(a, "  = ");
            std::cout << c << " |" << std::endl;
            out_down();
            break;
        case '*':
            multi_f(a, 1);
            break;
        case '/':
            multi_f(a, 0);
            break;
        case '+':
            if (std::cin.rdbuf()->in_avail() > 1) {
                std::cin >> sign;
                if (sign == '+') {
                    out_up("            ");
                    std::cout << "|              ";
                    out(a, "  +  1  = ");
                    ++a;
                    out(a, " |");
                    std::cout << std::endl;
                    out_down();
                    break;
                }
            }
            out_up("Enter number");
            std::cout << "|                                 ";
            out(a, " + |");
            std::cout << std::endl;
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
            out(a, "");
            if (b.get_one_char(0) == '0') {
                std::cout << "  +  ";
                std::cout << b << "  =  ";
            }
            else {
                std::cout << "  +(";
                std::cout << b << ") =  ";
            }
            try {
                c = a + b;
            }
            catch (std::exception & a) {
                std::cout << a.what();
                std::cout << "      |" << std::endl;
                out_down();
                break;
            }
            out(c, "   |");
            std::cout << std::endl;
            out_down();
            break;
        case '-':
            out_up("Enter number");
            std::cout << "|                                 ";
            out(a, " - |");
            std::cout << std::endl;
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
            out(a, "");
            if (b.get_one_char(0) == '0') {
                std::cout << "  -  ";
                std::cout << b << "  =  ";
            }
            else {
                std::cout << "  -(";
                std::cout << b << ") =  ";
            }
            try {
                c = a - b;
            }
            catch (std::exception & a) {
                std::cout << a.what();
                std::cout << "      |" << std::endl;
                out_down();
                break;
            }
            out(c, "   |");
            std::cout << std::endl;
            out_down();
            break;
        default:
            std::cout << "Wrong sign!" << std::endl;
        }
        while (std::cin.rdbuf()->in_avail() > 1)
            std::cin >> sign;
        std::cout << "Press = to work with the result" << std::endl;
        char s;
        std::cin >> s;
        if (s != '=')
            flag2 = true;
        else
            a = c;
    }
        std::cout << "Press 0 to enter new numbers and any other button to exit" << std::endl;
        std::cin >> flag;
	}
	return 0;
}
