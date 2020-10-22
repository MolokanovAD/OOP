//
// Created by Данил Морозов on 06/10/2020.
//

#include "biglong.h"
#pragma warning(disable : 4996)

namespace laba3bit1 {

    Biglong::Biglong(const Biglong& biglong) {
        Biglong::length = biglong.get_length();
        for (int i = 0; i <= MAX_LENGTH; ++i) {
            Biglong::value[i] = char(biglong.get_one_char(i));
        }
    }


    Biglong::Biglong() : length(0) {
        for (int i = 0; i <= MAX_LENGTH; ++i) {
            value[i] = '0';
        }
    };

    Biglong::Biglong(long parametr) {
        int counter = 0;
        long parametr_copy = parametr;
        if (parametr > 0) {
            Biglong::value[0] = '0';
        }
        else {
            Biglong::value[0] = '9';
            parametr_copy = -parametr_copy;
        }
        try {
            while (parametr_copy > 0) {
                if (MAX_LENGTH - counter < 1)
                    throw std::range_error("подано слишком большое значение long");
                Biglong::value[MAX_LENGTH - counter] = num_to_char(int(parametr_copy % 10));
                parametr_copy = parametr_copy / 10;
                ++counter;
            }
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
        Biglong::length = counter;
        for (int i = 1; i <= MAX_LENGTH - counter; ++i) {
            Biglong::value[i] = '0';
        }
    }


    Biglong::Biglong(const char* char_value) {
        int i = int(strlen(char_value)), j = 0;

        if (char_value[0] == '-') {
            value[0] = '9';
            j++;
            --i;
        }
        else {
            value[0] = '0';
            try {
                if ((char_value[0] < '0') || (char_value[0] > '9')) {
                    throw std::range_error("Попытка инициализировать класс некорректной строкой");
                }
            }
            catch (std::range_error & error) {
                std::cerr << error.what() << std::endl;
            }
        }
        try {
            if (i > MAX_LENGTH)
                throw std::range_error("попытка присвоить объекту слишком длинной строки");
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
        Biglong::length = i;
        try {
            while (char_value[j] != '\0') {
                if ((char_value[j] >= '0') & (char_value[j] <= '9')) {
                    value[MAX_LENGTH - i + 1] = char_value[j];
                    --i;
                    ++j;

                }
                else {
                    std::cout << "В строке встретился не числовой символ" << std::endl;
                    throw std::range_error("В строке встретился не числовой символ");
                }
            }
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
        for (int i = 1; i <= MAX_LENGTH - Biglong::length; ++i) {
            Biglong::value[i] = '0';
        }

    }

    void laba3bit1::Biglong::div10() {
        for (int i = MAX_LENGTH; i > 1; --i) {
            Biglong::value[i] = Biglong::value[i - 1];
        }
        if (value[1] != '0')
            value[1] = '0';
    }

    void laba3bit1::Biglong::multi10() {
        try {
            if (Biglong::value[1] == '0') {
                for (int i = 1; i < MAX_LENGTH; ++i) {
                    Biglong::value[i] = Biglong::value[i + 1];
                }
                Biglong::value[MAX_LENGTH] = '0';
            }
            else
                throw std::range_error("not enough space");
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
    }




    //----------------------------------------------------------------------тут пошла часть с перегрузками-----------------


    //вывод класса в поток
    std::ostream& operator<<(std::ostream& stream, const laba3bit1::Biglong& biglong) {
        //std::cout << "я тут2";
        int i = 1;
        if (biglong.get_one_char(0) == '9')
            stream << "-";
        while (i <= MAX_LENGTH) {
            stream << biglong.get_one_char(i);
            ++i;
        }
        stream << std::endl;
        return stream;
    }


    std::istream& operator>>(std::istream& istream, laba3bit1::Biglong& biglong) {
        try {
            for (int k = 1; k <= biglong.get_max_length(); ++k) {
                biglong.set_one_char(k, 0);
            }
            //std::cout << "tut" << std::endl;
            //char streamer[MAX_LENGTH + 1];
            char* streamer = readln();
            //istream >> streamer;                                                //здесь может быть считывание нормальной строки
            int i = int(strlen(streamer)), j = 0;
            if (i > biglong.get_max_length())
                throw std::range_error("the string is too long");
            if (streamer[0] == '-') {
                biglong.set_one_char(0, 1);
                j++;
                --i;
            }
            else {
                biglong.set_one_char(0, 0);
                if ((streamer[0] < '0') || (streamer[0] > '9')) {
                    throw std::range_error("incorrect data");
                }
            }
            biglong.set_length(i);
            while (streamer[j] != '\0') {
                if ((streamer[j] >= '0') & (streamer[j] <= '9')) {
                    //std::cout << "changing: " << biglong.get_max_length() - i + 1 << " on: " << streamer[j] << std::endl;
                    biglong.set_one_char(biglong.get_max_length() - i + 1, char_to_num(streamer[j]));
                    --i;
                    ++j;
                }
                else {
                    std::cout << "incorrect data" << std::endl;
                    throw std::range_error("incorrect data");
                }
            }
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
        return istream;

    }

    const Biglong Biglong::operator~() const {                      //здесь еще нужно написать прибавление единички
        Biglong newest(*this);
        if ((newest.get_one_char(0) == '9') || (newest.get_one_char(0) == '1')) {
            newest.set_one_char(0, 9);
            for (int i = 1; i <= MAX_LENGTH; ++i) {
                newest.set_one_char(i, 9 - char_to_num(newest.get_one_char(i)));
            }
            ++newest;
        }
        return newest;
    };


    Biglong& Biglong::operator++() {
        int a = 0, ostatok = 1, i = MAX_LENGTH;
        while ((i > 0)& (ostatok > 0)) {
            a = char_to_num(value[i]);
            a = ostatok + a;
            value[i] = num_to_char(a % 10);
            ostatok = a / 10;
            --i;
        }
        try {
            if ((i < 1) & (ostatok != 0)) {
                throw std::range_error("Overload");
            }
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
        return *this;
    }


    const Biglong Biglong::operator+(const Biglong& argument) const {
        Biglong result(*this);
        result = ~result;
        int a = 0, b = 0, over = 0;
        Biglong argument_copy;
        argument_copy = ~argument;
        for (int i = MAX_LENGTH; i >= 0; --i) {
            a = char_to_num(result.get_one_char(i));
            b = char_to_num(argument_copy.get_one_char(i));
            a = a + b + over;
            result.set_one_char(i, a % 10);
            over = a / 10;
        }
        //     std::cout << result.get_one_char(0) << "result0" << std::endl;
        //      std::cout << argument_copy.get_one_char(0) << "a_to_copy0" << std::endl;
        if (result.get_one_char(0) != '0') {
            result.set_one_char(0, 9);
            for (int i = 1; i <= MAX_LENGTH; ++i) {
                result.set_one_char(i, 9 - char_to_num(result.get_one_char(i)));
            }
            ++result;

        }
            if (argument.value[0] == value[0] && value[0] != result.value[0])
                throw std::exception("Overload");
        return result;
    }

    const Biglong Biglong::operator-(const Biglong& argument) const {
        Biglong argument_copy = argument;
        if (argument.get_one_char(0) == '0')
            argument_copy.set_one_char(0, 9);
        else
            argument_copy.set_one_char(0, 0);
        return (*this + argument_copy);
    }


    void Biglong::set_one_char(int number, int value) {
        Biglong::value[number] = num_to_char(value);
    }

    void Biglong::set_length(int new_length) {
        try {
            if (new_length < 0)
                throw std::range_error("Неприемлимая длина строки");
            Biglong::length = new_length;
        }
        catch (std::range_error & error) {
            std::cerr << error.what() << std::endl;
        }
    }


    Biglong Biglong::operator=(const Biglong& argument) {
        for (int i = 0; i <= MAX_LENGTH; ++i) {
            (*this).value[i] = argument.value[i];
        }
        (*this).length = argument.length;
        return *this;
    }




    char num_to_char(int num) {
        return num + '0';
    }

    int char_to_num(char char_a) {
        return char_a - '0';
    }


    char* readln(void) {
        fseek(stdin, 0, SEEK_END);

        //   printf("введите информацию\n");
        char* ptr = (char*)malloc(1);
        *ptr = '\0';
        char buf[101];
        int n, len = 0;
        do {
            n = scanf("%100[^\n]", buf);
            //printf("buff = %s\n",buf);
            if (n < 0) {
                free(ptr);
                ptr = nullptr;
                continue;
            }
            if (n == 0)
                scanf("%*c");
            else {
                len += strlen(buf);
                // printf("len = %d\n",len);
                ptr = (char*)realloc(ptr, len + 1);
                strcat(ptr, buf);
            }
        } while (n > 0);
        return ptr;
    }
}