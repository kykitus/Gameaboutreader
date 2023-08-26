#pragma once


int weapondisplay(unsigned int weapon_type) { // function for all three types of weapon
	int typeweapon = weapon_type - 1;
	int count = 1;

	while (count < weapon_list[typeweapon].size()) {
		if (gameplayer.getlvl() < weapon_list[typeweapon][count]->getlvlreq() || weapon_list[typeweapon][count]->getclassweapon() != weapon_type || weapon_list[typeweapon][count]->getclassweapon() == 0) {
			count++;
			continue;
		}
		std::cout << "-[" << count << "]- " << weapon_list[typeweapon][count]->getname() << "  | attack - " << weapon_list[typeweapon][count]->getvalueattack() << "  | length - " << weapon_list[typeweapon][count]->getrange() << "m  ||| price: ";
		if (weapon_list[typeweapon][count]->getisbought() == 0) { std::cout << weapon_list[typeweapon][count]->getprice() << "\n"; }
		else {
			if (typeweapon == gameplayer.getidofwep(1) && count == gameplayer.getidofwep(2)) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		count++;
	}
	return count;
}

int armordisplay(int helmorno) { //makes also a variable have number equal to number of items in list
	int helmornot = helmorno - 1;
	int count = 1;
	while (count < armor_list[helmornot].size()) {
		if (gameplayer.getlvl() < armor_list[helmornot][count]->getlvlreq()) {
			count++;
			continue;
		}
		std::cout << "-[" << count << "]- " << armor_list[helmornot][count]->getname() << "\t| hardness - " << armor_list[helmornot][count]->gethardness() << "  | type - ";
		std::cout << typetranslator(armor_list[helmornot][count]->getclassarmor(), 3);
		std::cout << "  ||| price: ";
		if (armor_list[helmornot][count]->getisbought() == 0) { std::cout << armor_list[helmornot][count]->getprice() << "\n"; }
		else {
			switch (helmorno) {
			case 1:
				if (count == gameplayer.getidofarmor(2)) { std::cout << "equipped\n"; }
				else {
					std::cout << "equip\n";
				}
				break;
			case 2:
				if (count == gameplayer.getidofhelm(2)) { std::cout << "equipped\n"; }
				else {
					std::cout << "equip\n";
				}
				break;
			}
		}

		count++;
	}
	return count;

}

void consumabledisplay(int choose) {
	int chosen = choose;
	int count = 0;
	std::string powername = typetranslator(consumable_list[chosen][count]->gettypeofconsumable(), 4);
	if (chosen < consumable_list.size()) {
		while (count < consumable_list[chosen].size()) {
			if (gameplayer.getlvl() < consumable_list[chosen][count]->getlvlreq()) {
				count++;
				continue;
			}
			std::cout << "-[" << count + 1 << "]- " << consumable_list[chosen][count]->getname() << "\t|" << powername << " power - " << consumable_list[chosen][count]->consumable_showpower();
			std::cout << "\t||| price: ";
			std::cout << consumable_list[chosen][count]->getprice() << "\n";
			count++;
		}
		std::cout << "-[y]- to choose category again\n";
	}

}

void exceptionhandler(std::string enter, int shoptype) { //acts as non variable player response handler and as unq (unequip) function
	if (enter == "y" || enter == "Y") {
		system("CLS");
	}
	try {
		if (toupper(enter[0]) == 85 && toupper(enter[1]) == 78 && toupper(enter[2]) == 81) {
			switch (shoptype) {
			case 1:
				gameplayer.setidofwep(0);
				std::cout << "weapon unequipped";
				enter = _getch();
				system("CLS");
				break;

			case 2:
				if (enter == "unq1" || enter == "UNQ1") {
					gameplayer.setidofarmor(0);
					std::cout << "breastplate unequipped";
					enter = _getch();
					break;
				}
				else if (enter == "unq2" || enter == "UNQ2") {
					gameplayer.setidofhelm(0);
					std::cout << "headpiece unequipped";
					enter = _getch();
				}
				break;

			case 3:
				gameplayer.setidofitem(0);
				std::cout << "item unequipped";
				enter = _getch();
				break;

			default:
				std::cout << "how";
				enter = _getch();
				break;
			}
		}
		else if(enter != "y" && enter != "Y") {
			std::cout << "youstupid";
			enter = _getch();
		}
    }
	catch(std::exception& l) {
		std::cout << "youstupid";
		enter = _getch();
	}
	system("CLS");
}

void weapon_shop() {
	std::string choose;
	std::string choose2;
	std::string enter;

	std::cout << "\n\n		SHOP OF WEAPONS\n\n";
	std::cout << "\n//////////////////////////\n SWORD [1]\n//////////////////////////\n";
	weapondisplay(sword_weapon);
	std::cout << "\n//////////////////////////\n MACE [2]\n//////////////////////////\n";
	weapondisplay(mace_weapon);
	std::cout << "\n//////////////////////////\n SPEAR [3]\n//////////////////////////\n";
	weapondisplay(spear_weapon);
	std::cout << "\n- ggols:" << gameplayer.getggol() << "\n	write number of option to buy it ('unq' will unequip your weapon)\n\n	exit[y]\n";

	while (true) {
		std::cin >> choose2;
		try {
			int categoryofweapon = std::stoi(choose2) - 1;
			std::cin >> choose;
			int choosenid = std::stoi(choose);

			
			if(categoryofweapon >= weapon_list.size() || categoryofweapon < 0) {
				std::cout << "so you want more types? Do mod or buy dlc if I will do one. Another option is reconstruction groups. :)\n";
				enter = _getch();
				continue;
			}
			if (choosenid < 0 || choosenid > weapon_list[categoryofweapon].size() || weapon_list[categoryofweapon][choosenid]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (weapon_list[categoryofweapon][choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "are you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.getidofwep(0) == choosenid + (std::stoi(choose2) * 10)) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				gameplayer.addggol(weapon_list[categoryofweapon][choosenid]->getprice() * -1);
				gameplayer.setidofwep((std::to_string(categoryofweapon) + choose));
				weapon_list[categoryofweapon][choosenid]->setisbought(1);
				weapon_list[categoryofweapon][choosenid]->setprice(0); // you need to save to keep item after closing game
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch(std::exception& d) {
			exceptionhandler(choose, 1);
			break;
		}
	}
}

void armor_shop() {
	std::string choose;
	std::string choose2;
	std::string enter;
	int numberofarmors = 0;
	int numberofhelms = 0;

	std::cout << "\n\n		SHOP OF ARMORS\n\n";
	std::cout << "\n//////////////////////////\n  BREASTPLATE [1] \n//////////////////////////\n";
	numberofarmors = armordisplay(1);
	std::cout << "\n//////////////////////////\n  HEADPIECE [2] \n//////////////////////////\n";
	numberofhelms = armordisplay(2);
	std::cout << "\n- ggols:" << gameplayer.getggol() << "\n	write number of type of armor and press space, then number of option to buy it ('unq1' will unequip your breastplate and 'unq2' unequip headpiece)\n\n	exit[y]\n";
	
	
	// whole interaction process for both breastplate and helm, so it needs double number of checkers
	while (true) {
		std::cin >> choose2;
		try {
			int categoryofarmor = std::stoi(choose2) - 1;
			std::cin >> choose;
			int choosenid = std::stoi(choose);

			if (categoryofarmor >= armor_list.size() || categoryofarmor < 0) {
				std::cout << "so you want something more than armor and helm? Do mod or buy dlc if I will do one. :)\n";
				enter = _getch();
				continue;
			}
			if (choosenid < 0 || choosenid > armor_list[categoryofarmor].size() || armor_list[categoryofarmor][choosenid]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (armor_list[categoryofarmor][choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "are you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.getidofarmor(0) == choosenid + (categoryofarmor * 10) || gameplayer.getidofhelm(0) == choosenid + (categoryofarmor * 10)) {
					std::cout << "you already have it";
					enter = _getch();
					continue;
				}
				gameplayer.addggol(armor_list[categoryofarmor][choosenid]->getprice() * -1);
				if (categoryofarmor == 0) {
					gameplayer.setidofarmor((std::to_string(categoryofarmor) + choose));
				}
				else if (categoryofarmor == 1) {
					gameplayer.setidofhelm((std::to_string(categoryofarmor) + choose));
				}
				armor_list[categoryofarmor][choosenid]->setisbought(1);
				armor_list[categoryofarmor][choosenid]->setprice(0); // you need to save to keep item after closing game
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		
		catch (std::exception& l) {
			exceptionhandler(choose2, 2);
			break;
		}
	}
}


void litem_shop() {
	std::string choose;
	std::string enter;
	int count = 1;
	std::cout << "\n\n		SHOP OF ITEMS\n\n";
	std::cout << "\n//////////////////////////\n LUCKY ITEMS \n//////////////////////////\n";
	while (count < item_list.size()) {
		if (gameplayer.getlvl() < item_list[count]->getlvlreq()) {
			count++;
			continue;
		}
		std::cout << "-[" << count << "]- " << item_list[count]->getname() << "\t||| price: ";
		if (item_list[count]->getisbought() == 0) { std::cout << item_list[count]->getprice() << "\n"; }
		else {
			if (count == gameplayer.getidofitem()) { std::cout << "equipped\n"; }
			else {
				std::cout << "equip\n";
			}
		}
		count++;
	}


	std::cout << "\n- ggols:" << gameplayer.getggol() << "\n	write number of option to buy it ('unq' will unequip your  lucky item)\n\n	exit[y]\n";

	// whole interaction process
	while (true) {
		std::cin >> choose;
		try {
			int choosenid = std::stoi(choose);
			if (choosenid < 0 || choosenid - 1 >= count || item_list[choosenid - 1]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (item_list[choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "description:" << item_list[choosenid]->getabilitydes();
			std::cout << "\nare you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.getidofitem() == choosenid) {
					std::cout << "you already have it";
					enter = _getch();
					system("CLS");
					break;
				}
				gameplayer.addggol(item_list[choosenid]->getprice() * -1);
				gameplayer.setidofitem(choose);
				item_list[choosenid]->setisbought(1);
				item_list[choosenid]->setprice(0); // you need to save to keep item after closing game
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch (std::exception& d) {
			exceptionhandler(choose, 3);
			break;
		}
	}
}

void consumable_shop() {
	std::string choose;
	std::string choose2;
	std::string enter;
	std::cout << "\n//////////////////////////\n FUNNY EATABLES AND NON-EATABLES \n//////////////////////////";
	std::cout << "\n-[1]- potions of healing";
	std::cout << "\n-[2]- potions of energy";
	std::cout << "\n-[3]- things of resistance\n\n";
	std::cout << "\n- ggols:" << gameplayer.getggol() << "\nexit[y]\n";
	while (true) {
		std::cin >> choose2;
		try {
			int choosen2id = std::stoi(choose2) - 1;
			if (choosen2id < 0 || choosen2id  >= consumable_list.size()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			else {
				consumabledisplay(choosen2id);
			}
			std::cin >> choose;
			if (choose == "y" || choose == "Y") { // going back from chosen category
				continue;
			}
			int choosenid = std::stoi(choose) - 1; // choosenid is for backend while choose for backpack (technically frontend)
			if (consumable_list[choosen2id][choosenid]->getlvlreq() > gameplayer.getlvl()) {
				std::cout << "this option doesn't exist";
				continue;
			}
			if (consumable_list[choosen2id][choosenid]->getprice() > gameplayer.getggol()) {
				std::cout << "you have not enough money";
				continue;
			}
			std::cout << "\nare you sure?\nYES[y]\tNO[n]\n";
			std::cin >> enter;
			if (enter == "y" || enter == "Y") {
				if (gameplayer.addtobackpack(std::stoi(choose2) * 10 + std::stoi(choose), false) == true) { // example: 32 means 3 as type of potion and 2 as tier
					enter = _getch();
					system("CLS");
					break;
				}
				gameplayer.addggol(consumable_list[choosen2id][choosenid]->getprice() * -1);
				std::cout << "thanks\n";
				enter = _getch();
				system("CLS");
				break;
			}
			else if (enter == "n" || enter == "N") {
				std::cout << "ok";
				enter = _getch();
				system("CLS");
				break;
			}
		}
		catch (std::exception& d) {
			exceptionhandler(choose, 4);
			break;
		}
	}

}
