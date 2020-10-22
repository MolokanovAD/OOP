#ifndef HEX_H
#define HEX_H
#include <iostream>
#define len 32
namespace H16_2 {
	class Hex {
	private:
		unsigned char length;
		char number[len];
		void pushN(char*);
	public:
		Hex();
		Hex(char*);
		Hex(const int);
		char getSign() const{ return number[0]; }
		int Check() const;
		Hex& Convert();
		Hex operator +(const Hex&) const;
		Hex operator -(const Hex&) const;
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
