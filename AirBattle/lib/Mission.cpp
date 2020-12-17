#include "pch.h"
#include "Mission.h"
#include "Anti_Rocket.h"
#include "Disguise.h"
#include "Radio.h"
#include "Scout.h"
#include "Launcher.h"
#include "Gun.h"
#include <fstream>
#include <string>
namespace AirBattle {
	Mission::Mission() {

	}
	Mission::Mission(const int& aa, const int& bb, std::string* squad_name, std::string* en_squad_name, const int& w, const int& l) {
		if (w < (140 * aa + 200) || l < 400)
			throw std::runtime_error("Invalid size of map");
		int width = w / (aa + 1);
		for (int i = 0; i < aa; i++)
			a.Add(new Squad(0.0, i * width, 0, 1, 1, 1, 1), squad_name[i]);
		for (int i = 0; i < bb; i++)
			b.Add(new Squad(l - 24, i * width, 0, 1, 1, 1, 1), en_squad_name[i]);
	}

	Table& Mission::get_table(const bool& bl) {
		if (bl)
			return a;
		return b;
	}

	Squad& Mission::find_squad(const std::string& s, bool f) {
		ConstTableIt j;
		if (f) {
			j = a.find(s);
			if (j == a.end())
				throw std::runtime_error("Wrong index");
		}
		else {
			j = b.find(s);
			if (j == b.end())
				throw std::runtime_error("Wrong index");
		}
		return *((*j).second);
	}
	Plane& Mission::find_plane(const std::string& s, const int& i, bool team) {
		if (team) {
			ConstTableIt j = a.find(s);
			if (j == a.end())
				throw std::runtime_error("Wrong name");
			Plane* res;
			try {
				res = (*j).second->get_plane(i);
			}
			catch (std::runtime_error& aaa) {
				throw std::runtime_error("Wrong index");
			}
			return *res;
		}
		else {
			ConstTableIt j = b.find(s);
			if (j == b.end())
				throw std::runtime_error("Wrong name");
			Plane* res;
			try {
				res = (*j).second->get_plane(i);
			}
			catch (std::runtime_error& aaa) {
				throw std::runtime_error("Wrong index");
			}
			return *res;
		}
	}

	void Mission::save(const std::string& filename) {
		std::ofstream fout(filename);
		for (int k = 0; k < 2; k++) {
			ConstTableIt start, end;
			if (k == 0) {
				fout << a.get_size() << " ";
				start = a.begin();
				end = a.end();
			}
			else {
				fout << b.get_size() << " ";
				start = b.begin();
				end = b.end();
			}
			for (ConstTableIt j = start; j != end; j++) {
				/*fout << (*j).first.length() << " ";
				for (int rn = 0; rn < (*j).first.length(); rn++)
					fout << (*j).first[rn];*/
				fout << (*j).first << " ";
				Squad* s = (*j).second;
				fout << s->get_command() << " " << s->getx() << " " << s->gety() << " " << s->get_N() << " ";
				/*for (std::vector<Plane*>::const_iterator i = s->begin(); i != s->end(); i++)
					fout << (*i)->iam() << " ";*/
				for (other_vector<Plane*>::iterator i = s->begin(); i != s->end(); i++) {
					int type = (*i)->iam();
					fout << type << " " << (*i)->get_hp() << " " << (*i)->get_max_hp() << " " << (*i)->get_speed() << " " << (*i)->get_weapons_total() << " " << (*i)->get_x() << " " << (*i)->get_y() << " " << (*i)->get_radio_detection() << " ";
					switch (type)
					{
					case 1: {
						Anti_Rocket* ar = (Anti_Rocket*)(*i);
						fout << ar->get_pro() << " " << ar->get_pro_max() << " ";
						break;
					}

					case 2: {
						Disguise* d = (Disguise*)(*i);
						fout << d->get_det_coef() << " " << d->get_acc_coef() << " ";
						break;
					}

					case 3: {
						Radio* r = (Radio*)(*i);
						fout << r->get_pro_decr() << " " << r->get_disguise_decr() << " " << r->get_det_decr() << " ";
						break;
					}
					case 4: {
						Scout* ss = (Scout*)(*i);
						fout << ss->get_ignore_coef() << " ";
						break;
					}
					default:
						break;
					}
					for (other_vector<Weapon*>::iterator j = (*i)->begin(); j != (*i)->end(); j++) {
						bool t = (*j)->iam();
						fout << t << " " << (*j)->get_range() << " " << (*j)->get_fire_rate() << " " << (*j)->get_damage() << " ";
						switch (t)
						{
						case true: {
							Gun* g = (Gun*)(*j);
							fout << g->get_accuracy() << " ";
							break;
						}
						case false: {
							Launcher* l = (Launcher*)(*j);
							fout << l->get_max_ammo() << " " << l->get_ammo() << " ";
						}
						default:
							break;
						}
					}
				}
			}
		}
		fout.close();
	}
	void Mission::load(const std::string& filename) {
		std::ifstream fin(filename);
		if (!fin.is_open())
			throw std::runtime_error("Can't open this file");
		for (int m = 0; m < 2; m++) {
			int map;
			fin >> map;
			for (int i = 0; i < map; i++) {
				int command, iam, hp, max_hp, speed, w_t;
				unsigned char N;
				double x, y, rdet;
				std::string name;
				fin >> name;
				fin >> command >> x >> y >> N;
				Squad S(x, y, command);
				Plane* P = nullptr;
				for (int j = 0; j < N; j++) {
					fin >> iam >> hp >> max_hp >> speed >> w_t >> x >> y >> rdet;
					if (iam == 1) {
						int pro, pro_max;
						fin >> pro >> pro_max;
						P = new Anti_Rocket(x, y, max_hp, hp, pro_max, pro, speed, 0, 0, rdet);
					}
					if (iam == 2) {
						double det, acc;
						fin >> det >> acc;
						P = new Disguise(x, y, max_hp, hp, acc, det, speed, 0, 0, rdet);
					}
					if (iam == 3) {
						double det, disg, pro;
						fin >> pro >> disg >> det;
						P = new Radio(x, y, max_hp, hp, pro, disg, det, speed, 0, 0, rdet);
					}
					if (iam == 4) {
						double ign;
						fin >> ign;
						P = new Scout(x, y, max_hp, hp, ig, speed, 0, 0, rdet);
					}
					P->set_weapons_total(w_t);
					for (int w = 0; w < w_t; w++) {
						bool ia;
						int d;
						double f_r, range;
						fin >> ia >> range >> f_r >> d;
						if (ia) {
							double acc;
							fin >> acc;
							Weapon* ptr = new Gun(range, acc, f_r, d);
							P->Add_weapon(ptr);
							ptr->~Weapon();
						}
						if (!ia) {
							int pro, pro_max;
							fin >> pro_max >> pro;
							Weapon* ptr = new Launcher(range, f_r, d, pro, pro_max);
							P->Add_weapon(ptr);
							ptr->~Weapon();
						}
					}
					S.Add(P);
					P->~Plane();
				}
				S.set_N(N);
				if (m == 0)
					a.Add(&S, name);
				else
					b.Add(&S, name);
			}
		}
		fin.close();
	}
}