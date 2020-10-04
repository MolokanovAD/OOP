#ifndef HEX_H
#define HEX_H
#include <iostream>
const int len = 32;
namespace Project3_1 {
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
		const Hex Add(const Hex&);
		const Hex Decrease(const Hex&);
		Hex& Move_l(int);
		Hex& Move_r(int);
		char Compare(const Hex&);
		std::istream& Input(std::istream&);
		std::ostream& Print(std::ostream&);
	};
	char upper(const char);
	char HexToChar(int);
	int CharToHex(char);
}
#endif
