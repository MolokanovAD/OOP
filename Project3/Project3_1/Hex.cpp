#include "Hex.h"
#include <iostream>

namespace Project3_1 {
	Hex::Hex() { //Пустой конструктор
		length = 1;
		for (int i = 0; i < len; i++)
			number[i] = '0';
	}
	Hex::Hex(char* a) { //Инициализирующий конструктор для инициализации строкой
		try{
			setN(a);
		}
		catch (std::exception & a) {
			throw std::exception("Wrong data");
		}
	}
	Hex::Hex(const int A) { //Инициализирующий конструктор для инициализации константой
		int a = A;
		if (a < 0) {
			number[0] = 'F';
			a = -a;
		}
		else
			number[0] = '0';
		int i = 0;
		i = len - 1;
		for (; a; i--) {
			number[i] = HexToChar(a & 0xf);
			a >>= 4;
		}
		for (int j = 1; j <= i; j++)
			number[j] = '0';
		length = len - i - 1;
		if (!length)
			length = 1;
	}
	Hex& Hex::setN(char* a) {
		int leng = strlen(a), i = 0;
		if(!leng)
			throw std::exception("Wrong data");
		if (leng > (len + 2)) {
			a[len + 2] = '\0';
			leng = len + 1;
		}
		switch (a[0]) {//Проверка знака
		case '+':
			i++;
			break;
		case '-':
			number[0] = 'F';
			i++;
			break;
		default:
			number[0] = '0';
		}
		if (a[i] == '0' && a[i + 1] == 'x')//проверка ввода числа, начинающегося с 0х
			i += 2;
		int ll = len - leng + i;//место, с которого начинаем вводить число в массив
		if (ll < 1)
			ll = 1;
		for (int j = 1; j < ll; j++)// заполняем массив нулями до значащих цифр
			number[j] = '0';
		length = ((leng - i) > 31) ? 31 : leng - i;
		for (; i < leng && ll < len; i++, ll++) {
			a[i] = upper(a[i]); //проверка регистра
			if ((a[i] < '0' || ('9' < a[i] && a[i] < 'A') || 'F' < a[i]))//проверка попадания символа в диапазон шестнадцатиричных цифр
				throw std::exception("Invalid symbol");
			number[ll] = a[i];
		}
		if (leng - i > 31)
			std::cout << "Only first 31 digit will be read" << std::endl;
		if (number[0] == 'F' && length == 1 && number[len - 1] == '0') {
			Hex c;
			*this = c;
		}
		free(a);
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
	int Hex::Check() const{ //проверка четности
		if (CharToHex(number[31]) & 1)
			return 0;
		return 1;
	}
	char Hex::Compare(const Hex& N) {
		if (this->number[0] < N.number[0]) //сначала проверка на разные знаки
			return '>';
		if (this->number[0] > N.number[0])
			return '<';
		int l = this->length, flag = 0;
		for (int i = len - l; i < len; i++) { //выявляем модуль какого числа больше
			if (this->number[i] > N.number[i])
				i = len, flag = 1;
			if (N.number[i] > this->number[i])
				i = len, flag = -1;
		}
		char sign = this->getSign();
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
		for (int i = 1; i < len; i++) { //инверитруем все разряды
			int n = 0xF - CharToHex(this->number[i]);
			this->number[i] = HexToChar(n);
		}
		int l = len - 1;
		while (l > 0 && this->number[l] == 'F') // поиск места для добавления единицы
			l--;
		if (l == 0) // если места нет произошло переполнение
			throw std::exception("Incorrect operand");
		int k = CharToHex(this->number[l]) + 1;
		this->number[l] = HexToChar(k); //добавляем единицу в найденное место
		for (int i = l + 1; i < len; i++)
			this->number[i] = '0';
		return *this;
	}
	const Hex Hex::Add(const Hex& N) {
		Hex Second = N, res,First = *this;
		if (First.number[0] == 'F') //перевод числа в дополнительный код при надобности
			First.Convert();
		if (Second.number[0] == 'F') //перевод числа в дополнительный код при надобности
			Second.Convert();
		int transfer = 0;// transfer - перенос из младшего разряда
		for (int i = len - 1; i > -1; i--) { //сложение чисел
			int sum = CharToHex(First.number[i]) + CharToHex(Second.number[i]) + transfer;
			res.number[i] = HexToChar((sum) % 0x10);
			transfer = 0;
			if (sum >>= 4)
				transfer = 1;
		}
		if (First.number[0] == Second.number[0] && Second.number[0] != res.number[0])
			throw std::exception("Overload"); //если знаки исходных чисел равны, а знак результата от них отличается - произошло переполнение
		if (res.number[0] == 'F') {
			try {
				res.Convert();
			}
			catch (std::exception & a) {
				throw std::exception("Overload");//при переводе числа в прямой код также можно поймать переполнение, не обнаруженное после сложения
			}
		}
		int k = 1;
		while (res.number[k] == '0') //вычисление длины результата
			k++;
		res.length = len - k;
		return res;
	}
	const Hex Hex::Decrease(const Hex& N) {
		Hex second = N, res;
		if (second.number[0] == '0') //домножаем второй операнд на -1
			second.number[0] = 'F';
		else
			second.number[0] = '0';
		try {
			res = this->Add(second);
		}
		catch (std::exception & a) {
			throw std::exception("Overload");
		}
		return res;
	}
	Hex& Hex::Move_l(int a) {
		if (a > (len - length)) {
			Hex a;
			*this = a;
			return *this;
		}
		for (int i = len - length; i < len; i++)
			if ((i - a) > 0)
				number[i - a] = number[i]; //перемещение цифр на новое место, если это возможно
		for (int i = 0; i < a; i++)
			number[len - i - 1] = '0'; //дополнение нулями числа справа
		length += a; // коррекция длины числа
		if (length > 31)
			length = 31;
		return *this;
	}
	Hex& Hex::Move_r(int a) {
		if (a >= length) {
			Hex a;
			*this = a;
			return *this;
		}
		if (a == 0)
			return *this;
		int stop = len - length;
		for (int i = len - 1; i >= stop; i--) {
			if ((i + a) < len)
				this->number[i + a] = this->number[i];//перемещение цифр на новое место, если это возможно
			this->number[i] = '0';
		}
		length -= a;
		return *this;
	}
	std::istream& Hex::Input(std::istream& c) {
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
			setN(s);
		}
		catch (std::exception & a) {
			c.setstate(std::ios::failbit);
		}
		return c;
	}
	std::ostream& Hex::Print(std::ostream& c) {
		if (number[0] == 'F')
			c << "-";
		int j = len - length;//место, с которого начинаются ненулевые элементы
		for (; j < len; j++)
			c << number[j];
		return c;
	}
}
