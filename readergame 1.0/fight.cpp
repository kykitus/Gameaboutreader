#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <conio.h>
#include <map>
#include <cmath>

#include "pl.h"

#include "fight.h"



void fight_option() {
	std::string enter;
	std::string enter2;
	int round = 1;

	InitEnemynames();
	enemy * gameenemy = enemy_creator();
	enemybackpack_creator(gameenemy);
	equipmentinfo * eqinfo = new equipmentinfo(gameenemy); // yay readable code

	int number = randomnumber(gameenemy->getbackpack_size() - 1);


	std::cout << "By an unpredictable accident you have found an worthy enemy in arena";
	enter = _getch();
	if (item_list[eqinfo->p_item_index]->gethavepassiveability()) { item_list[eqinfo->p_item_index]->passivepower(gameplayer_ptr, gameenemy); }
	if (item_list[eqinfo->e_item_index]->gethavepassiveability()) { item_list[eqinfo->e_item_index]->passivepower(gameenemy, gameplayer_ptr); }
	while (gameenemy->gethp() > 0 && gameplayer.gethp() > 0) {
		system("CLS");
		refresh(gameplayer_ptr, gameenemy);
		bar_writer(gameenemy, round);
		conditionchecker(gameplayer_ptr, gameenemy, "beforedefault");
		std::cout << "\n=attack[1]=   =use[2]=   =move[3]=   =rest[4]=   =check[5]=		distance = " << gameplayer.getdistance() << "\n";
		std::cin >> enter;
		try {
			if (gameplayer.havequeue()) {
				queuechecker(gameplayer_ptr, gameenemy, round);
			}
			else {
				switch (std::stoi(enter)) {
				case 1:
					conditionchecker(gameplayer_ptr, gameenemy, "beforeattacking");
					std::cout << "\nSelect type of attack\n";
					std::cout << "=side attack[1]=   =above attack[2]=   =stab[3]=   =cancel[y]=\n"; // 3 types attack have different power depending on type of weapon
					std::cin >> enter;
					if (enter == "y" || enter == "Y") {
						continue;
					}
					std::cout << "You decided to attack\n";
					enter2 = _getch();
					if (std::stoi(enter) > 3 || std::stoi(enter) < 1) {
						std::cout << "Are you going beyond this ultimate marial art? Sad\n";
						enter = _getch();
						continue;
					}
					if (gameplayer.gettiredness() < 3) {
						std::cout << "You are too tired\n";
						enter = _getch();
						continue;
					}
					else {
						if (attackprocess(gameplayer_ptr, gameenemy, std::stoi(enter))) {
							std::cout << "Enemy took damage";
							enter = _getch();
						}
						else {
							std::cout << "your attack missed";
							enter = _getch();
						}
						gameplayer.setlastmove(10 + std::stoi(enter));
						conditionchecker(gameplayer_ptr, gameenemy, "attacking");
					}
					break;

				case 2:
					conditionchecker(gameplayer_ptr, gameenemy, "beforeusing");
					std::cout << "Select item\n";
					gameplayer.getbackpack_whole();
					std::cout << "\n[y]cancel]";
					std::cin >> enter;

					if (enter == "y" || enter == "Y") {
						continue;
					}
					if (std::stoi(enter) - 1 >= gameplayer.getbackpack_size() || std::stoi(enter) - 1 < 0) {
						std::cout << "\nfree space is quite uneatable\n";
						enter = _getch();
						continue;
					}
					gameplayer.usebackpack_single(std::stoi(enter) - 1, round);
					gameplayer.setlastmove(20 + std::stoi(enter));
					conditionchecker(gameplayer_ptr, gameenemy, "using");
					break;

				case 3:
					conditionchecker(gameplayer_ptr, gameenemy, "beforemoving");
					std::cout << "\n  Select direction\n";
					std::cout << "           /[88]\\ \n";
					std::cout << "             |\n";
					std::cout << "           /[8]\\\n";
					std::cout << "	     |\n";
					std::cout << " [44]-[4]---[0]---[6]-[66]\n"; // movement
					std::cout << "             |\n";
					std::cout << "           \\[2]/\n";
					std::cout << "             |\n";
					std::cout << "           \\[22]/\n";
					std::cout << "\n[y]cancel\n";

					std::cin >> enter;
					if (enter == "y" || enter == "Y") {
						continue;
					}
					if (!gameplayer.movement_check(enter, false)) {
						continue;
					}
					gameplayer.movement_process(std::stoi(enter));
					gameenemy->setdistance(gameplayer.getdistance());
					std::cout << "You have moved";
					gameplayer.setlastmove(30 + std::stoi(enter));
					conditionchecker(gameplayer_ptr, gameenemy, "moving");
					break;
				case 4:
					conditionchecker(gameplayer_ptr, gameenemy, "beforeresting");
					std::cout << "\nYou decided to rest\n";
					gameplayer.rest_process();
					gameplayer.setlastmove(40 + std::stoi(enter));
					conditionchecker(gameplayer_ptr, gameenemy, "resting");
					enter = _getch();
					break;
				case 5:
					conditionchecker(gameplayer_ptr, gameenemy, "beforechecking");
					std::cout << "\nenemy's equipment:";
					std::cout << "\nWEAPON: " << weapon_list[eqinfo->e_weapon_category][eqinfo->e_weapon_index]->getname();
					std::cout << "\nARMOR: " << armor_list[eqinfo->e_armor_category][eqinfo->e_armor_index]->getname();
					std::cout << "\nHELM: " << armor_list[eqinfo->e_helm_category][eqinfo->e_helm_index]->getname();
					std::cout << "\nONE OF HIS CONSUMABLES: ";
					if (number >= 0 && gameenemy->getbackpack_size() != 0) {
						std::cout << consumable_list[gameenemy->getidofcons(1, number)][gameenemy->getidofcons(2, number)]->getname();
					}
					else { std::cout << "none"; }
					std::cout << "\nSTATUS: ";
					if (gameenemy->gettirednessstatus() == "high") { std::cout << "fine"; }
					else if (gameenemy->gettirednessstatus() == "medium") { std::cout << "little tired"; }
					else { std::cout << "tired"; }
					conditionchecker(gameplayer_ptr, gameenemy, "checking");
					enter = _getch();
					break;
				default:
					std::cout << "\nyoustupid";
					enter = _getch();
					break;
				}
			}
			conditionchecker(gameplayer_ptr, gameenemy, "default");

			std::cout << "\nNow opponents turn\n";
			enter = _getch();
			if (gameenemy->gethp() > 0) {
				if (gameenemy->havequeue()) {
					queuechecker(gameenemy, gameplayer_ptr, round);
				}
				else {
					conditionchecker(gameenemy, gameplayer_ptr, "beforedefault");
					enemy_ai(gameenemy, eqinfo, round);
					enter = _getch();
				}
				conditionchecker(gameenemy, gameplayer_ptr, "default");
				gameplayer.effectstatus_tick(round);
				gameenemy->effectstatus_tick(round);
				round++;
			}
		}
		catch (std::exception& l) {
			std::cout << "\nyoustupid\n";
			enter = _getch();
		}
	}
	if (item_list[eqinfo->p_item_index]->gethavepassiveability()) { item_list[eqinfo->p_item_index]->cancelpassive(gameplayer_ptr, gameenemy); }
	if (item_list[eqinfo->e_item_index]->gethavepassiveability()) { item_list[eqinfo->e_item_index]->cancelpassive(gameenemy, gameplayer_ptr); }
	if (gameenemy->gethp() <= 0) {
		std::cout << "\nYou have won!";
		enter = _getch();
		std::cout << "\nyou got " << gameenemy->getggolvalue() << " ggols\nand " << gameenemy->getlvlptsvalue() << " level points!";
		gameplayer.addlvlpts(gameenemy->getlvlptsvalue());
		gameplayer.addggol(gameenemy->getggolvalue());
		gameplayer.cleanup();
		if (gameplayer.checklvl(false)) {
			std::cout << "\nYou have reached new lvl!";
		}
	}
	else if (gameplayer.gethp() <= 0) {
		gameplayer.cleanup();
		std::cout << "\nYou lose!";
		enter = _getch();
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