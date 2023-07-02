#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <conio.h>
#include <cmath>

#include "pl.h"

#include "fight.h"



void fight_option() {
	int hpcount = 0;
	std::string enter;
	InitEnemynames();
	enemy * gameenemy = enemy_creator();
	while (gameenemy->gethp() > 0 && gameplayer.gethp() > 0) {
		std::cout << "===================			" << gameenemy->getname() << "				===================";
		std::cout << "\n\nHP:";
		while (hpcount <= gameenemy->gethp()) {
			std::cout << "/";
			hpcount++;
			if (hpcount % 100 == 0) {
				std::cout << "\n";
			} 
		} // makes slashes look like hp bar
		hpcount = 0;
		std::cout << "\n\n\n\n\n\n\n\n\n";
		std::cout << "=attack[1]=   =use[2]=   =move[3]=		distance = " << gameplayer.getdistance() << "\n";
		std::cin >> enter;
		try {
			switch (std::stoi(enter)) {
			case 1:
				std::cout << "Select type of attack\n";
				std::cout << "=side attack[1]=   =above attack[2]=   =stab[3]="; // 3 types attack have different power depending on type of weapon
				std::cin >> enter;
				attackprocess(gameenemy, std::stoi(enter), 1);
				break;
			case 2:
				break;
			case 3:
				std::cout << "Select direction\n";
				std::cout << "           /[88]\\ \n";
				std::cout << "             |\n";
				std::cout << "           /[8]\\\n";
				std::cout << "	     |\n";
				std::cout << " [44]-[4]---[0]---[6]-[66]\n"; // movement
				std::cout << "             |\n";
				std::cout << "           \\[2]/\n";
				std::cout << "             |\n";
				std::cout << "           \\[22]/\n";

				std::cin >> enter;
				movement_process(std::stoi(enter));
				break;
			default:
				std::cout << "youstupid";
				enter = _getch();
				break;
			}
		}
		catch (std::exception& l) {
			std::cout << "youstupid";
			enter = _getch();
		}
		system("CLS");
	}
	std::cin >> enter;
	system("CLS");

}

/*std::cout << "\n	NAME: " << gameenemy->getname();
	std::cout << "\n	Points to new LVL: " << gameenemy->getlvlptsvalue();
	std::cout << "\n\n	 HP:" << gameenemy->gethp();
	std::cout << "\n	ATK:" << gameenemy->getatk();
	std::cout << "\n	WEAPON:" << weapon_list[gameenemy->getidofwep()]->getname();
	std::cout << "\n	BREASTPLATE:" << armor_list[gameenemy->getidofarmor()]->getname();
	std::cout << "\n	HEADPIECE:" << helm_list[gameenemy->getidofhelm()]->getname();
	std::cout << "\n\n [anything] back\n";*/