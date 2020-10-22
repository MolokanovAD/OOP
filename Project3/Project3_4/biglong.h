//
// Created by ����� ������� on 06/10/2020.
//

#ifndef LAB3BYTE1_BIGLONG_H
#define LAB3BYTE1_BIGLONG_H
#include <iostream>
#include <stdexcept>
#define  MAX_LENGTH 10

namespace laba3bit1 {


    class Biglong {
        int length;
        char value[MAX_LENGTH + 1]{};             //+ 1 ��� �����
    public:
        //�����������
        Biglong();    //������ �����������    //��������
        explicit Biglong(long parameter);  //������������� ����� ������� �����
        Biglong(const char* char_value);  //������������� �� ������
        Biglong(const Biglong& biglong);        //���������� �����������
        //�������
        int get_length() const { return length; };
        char get_one_char(int i) const { return value[i]; };
        int get_max_length() const { return MAX_LENGTH; };
        //�������
        void set_one_char(int number, int value);    //���������� ���������� ������
        void set_length(int new_length);       
        void div10();    //���������� �������� ����������� ����� � ������ ��� (������� �� 10 ������)�
        void multi10();  //���������� �������� ����������� ����� � ������ ���
        //����� � ������������
        friend std::ostream& operator<<(std::ostream& ostream, const Biglong& biglong); //����� � ������� �����
        friend std::istream& operator>>(std::istream& istream, Biglong& biglong); //���� �� �������� ������
        const Biglong operator~() const;//��������� ��������������� ���� ����� ((*) � ������� �������������� ��������� ~ )
        Biglong& operator ++();
        const Biglong operator+(const Biglong& argumnet) const;    //���������� �������� ��������
        const Biglong operator-(const Biglong& argument) const;
        Biglong operator=(const Biglong& argument);
    };

    char* readln(void);
    char num_to_char(int);
    int char_to_num(char a);

    template<class T>
    double getNum(T& a) {                //���������� ����� ���������������� ���� ������
        int i = 1;
        while (i == 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> a;
            if (!std::cin.good())
                i = 1;
            else
                i = 0;
            if (i != 0) std::cout << "�� ����� ������������ ��������, ��������� ����" << std::endl;
        }
        return 0;
    }
}

#endif //LAB3BYTE1_BIGLONG_H
