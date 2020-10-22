#ifndef F_H
#define F_H
#include <iostream>
#include "Hex.h"
char Interprete(int k);
void dialog(H16_3::Hex& a, H16_3::Hex& b);
H16_3::Hex f(const H16_3::Hex& b); // функция для тестирования перемещающего конструктора
H16_3::Hex FF(const H16_3::Hex& m); // функция для тестирования перемещающего равенства
#endif
