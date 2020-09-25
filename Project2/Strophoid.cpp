#include "Strophoid.h"
#include <strstream>
#include <stdio.h>
#include <string.h>
double const PI = 3.1415926535;

namespace Project2 {
	Strophoid::Strophoid(double par){
		if(par == 0)
			throw std::exception("Invalid parameter");
		a = par;
	}
	double plus() { return 2 + PI / 2; }
	double minus() { return 2 - PI / 2; }
	Strophoid& Strophoid::setA(double par) {
		if (par == 0)
			throw std::exception("Invalid parameter");
		a = par; 
		return *this; 
	}
	double Strophoid::dist(double x) const { 
		if(x >= 360 || x < 0)
			throw std::exception("Invalid angle");
		x = x * PI / 180;
		if (x == PI/2 || x == 3*PI/2)
			throw std::exception("Invalid angle");
		double res = (-1) * a * cos(2 * x) / cos(x);
		return abs(res);
	}
	double Strophoid::S(double f()) const{ 
		return a * a * f();
	}
	double Strophoid::V() const {
		return abs(a) * a * a * PI * (2 * log(2) - 4 / 3);
	}
	double Strophoid::findY(double x) const { 
		if (a > 0)
			if (x >= a || x < (-1)*a)
				throw std::exception("Invalid x");
		if (a < 0)
			if (x > (-1)*a || x <= a)
				throw std::exception("Invalid x");
		if (a == x || (-1) * a == x)
			return 0;
		return x * sqrt((a + x) / (a - x));
	}
	char* Strophoid::formula() const {
		const char* s1 = "y ^ 2 * (x - ) + x ^ 2 * (x + ) = 0\n";
		int l = strlen(s1) + 1;
		char num[20];
		sprintf_s(num, 20, "%.2f", a);
		l += strlen(num)*2;
		char* s = new char[l];
		if (a < 0) {
			double val = (-1)*a;
			sprintf_s(s, l, "y ^ 2 * (x + %.2f)", val);
			int k = strlen(s);
			sprintf_s(s + k, l - k, " + x ^ 2 * (x - %.2f) = 0", val);
		}
		else {
			sprintf_s(s, l, "y ^ 2 * (x - %.2f)", a);
			int k = strlen(s);
			sprintf_s(s + k, l - k, " + x ^ 2 * (x + %.2f) = 0", a);
		}
		return s;
	}
}
