#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <conio.h>

#include "pl.h"

#include "fight.h"


void faight() {
	int hpcount = 0;
	std::string choose;
	Enemynames();
	enemy * enemyn = enenemy();
	while (enemyn->gethp() > 0 && playere.gethp() > 0) {
		std::cout << "===================			" << enemyn->getname() << "				===================";
		std::cout << "\n\nHP:";
		while (hpcount <= enemyn->gethp()) {
			std::cout << "/";
			hpcount++;
			if (hpcount % 100 == 0) {
				std::cout << "\n";
			}
		}
		std::cout << "\n\n\n\n\n\n\n\n\n";
		std::cout << "=attack[1]=	=use[2]=   =move[3]=\n";
		std::cin >> choose;
		try {
			switch (std::stoi(choose)) {
			case 1:
				std::cout << "Select type of attack\n";
				std::cout << "=side attack[1]=   =above attack[2]=   =stab[3]=";
				std::cin >> choose;
				attackprocess(false, std::stoi(choose));
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				std::cout << "youstupid";
				choose = _getch();
				break;
			}
		}
		catch (std::exception& l) {
			std::cout << "youstupid";
			choose = _getch();
			system("CLS");
		}
	}
	/*std::cout << "\n	NAME: " << enemyn->getname();
	std::cout << "\n	Points to new LVL: " << enemyn->getlvlptsvalue();
	std::cout << "\n\n	 HP:" << enemyn->gethp();
	std::cout << "\n	ATK:" << enemyn->getatk();
	std::cout << "\n	WEAPON:" << wepon[enemyn->getidofwep()]->getname();
	std::cout << "\n	BREASTPLATE:" << armo[enemyn->getidofarmor()]->getname();
	std::cout << "\n	HEADPIECE:" << hem[enemyn->getidofhelm()]->getname();
	std::cout << "\n\n [anything] back\n";*/
	std::cin >> choose;
	system("CLS");

}
