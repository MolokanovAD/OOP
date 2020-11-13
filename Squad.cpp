#include "Squad.h"
#include <iostream>
namespace AirBattle {
	Squad::Squad(double x0, double y0,int anti_rocket, int radio, int disguise, int scout) {
		if (anti_rocket < 0 || anti_rocket > 4)
			throw std::exception("Invalid amount of anti-rocket planes");
		if (radio < 0 || radio > 4)
			throw std::exception("Invalid amount of radio planes");
		if (disguise < 0 || disguise > 4)
			throw std::exception("Invalid amount of disguise planes");
		if (scout < 0 || scout > 4)
			throw std::exception("Invalid amount of scout planes");
		N = anti_rocket + radio + disguise + scout;
		if (N > 4)
			throw std::exception("Too much planes");
		int i = 0;
		int cur = anti_rocket;
		plane = new Plane*[N];
		for (; i < cur; i++)
			plane[i] = new Anti_Rocket;
		cur += radio;
		for (; i < cur; i++)
			plane[i] = new Radio;
		cur += disguise;
		for (; i < cur; i++)
			plane[i] = new Disguise;
		cur += scout;
		for (; i < cur; i++)
			plane[i] = new Scout;
		x = x0;
		y = y0;
	}
	Squad::Squad(const Squad& a) {
		command = a.command;
		N = a.N;
		x = a.x;
		y = a.y;
		plane = new Plane * [N];
		for (int i = 0; i < N; i++)
			plane[i] = a.plane[i]->clone();
	}
	Squad::Squad(Squad&& a) {
		command = a.command;
		N = a.N;
		x = a.x;
		y = a.y;
		plane = a.plane;
		a.plane = nullptr;
	}
	Squad::~Squad() {
		for (int i = 0; i < N; i++)
			plane[i]->Free();
		delete[] plane;
	}


	int Squad::get_det_range()const {
		int r = 0;
		for (int i = 0; i < N; i++) {
			int k = plane[i]->get_radio_detection();
			if (k > r)
				r = k;
		}
		return r;
	}


	bool Squad::Delete(int& k) {
		if (k < 0 || k >= N)
			return false;
		N--;
		if (N == 0 && k == 0) {
			plane[k]->Free();
			delete plane;
			plane = nullptr;
			return true;
		}	
		Plane** old = plane;
		plane = new Plane * [N - 1];
		for (int i = 0; i < (N - 1); i++)
			if (i != k)
				plane[i] = old[k];
		old[k]->Free();
		return true;
	}
	bool Squad::Add(int& type) {
		if (N == 4 || type >4 || type < 1)
			return false;
		Plane** old = plane;
		plane = new Plane * [N+1];
		for (int i = 0; i < N; i++)
			plane[i] = old[i];
		switch (type) {
		case 1:
			plane[N] = new Anti_Rocket;
		case2:
			plane[N] = new Disguise;
		case 3:
			plane[N] = new Radio;
		case 4:
			plane[N] = new Scout;
		}
		N++;
		return true;
	}

	std::ostream& operator <<(std::ostream& c, const Squad& a){
		for (int i = 0; i < a.N; i++)
			c << *a.plane[i];
		c << std::endl << std::endl;
		return c;
	}
}