#ifndef HEX_H
#define HEX_H
#include <iostream>
const int len = 32;
namespace Project3_2 {
	class Hex {
	private:
		unsigned char length;
		char number[len];
	public:
		Hex();
		Hex(char*);
		Hex(const int);
		Hex& setN(char*);
		char getSign() { return number[0]; }
		int Check();
		Hex& Convert();
		const Hex operator +(const Hex&);
		const Hex operator -(const Hex&);
		Hex& operator <<=(int);
		Hex& operator >>=(int);
		char Compare(const Hex&);
		friend std::istream& operator >>(std::istream&, Hex&);
		friend std::ostream& operator <<(std::ostream&, const Hex&);
	};
	char upper(const char);
	char HexToChar(int);
	int CharToHex(char);
}
#endif
