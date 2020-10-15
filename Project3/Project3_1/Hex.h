#ifndef HEX_H
#define HEX_H
#include <iostream>
const int len = 32;
const int N = 10;
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
		char getSign() const{ return number[0]; }
		int Check() const;
		Hex& Convert();
		char Compare(const Hex&);
		const Hex Add(const Hex&);
		const Hex Decrease(const Hex&);
		Hex& Move_l(int);
		Hex& Move_r(int);
		std::istream& Input(std::istream&);
		std::ostream& Print(std::ostream&);
	};
	char upper(const char);
	char HexToChar(int);
	int CharToHex(char);

	void dialog(Hex&, Hex&);
	void out(Hex&, Hex&, Hex&, const char*);
}
#endif
