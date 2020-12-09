#include <SFML/Graphics.hpp>
#include "Mission.h"
#include "Anti_Rocket.h"
#include "Disguise.h"
#include "Radio.h"
#include "Scout.h"
#include "Button.h"
#include "Object.h"
#include "SquadInfo.h"
#include "Launcher.h"
#include "moving.h"
#include "other_vector.h"
#define N 4
using namespace sf;
using namespace AirBattle;

/*!
	\brief Загрузка текстур самолетов из файла.
*/
void load_planes(Texture* T) {
	T[0].loadFromFile("images/A_r.png");
	T[1].loadFromFile("images/A_l.png");
	T[2].loadFromFile("images/D_r.png");
	T[3].loadFromFile("images/D_l.png");
	T[4].loadFromFile("images/R_r.png");
	T[5].loadFromFile("images/R_l.png");
	T[6].loadFromFile("images/S_r.png");
	T[7].loadFromFile("images/S_l.png");
}
/*!
	\brief Функция содержит реализацию графического интерфейса.
*/
int main() {
	Mission M;
	bool fa = false;
	int w = 900, l = 1800;
	std::cout << "0 - new game" << std::endl << "1 - load game" << std::endl;
	std::cin >> fa;
	std::string squad_name[4] = { "First","Second","Third","Fourths" };//позывные звеньев игрока
	std::string en_squad_name[4] = { "Enemy1","Enemy2","Enemy3","Enemy4" };//позывные звеньев врага
	std::string btn[2] = { "Squad","Plane" };//строки для кнопок для атаки
	if (!fa) {
		int width = w / (N + 1);
		for (int i = 0; i < N; i++)
			M.get_table(true).Add(new Squad(0.0, i * width, 0, 1, 1, 1, 1), squad_name[i]);
		for (int i = 0; i < N; i++)
			M.get_table(false).Add(new Squad(l - 24, i * width, 0, 1, 1, 1, 1), en_squad_name[i]);
	}
	else
		M.load("Data.txt");
	Clock clock;
	int o_t = std::clock(), holder = -1000;
	Texture T[8];
	load_planes(T);
	Font font;
	font.loadFromFile("Arial.ttf");
	RenderWindow window(VideoMode(l, w), "SFMLworks");
	other_vector<Button*> buttons, actions, numbers;
	std::string action_name[3]{ "Move","Stay","Attack" };
	Text msg;
	msg.setFont(font);
	msg.setPosition(l / 3 + 150, (w - 200) / 3 + 100);
	msg.setCharacterSize(100);
	msg.setFillColor(sf::Color::Yellow);
	msg.setString("You won!");
	RectangleShape line;
	Button save_button("Save", 550, w - 50, font);
	line.setSize(Vector2f(l, 2));
	line.setFillColor(Color::Black);
	line.setPosition(0, w - 195);
	for (int i = 0; i < N; i++) {//создание кнопок
		int y = w - 185 + i * 45;
		if(M.get_table(true).find(squad_name[i]) != M.get_table(true).end())
			buttons.push_back(new Button(squad_name[i], 10, y, font));//кнопки с позывными звеньев ользователя
		if (i < 3)
			actions.push_back(new Button(action_name[i], 140, y, font));//кнопки с действиями
		if (i < 2)
			numbers.push_back(new Button(btn[i], 280, y, font));//кнопки атаки звена и самолета
	}
	Button cancel("Cancel", 420, w - 50, font);//кнопка отмены действия
	other_vector<SquadInfo*> squads, en_squads;//векторы со звеьями пользователя и врага соответственно
	for (int i = 0; i < N; i++) {
		try {
			Squad* S = &M.find_squad(squad_name[i], true);
			squads.push_back(new SquadInfo(*S, squad_name[i], T, font, true));
		}
		catch (std::runtime_error& a) {}
	}
	for (int i = 0; i < N; i++) {
		try {
			Squad* S = &M.find_squad(en_squad_name[i], false);
			en_squads.push_back(new SquadInfo(*S, en_squad_name[i], T, font, false));
		}
		catch (std::runtime_error& a) {}
	}
	bool squad_chosen = false, action_chosen = false, number_chosen = false;
	SquadInfo* active = nullptr;//действующее звено
	int X = 100, Y = 100;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;
		Event event;
		Vector2i mpos = Mouse::getPosition(window);
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)//закрытие окна
				window.close();
			if (event.type == Event::MouseButtonPressed)//нажатие кнопки с именем звена
				if (event.key.code == Mouse::Left)
					for (auto it : buttons) {
						if (it->is_being_pressed(mpos.x, mpos.y)) {
							if (squad_chosen) {
								for (auto it1 : buttons)
									if (it1->isPressed())
										it1->press();
								if (action_chosen) {
									for (auto it2 : actions)
										if (it2->isPressed())
											it2->press();
									action_chosen = false;
									if (number_chosen) {
										for (auto it3 : numbers)
											if (it3->isPressed())
												it3->press();
										number_chosen = false;
									}
								}
								active = nullptr;
							}
							for (auto iter : squads)
								if (iter->get_name() == it->get_string()) {
									active = iter;//выбор звена, которое будет действовать
									it->press();
									squad_chosen = true;
								}
						}
					}
			if (event.type == Event::MouseButtonPressed)//сохранение
				if (event.key.code == Mouse::Left)
					if (save_button.is_being_pressed(mpos.x, mpos.y)) {
						holder = std::clock();
						M.save("Data.txt");
						save_button.press();
					}
			if (event.type == Event::MouseButtonPressed)//нажатие на кнопку действия
				if (event.key.code == Mouse::Left)
					if (squad_chosen) {
						for (auto it : actions) {
							if (it->is_being_pressed(mpos.x, mpos.y)) {
								if (action_chosen) {
									for (auto it1 : actions)
										if (it1->isPressed())
											it1->press();
									if (number_chosen) {
										for (auto it2 : numbers)
											if (it2->isPressed())
												it2->press();
									}
								}
								it->press();
								if (it->get_string() == "Move") {
									active->set_command(1);
									active->set_plane_attack(false);
									active->set_squad_attack(false);
								}
								if (it->get_string() == "Stay") {
									active->set_is_ready(false);
									active->set_command(0);
									active->set_plane_attack(false);
									active->set_squad_attack(false);
								}
								if (it->get_string() == "Attack") {
									active->set_command(2);
									active->set_is_ready(false);
								}
								action_chosen = true;
							}
						}
					}
			if (event.type == Event::MouseButtonPressed)//нажатие на кнопку отмены
				if (event.key.code == Mouse::Left)
					if (cancel.is_being_pressed(mpos.x, mpos.y)) {
						for (auto it1 : buttons) {
							if (it1->isPressed())
								it1->press();
							for (auto it1 : actions)
								if (it1->isPressed())
									it1->press();
							for (auto it1 : numbers)
								if (it1->isPressed())
									it1->press();
							squad_chosen = false;
							action_chosen = false;
							number_chosen = false;
						}
					}
			if (event.type == Event::MouseButtonPressed)//нажатие на отряд пользователя(вместо нажатия кнопки)
				if (event.key.code == Mouse::Left)
					for (auto it : squads) {
						if (it->is_being_pressed(mpos.x, mpos.y)) {
							for (auto it1 : buttons)
								if (it1->isPressed())
									it1->press();
							if (action_chosen)
								for (auto it2 : actions)
									if (it2->isPressed())
										it2->press();
							for (auto j : buttons)
								if (j->get_string() == it->get_name())
									j->press();
							active = it;
							squad_chosen = true;
						}
					}
			if (event.type == Event::MouseButtonPressed)//нажатие на точку, в которую полетит звено
				if (event.key.code == Mouse::Right)
					if (active && active->get_command() == 1) {
						X = mpos.x;
						Y = mpos.y;
						for (auto it1 : actions)
							if (it1->isPressed())
								it1->press();
						active->correct(X, Y, l, w);
						active->set_X(X);
						active->set_Y(Y);
						active->set_is_ready(true);
					}
			if (event.type == Event::MouseButtonPressed)//нажатие на кнопку атаки
				if (event.key.code == Mouse::Left)
					if (squad_chosen && action_chosen && active->get_command() == 2) {
						for (auto it : numbers)
							if (it->is_being_pressed(mpos.x, mpos.y)) {
								if (number_chosen) {
									for (auto it2 : numbers)
										if (it2->isPressed())
											it2->press();
								}
								it->press();
								number_chosen = true;
							}
					}
			if (event.type == Event::MouseButtonPressed)//выбор цели
				if (event.key.code == Mouse::Right)
					if (active && active->get_command() == 2 && number_chosen) {
						for (auto i : numbers) {
							if (i->isPressed()) {
								if (i->get_string() == "Squad") {
									for (auto it : en_squads)
										if (it->is_being_pressed(mpos.x, mpos.y)) {
											active->set_squad_attack(true);
											active->set_s_goal(it);
											for (auto it2 : numbers)
												if (it2->isPressed())
													it2->press();
										}
								}
								if (i->get_string() == "Plane") {
									for (auto it : en_squads)
										if (it->is_being_pressed(mpos.x, mpos.y)) {
											for (int it1 = 0; it1 < it->size(); it1++) {
												if (it->get_object(it1).is_being_pressed(mpos.x, mpos.y)) {
													active->set_plane_attack(true);
													active->set_p_goal(&it->get_object(it1));
												}
											}
										}
								}
								break;
							}
						}
					}
		}
		for (auto i : squads) {
			if (i->get_command() == 1 && i->is_ready_to_move())
				i->move(time, 0.001);
			if (i->get_command() == 2) {
				if (i->is_attacking_squad()) {//атака звена
					o_t = std::clock();
					i->s_attack(M.get_table(true), M.get_table(false), o_t);
					if (i->monster_kill()) {
						SquadInfo* killed = i->get_s_goal();
						for (auto k : squads) {//если еще кто-то стрелял по этому звену прекратить огонь
							if (k->is_attacking_squad() && i != k && k->get_s_goal() == killed) 
								k->stop_fire();
						}
						for (other_vector<SquadInfo*>::iterator ittt = en_squads.begin(); ittt != en_squads.end(); ittt++) {//удаление уничтоженного звена
							if ((*ittt) == killed) {
								en_squads.erase(ittt);
								break;
							}
						}
						M.get_table(false).Delete(i->get_s_goal()->get_name());
						i->set_squad_attack(false);
						i->set_s_goal(nullptr);
					}
				}
				if (i->is_attacking_plane()) {//атака одного самолета
					o_t = std::clock();
					i->p_attack(M.get_table(true), M.get_table(false), o_t);
					if (i->frag()) {
						for (auto k : squads) {//если еще кто-то стрелял по этому самолету прекратить огонь
							if (k->is_attacking_plane() && i != k && k->get_p_goal() == i->get_p_goal())
								k->stop_fire();
						}
						i->set_plane_attack(false);//прекратить огонь
						i->set_p_goal(nullptr);
					}
				}
			}

		}
		if (o_t - holder > 500)//полсекунды кнопка сохранения остается нажатой
			if (save_button.isPressed())
				save_button.press();
		for (auto iterator : squads)
			iterator->update(T);
		for (auto iterator : en_squads)
			iterator->update(T);
		window.clear(Color::White);
		if (M.get_table(false).get_size() == 0) {//вывод сообщения о победе
			window.draw(msg);
		}
		else
			if (M.get_table(true).get_size() == 0) {//вывод сообщения о поражении
				msg.setString("You lost!");
				window.draw(msg);
			}
		for (auto it : squads) {
			for (int iter = 0; iter < it->size(); iter++) {
				Object& cur = it->get_object(iter);
				if (cur.is_alive())
					cur.draw(window);
				else {
					it->Delete(iter);//удаление уничтоженного самолета
				}
			}
		}
		int k = 0;
		o_t = std::clock();
		for (auto it : en_squads) {
			for (int iter = 0; iter < it->size(); iter++) {
				Object& cur = it->get_object(iter);
				if (o_t % 1000 == k)//обновление информации об обнаружении самолетов врага (идет в течение секунды для оптимизации)
					cur.set_spotted(cur.is_spotted(M.get_table(false), M.get_table(true)));
				if (cur.is_alive()) {
					if (cur.is_spotted())
						cur.draw(window);
				}
				else {
					it->Delete(iter);//удаление уничтоженного самолета
				}
				k += 50;
			}
		}
		window.draw(line);
		save_button.draw(window);
		for (auto it : buttons) {
			it->draw(window);
		}
		cancel.draw(window);
		if (squad_chosen) {
			for (auto it : actions) {
				it->draw(window);
			}
			if (action_chosen && active->get_command() == 2)
				for (auto it : numbers) {
					it->draw(window);
				}
		}
		window.display();
	}
	return 0;
}