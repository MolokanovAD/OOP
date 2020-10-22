#ifndef HEX_H
#define HEX_H
#include <iostream>
#define len 32

namespace H16_1 {
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
		char Compare(const Hex&) const;
		Hex Add(const Hex&) const;
		Hex Decrease(const Hex&) const;
		Hex& Move_l(int);
		Hex& Move_r(int);
		std::istream& Input(std::istream&);
		std::ostream& Print(std::ostream&);
	};
	char upper(const char);
	char HexToChar(int);
	int CharToHex(char);

}
#endif
