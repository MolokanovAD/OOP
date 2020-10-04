#include "Hex.h"
#include <iostream>
#include <stdio.h>



namespace Project3_3 {
	Hex::Hex() { //Пустой конструктор
		length = 1;
		number = new char[2];
		number[0] = '0';
		number[1] = '0';
	}
	Hex::Hex(char* a) {//Инициализирующий конструктор для инициализации строкой
		try {
			setN(a);
		}
		catch (std::exception & a) {
			throw std::exception("Wrong data");
		}
	}
	Hex::Hex(const int A) { //Инициализирующий конструктор для инициализации константой
		int a = A,b = A,size = 0;
		char sign = '0';
		if (a < 0) {
			sign = 'F';
			a *= -1;
			b = a;
		}
		for (; b; size++)
			b >>= 4;
		number = new char[size+1];
		int i = 0;
		i = size;
		number[0] = sign;
		for (; a; i--) {
			number[i] = HexToChar(a % 0x10);
			a >>= 4;
		}
		length = size;
		if (!length) {
			length = 1;
			number = new char[2];
			number[0] = '0';
			number[1] = '0';
		}
	}
	Hex::Hex(const Hex& A) {
		/*length = A.length;
		number = new char[length + 1];
		for (int i = 0; i <= length; i++)
			number[i] = A.number[i];*/
		*this = A;
	}
	void Hex::Formate(int k) {
		int new_size = length + k+1;
		char* a = number;
		number = new char[new_size];
		number[0] = a[0];
		for (int i = k+1; i < new_size; i++)
			number[i] = a[i-k];
		for (int i = 1; i <= k; i++)
			number[i] = '0';
		length += k;
		delete[] a;
	}
	Hex& Hex::setN(char* a) {
		int leng = strlen(a), i = 0;
		char sign = '0';
		switch (a[0]) {//Проверка знака
		case '+':
			i++;
			break;
		case '-':
			sign = 'F';
			i++;
			break;
		default:
			sign = '0';
		}
		if (a[i] == '0' && a[i + 1] == 'x')//проверка ввода числа, начинающегося с 0х
			i += 2;
		int size = leng - i + 1;
		/*if(size > 32)
			size = 32;*/
		number = new char[size];
		number[0] = sign;
		int ll = 1;
		//length = ((leng - i) > 31) ? 31 : leng - i;
		length = size - 1;
		for (; i < leng/* && ll < size*/; i++, ll++) {
			a[i] = upper(a[i]); //проверка регистра
			if ((a[i] < '0' || ('9' < a[i] && a[i] < 'A') || 'F' < a[i]))//проверка попадания символа в диапазон шестнадцатиричных цифр
				throw std::exception("Invalid symbol");
			number[ll] = a[i];
		}
		return *this;
	}
	char upper(const char a) {
		switch (a) {
		case 'a':return 'A';
		case 'b':return 'B';
		case 'c':return 'C';
		case 'd':return 'D';
		case 'e':return 'E';
		case 'f':return 'F';
		}
		return a;
	}
	char HexToChar(int num) {
		switch (num) {
		case 0x0: return '0';
		case 0x1: return '1';
		case 0x2: return '2';
		case 0x3: return '3';
		case 0x4: return '4';
		case 0x5: return '5';
		case 0x6: return '6';
		case 0x7: return '7';
		case 0x8: return '8';
		case 0x9: return '9';
		case 0xA: return 'A';
		case 0xB: return 'B';
		case 0xC: return 'C';
		case 0xD: return 'D';
		case 0xE: return 'E';
		case 0xF: return 'F';
		}
		return '/';
	}
	int CharToHex(char num) {
		switch (num) {
		case '0': return 0x0;
		case '1': return 0x1;
		case '2': return 0x2;
		case '3': return 0x3;
		case '4': return 0x4;
		case '5': return 0x5;
		case '6': return 0x6;
		case '7': return 0x7;
		case '8': return 0x8;
		case '9': return 0x9;
		case 'A': return 0xa;
		case 'B': return 0xb;
		case 'C': return 0xc;
		case 'D': return 0xd;
		case 'E': return 0xe;
		case 'F': return 0xf;
		}
		return -1;
	}
	int Hex::Check() { //проверка четности
		if (CharToHex(number[length]) & 1)
			return 0;
		return 1;
	}
	char Hex::Compare(const Hex& N) {
		Hex S(N),F(*this);
		if (number[0] < N.number[0]) //сначала проверка на разные знаки
			return '>';
		if (number[0] > N.number[0])
			return '<';
		int l = length, flag = 0;
		if (S.length > length) {
			l = S.length;
			F.Formate(l - length);
		}
		else
			S.Formate(length - S.length);
		for (int i = 1; i <= l; i++) { //выявляем модуль какого числа больше
			if (F.number[i] > S.number[i]) {
				i = l + 1;
				flag = 1;
				continue;
			}
			if (S.number[i] > F.number[i])
				i = l+1, flag = -1;
		}
		char sign = F.getSign();
		if (sign == '0') { //если число положительное, то больше то, модуль которого больше
			if (flag == 1)
				return '>';
			if (flag == -1)
				return '<';
		}
		if (flag == 1)//если число отрицательное, то больше то, модуль которого меньше
			return '<';
		if (flag == -1)
			return '>';
		return '=';
	}
	Hex& Hex::Convert() {
		for (int i = 1; i <= length; i++) { //инверитруем все разряды кроме знакового
			int n = 0xF - CharToHex(number[i]);
			number[i] = HexToChar(n);
		}
		int l = length;
		while (l > 0 && number[l] == 'F') // поиск места для добавления единицы
			l--;
		if (l == 0) // если места нет произошло переполнение
			throw std::exception("Incorrect operand");
		int k = CharToHex(number[l]) + 1;
		number[l] = HexToChar(k); //добавляем единицу в найденное место
		for (int i = l + 1; i <= length; i++)
			number[i] = '0';
		return *this;
	}
	const Hex Hex::operator +(const Hex& N) {
		Hex F(*this), Second(N);
		int l = length + 1, flag = 0;
		if (Second.length > length) {
			l = Second.length + 1;
		}
		F.Formate(l - F.length);
		Second.Formate(l - Second.length);
		Hex res(F);
		if (F.number[0] == 'F') //перевод чисел в дополнительный код при надобности
			F.Convert();
		if (Second.number[0] == 'F')
			Second.Convert();
		int transfer = 0;// transfer - перенос из младшего разряда
		res.number = new char[l + 1];
		for (int i = F.length; i > -1; i--) { //сложение чисел
			int sum = CharToHex(F.number[i]) + CharToHex(Second.number[i]) + transfer;
			res.number[i] = HexToChar((sum) % 0x10);
			transfer = 0;
			if (sum >>= 4)
				transfer = 1;
		}
		/*if (F.number[0] == Second.number[0] && Second.number[0] != res.number[0])
			throw std::exception("Overload"); //если знаки исходных чисел равны, а знак результата от них отличается - произошло переполнение*/
		if (res.number[0] == 'F')
			res.Convert();
		int k = 1;
		while (res.number[k] == '0') //вычисление длины результата
			k++;
		res.length = l + 1 - k;
		char* buf = res.number;
		res.number = new char[res.length + 1];
		res.number[0] = buf[0];
		for (int i = 1; i <= res.length; i++)
			res.number[i] = buf[k + i - 1];
		if (!res.length) {
			Hex a(0);
			res = a;
		}
		delete[] buf;
		return res;
	}
	const Hex Hex::operator -(const Hex& N) {
		Hex second = N, res;
		if (second.number[0] == '0') //домножаем второй операнд на -1
			second.number[0] = 'F';
		else
			second.number[0] = '0';
		res = *this + second;
		return res;
	}
	Hex& Hex::operator <<=(int a) {
		int l = length;
		length += a;
		char* buf = number;
		number = new char[length+1];
		int i = 0;
		for (; i <= l; i++)
			number[i] = buf[i];
		for (; i <= length; i++)
			number[i] = '0';
		return *this;
	}
	Hex& Hex::operator >>=(int a) {
		if (a >= length) {
			Hex a(0);
			*this = a;
			return *this;
		}
		length -= a;
		char* buf = number;
		number = new char[length + 1];
		for (int i = 0; i <= length; i++)
			number[i] = buf[i];
		return *this;
	}
	Hex& Hex::operator =(const Hex& A) {
		length = A.length;
		number = new char[length + 1];
		for (int i = 0; i <= length; i++)
			number[i] = A.number[i];
		return *this;
	}
	std::istream& operator >>(std::istream& c, Hex& El) {
		char* s = (char*)malloc(1), buf[35];
		int n = 0, l = 0;
		s[0] = '\0';
		do {
			n = scanf_s("%34[^\n]", buf, 35);
			if (n < 0)
			{
				free(s);
			}
			if (n > 0) {
				l += strlen(buf);
				s = (char*)realloc(s, l + 1);
				strcat_s(s, l + 1, buf);
			}
			else
				scanf_s("%*c");
		} while (n > 0);
		try {
			El.setN(s);
		}
		catch (std::exception & a) {
			c.setstate(std::ios::failbit);
		}
		return c;
	}
	std::ostream& operator <<(std::ostream& c, const Hex& El) {
		if (El.number[0] == 'F')
			c << "-";
		for (int j = 1; j <= El.length; j++)
			c << El.number[j];
		return c;
	}
}
