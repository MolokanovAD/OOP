#ifndef HEX_H
#define HEX_H
#include <iostream>
const int len = 32;
namespace Project3_3 {
	class Hex {
	private:
		int length;
		char* number;
	public:
		Hex();
		Hex(char*);
		Hex(const int);
		Hex(const Hex&);
		Hex(Hex &&);
		~Hex();
		Hex& setN(char*);
		void Formate(int);
		char getSign() const{ return number[0]; }
		int Check() const;
		Hex& Convert();
		const Hex operator +(const Hex&);
		const Hex operator -(const Hex&);
		Hex& operator <<=(int);
		Hex& operator >>=(int);
		Hex& operator =(const Hex&);
		char Compare(const Hex&);
		friend std::istream& operator >>(std::istream&, Hex&);
		friend std::ostream& operator <<(std::ostream&, const Hex&);
	};
	char upper(const char);
	char HexToChar(int);
	int CharToHex(char);

	Hex f(const Hex&);
	void dialog(Hex&, Hex&);
}
#endif
