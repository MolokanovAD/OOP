#include <iostream>

#include "Table.h"
#include "Gun.h"
/*int main() {
	AirBattle::Weapon* mas[3];
	mas[0] = new AirBattle::Gun;
	mas[1] = new AirBattle::Launcher;
	mas[2] = new AirBattle::Gun(1,2,3,4);
	AirBattle::Gun* gp = (AirBattle::Gun*)mas[2];
	gp->get_accuracy();
}*/
using namespace AirBattle;
Scout f() {
	Scout a;
	return a;
}
int main() {
	std::string squad_name[4] = { "First","Second","Third","Fourths" };
	Table a;
	std::cout << "Enter words; press CTRL+z to quit:" << std::endl;
	for (int i = 0; i < 4; i++)
		a[squad_name[i]];
	std::cout << "Output by use of class iterator" << std::endl;
	std::cout << a;
	const Table ca = a;
	std::string s;
	std::cin.clear();
	std::cout << "Enter the word you want to find; press ctrl+z to quit" << std::endl;
	while (std::cin >> s, std::cin.good()) {
		try {
			a.Delete(s);
		}
		catch (const std::exception& msg)
		{
			std::cout << msg.what() << std::endl;
		}
	}
	std::cout << a;
	return 0;
}