#ifndef STROPHOID_H_
#define STROPHOID_H_
#include <math.h>

namespace Project2 {
	class Strophoid {
	private: 
		double a;
	public:
		Strophoid(double parameter = 1.0);
		Strophoid& setA(double aa);
		double getA() const{ return a; };
		double findY(double x) const;
		double dist(double x) const;
		double curv_rad() const{return fabs(a) * sqrt(2);}
		double S(double f()) const;
		double V()const;
		char* formula() const;
	};
	double plus();
	double minus();
}
#endif
